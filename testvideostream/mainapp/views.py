import mimetypes
import os
from wsgiref.util import FileWrapper

from django.http.response import HttpResponse, StreamingHttpResponse
from django.shortcuts import render


# Create your views here.

def stream_video(request):
    file_to_stream = '/var/www/html/output.mp4'
    filename = os.path.basename(file_to_stream)
    chunksize = 8192

    response = StreamingHttpResponse(FileWrapper(open(file_to_stream, 'rb'), chunksize),
                                     content_type=mimetypes.guess_type(file_to_stream)[0])
    response['Content-Length'] = os.path.getsize(file_to_stream)
    return response


def live_stream(request):
    file_to_stream = '/var/www/html/output.mp4'
    filename = os.path.basename(file_to_stream)
    chunksize = 8192

    response = StreamingHttpResponse(FileWrapper(open(file_to_stream, 'rb'), chunksize),
                                     content_type=mimetypes.guess_type(file_to_stream)[0])
    response['Content-Length'] = os.path.getsize(file_to_stream)
    return response


def index(request):
    return render(request, 'mainapp/home.html', {

    })
