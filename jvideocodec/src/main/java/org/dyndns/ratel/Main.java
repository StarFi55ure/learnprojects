package org.dyndns.ratel;


import org.bytedeco.javacpp.BytePointer;
import org.bytedeco.javacpp.DoublePointer;
import org.bytedeco.javacpp.PointerPointer;
import org.bytedeco.javacpp.avutil;

import java.io.IOException;
import java.io.OutputStream;
import java.nio.DoubleBuffer;
import java.nio.file.Files;
import java.nio.file.Paths;

import static org.bytedeco.javacpp.avcodec.*;
import static org.bytedeco.javacpp.avformat.*;
import static org.bytedeco.javacpp.avutil.*;
import static org.bytedeco.javacpp.swscale.*;

public class Main {

    public static void main(String[] args) throws IOException {

        AVFormatContext     pFormatContext = new AVFormatContext(null);
        int                 i;
        int                 videoStream;
        AVCodecContext      pCodecCtx = null;
        AVCodec             pCodec = null;
        AVFrame             pFrame = null;
        AVFrame             pFrameRGB = null;
        AVPacket            packet = new AVPacket();
        int[]               frameFinished = new int[1];
        int                 numBytes;
        BytePointer         buffer = null;

        AVDictionary        optionsDict = null;
        SwsContext          sws_ctx = null;


        String              fileName = "input.webm";
        av_register_all();

        if (avformat_open_input(pFormatContext, fileName, null, null) != 0) {
            System.out.println("Couldnt open file");
            System.exit(1);
        }

        if (avformat_find_stream_info(pFormatContext, (PointerPointer) null) < 0) {
            System.out.println("Could not find stream info");
            System.exit(1);
        }

        av_dump_format(pFormatContext, 0, fileName, 0);

        videoStream = -1;
        for (i = 0; i < pFormatContext.nb_streams(); i++) {
            if (pFormatContext.streams(i).codec().codec_type() == AVMEDIA_TYPE_VIDEO) {
                videoStream = i;
                break;
            }
        }

        if (videoStream == -1) {
            System.out.println("Could not find any video streams");
            System.exit(1);
        }

        pCodecCtx = pFormatContext.streams(videoStream).codec();

        pCodec = avcodec_find_decoder(pCodecCtx.codec_id());
        if (pCodec == null) {
            System.out.println("Unsupported codec!");
            System.exit(1);
        }

        if (avcodec_open2(pCodecCtx, pCodec, optionsDict) < 0) {
            System.out.println("Could not open codec");
            System.exit(1);
        }

        pFrame  = av_frame_alloc();

        pFrameRGB = av_frame_alloc();
        if (pFrameRGB == null) {
            System.out.println("Could not allocate frame");
            System.exit(1);
        }

        numBytes = avpicture_get_size(AV_PIX_FMT_RGB24, pCodecCtx.width(), pCodecCtx.height());
        buffer = new BytePointer(av_malloc(numBytes));

        sws_ctx = sws_getContext(pCodecCtx.width(), pCodecCtx.height(), pCodecCtx.pix_fmt(),
                pCodecCtx.width(), pCodecCtx.height(),
                AV_PIX_FMT_RGB24, SWS_BILINEAR, null, null, (DoublePointer) null);

        avpicture_fill(new AVPicture(pFrameRGB), buffer, AV_PIX_FMT_RGB24,
                pCodecCtx.width(), pCodecCtx.height());

        i = 0;
        while (av_read_frame(pFormatContext, packet) >= 0) {
            if (packet.stream_index() == videoStream) {
                avcodec_decode_video2(pCodecCtx, pFrame, frameFinished, packet);

                if (frameFinished[0] != 0) {
                    sws_scale(sws_ctx, pFrame.data(), pFrame.linesize(), 0,
                            pCodecCtx.height(), pFrameRGB.data(), pFrameRGB.linesize());


                    if (++i <= 10) {
                        SaveFrame(pFrameRGB, pCodecCtx.width(), pCodecCtx.height(), i);
                    } else {
                        break;
                    }
                }
            }

            av_free_packet(packet);

        }


        av_free_packet(packet);

        av_free(buffer);
        av_free(pFrameRGB);
        av_free(pFrame);

        avcodec_close(pCodecCtx);
        avformat_close_input(pFormatContext);

        System.exit(0);

    }

    private static void SaveFrame(AVFrame pFrame, int width, int height, int i) throws IOException {

        OutputStream stream = Files.newOutputStream(Paths.get("frame-" + i + ".ppm"));

        stream.write(("P6\n" + width + " " + height + "\n255\n").getBytes());

        BytePointer data = pFrame.data(0);
        byte[] bytes = new byte[width * 3];
        int l = pFrame.linesize(0);
        for (int y=0; y < height; y++) {
            data.position(y * l).get(bytes);
            stream.write(bytes);
        }

        stream.close();
    }
}





