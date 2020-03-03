//
// Created by julian on 2018/08/21.
//

#include <gst/gl/gl.h>
#include <gst/gl/x11/gstgldisplay_x11.h>

#include <X11/Xlib.h>
#include "GstPlayer.h"

static bool _gst_initialized = FALSE;

GstPlayer::GstPlayer() {

    redrawShader = Shader("shaders/copyShader.vert", "shaders/copyShader.frag");

    if (!_gst_initialized) {
        std::cout << "Initializing GST" << std::endl;
        gst_init(NULL, NULL);
        _gst_initialized = true;
    } else {
        std::cout << "GST already initialized" << std::endl;
    }

}

GstPlayer::~GstPlayer() {
    g_print("Destructing GstPlayer.\n");
    if (G_IS_OBJECT(this->pipeline)) { gst_object_unref(this->pipeline); }
    if (G_IS_OBJECT(this->file)) { gst_object_unref(this->file); }

    if (G_IS_OBJECT(this->x11context)) { gst_object_unref(this->x11context); }
    if (G_IS_OBJECT(this->glcontext)) { gst_object_unref(this->glcontext); }
}

bool GstPlayer::initPlayer(GLFWwindow* window) {

    const char *pl = "filesrc name=file ! qtdemux name=demux demux.video_0 ! avdec_h264 ! videoconvert "
                     "! glupload ! glfilterapp name=filter ! glfilterapp name=filter2 "
//                     "! gldownload ! filesink location=/dev/null";
//                     "! fakesink sync=true";
                     //"! gldownload ! videoconvert ";
//                     "! appsink name=dummy ! glimagesinkelement";
                     "! glimagesinkelement name=dummy";
    this->pipeline = gst_parse_launch(pl, NULL);

    if (!this->pipeline) {
        g_printerr("Pipeline not created\n");
        return -1;
    }

    this->file = gst_bin_get_by_name(GST_BIN(this->pipeline), "file");
    if (!this->file) {
        g_printerr("Could not find file element\n");
        return -1;
    }
    g_object_set(this->file, "location", "vid.mp4", NULL);

    this->glfilterapp = gst_bin_get_by_name(GST_BIN(this->pipeline), "filter");
    if (!this->glfilterapp) {
        g_printerr("Could not find filter element\n");
        return -1;
    }

    this->glfilterapp2 = gst_bin_get_by_name(GST_BIN(this->pipeline), "filter2");

    this->bus = gst_element_get_bus(this->pipeline);
    if (!this->bus) {
        g_printerr("Could not get the pipeline bus");
        return -1;
    }

    // setup X11 context
    Display* dpy = glfwGetX11Display();
    GstGLDisplay* gldisplay = GST_GL_DISPLAY(gst_gl_display_x11_new_with_display(dpy));
    this->x11context = gst_context_new(GST_GL_DISPLAY_CONTEXT_TYPE, TRUE);
    gst_context_set_gl_display(this->x11context, gldisplay);

    //gst_object_unref(gldisplay);

    // setup OpenGL context
    GLXContext ctx = glfwGetGLXContext(window);
    GstGLContext* gst_glcontext = gst_gl_context_new_wrapped(gldisplay, (guintptr) ctx, GST_GL_PLATFORM_GLX, GST_GL_API_OPENGL3);
    GstStructure* s;
    this->glcontext = gst_context_new("gst.gl.app_context", TRUE);
    s = gst_context_writable_structure(this->glcontext); // FIXME: probably needs an unref, check apidoc
    gst_structure_set(s, "context", GST_GL_TYPE_CONTEXT, gst_glcontext, NULL);

    gst_object_unref(gst_glcontext);

    //gst_element_set_context(this->pipeline, this->x11context);
    gst_element_set_context(GST_ELEMENT(this->glfilterapp), this->glcontext);
    gst_element_set_context(GST_ELEMENT(this->glfilterapp2), this->glcontext);

    g_signal_connect(this->glfilterapp, "client-draw", G_CALLBACK(predraw_texture), this);
    g_signal_connect(this->glfilterapp2, "client-draw", G_CALLBACK(redraw_texture), this);

//    // print playing dot graph
//    GST_DEBUG_BIN_TO_DOT_FILE(GST_BIN(this->pipeline), GST_DEBUG_GRAPH_SHOW_ALL, "graph");

    return TRUE;
}

gboolean GstPlayer::predraw_texture(GstElement *object, guint width, guint height, guint texID, gpointer user_data) {
    //g_print("in redraw_texture: width (%i) height (%i) texID (%i)\n", width, height, texID);
    //g_print("elem name: %s\n", GST_ELEMENT_NAME(object));
//    GstContext* gstctx = GST_CONTEXT(gst_element_get_context(object, "gst.gl.app_context"));
//    GstGLContext* ctx = reinterpret_cast<GstGLContext *>(gst_structure_get(gst_context_get_structure(gstctx), "context"));
//    g_print("ctx in redraw: %i\n", ctx);

//    int newTex;
//    glGenTextures(1, (GLuint *) &newTex);
//    g_print("New texture id: %d\n", newTex);
    GstPlayer* currentPlayer = reinterpret_cast<GstPlayer*>(user_data);
    currentPlayer->predraw_texID = texID;

    return FALSE;
}

gboolean GstPlayer::redraw_texture(GstElement *object, guint width, guint height, guint texID, gpointer user_data) {
    g_print("in redraw_texture: width (%i) height (%i) texID (%i)\n", width, height, texID);

    GstPlayer* currentPlayer = reinterpret_cast<GstPlayer*>(user_data);

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    std::cout << "GL Error (START): " << glGetError() << std::endl;
//    int src_texid = currentPlayer->predraw_texID;
//    g_print("Source ID: %d\n", src_texid);
//    int dst_texid = 1;
    int src_texid = 1;
    g_print("Source ID: %d\n", src_texid);
    int dst_texid = texID;

    float vertices[] = {
            // vertices             // color            // texture coords
            0.5f, 0.5f, 0.0f,       1.0f, 0.0f, 0.0f,   1.0f, 1.0f,
            0.5f, -0.5f, 0.0f,      0.0f, 1.0f, 0.0f,   1.0f, 0.0f,
            -0.5f, -0.5f, 0.0f,     0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
            -0.5f, 0.5f, 0.0f,      1.0f, 0.5f, 0.3f,   0.0f, 1.0f
    };

    unsigned int indices[] = {
            0, 1, 3,
            1, 2, 3
    };

    // upload indices to buffer
    glGenBuffers(1, (GLuint*) &currentPlayer->redrawEBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, currentPlayer->redrawEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // upload vertices to buffer
    glGenBuffers(1, (GLuint*) &currentPlayer->redrawVBO);
    glBindBuffer(GL_ARRAY_BUFFER, currentPlayer->redrawVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    currentPlayer->redrawShader.use();

    // link attributes
    int aPosLoc = glGetAttribLocation(currentPlayer->redrawShader.ID, "aPos");
    glVertexAttribPointer(aPosLoc, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(aPosLoc);

    int aColorLoc = glGetAttribLocation(currentPlayer->redrawShader.ID, "aColor");
    std::cout << "aColorLoc: " << aColorLoc << std::endl;
    glVertexAttribPointer(aColorLoc, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(aColorLoc);

    int aTexCoordLoc = glGetAttribLocation(currentPlayer->redrawShader.ID, "aTexCoord");
    glVertexAttribPointer(aTexCoordLoc, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
    glEnableVertexAttribArray(aTexCoordLoc);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, dst_texid);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, src_texid);

    glUniform1i(glGetUniformLocation(currentPlayer->redrawShader.ID, "ourTexture"), 0);

    // setup framebufferobject
    unsigned int fbo;
    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, src_texid, 0);

    unsigned int rbo;
    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, 1280, 720);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
//
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        std::cout << "ERROR:FRAMEBUFFER::Framebuffer incomplete!!!" << std::endl;
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    // render
    glViewport(0, 0, 1080, 720);
    //glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

//
//    // reset framebuffer
//    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, 0, 0);

    //glBindFramebuffer(GL_FRAMEBUFFER, 0);

//    //glDeleteFramebuffers(1, &fbo);
//    glDeleteVertexArrays(1, &vao);

    std::cout << "GL Error (END): " << glGetError() << std::endl;
    return FALSE;
}


int GstPlayer::startPlayback() {
    stateChangeReturn = gst_element_set_state(this->pipeline, GST_STATE_PLAYING);
    if (stateChangeReturn == GST_STATE_CHANGE_FAILURE) {
        g_printerr("Unable to set the pipeline to PLAYING state.\n");
        return -1;
    }
    this->processMessages();

    return 0;
}

int GstPlayer::stopPlayback() {
    // print playing dot graph
    GST_DEBUG_BIN_TO_DOT_FILE(GST_BIN(this->pipeline), GST_DEBUG_GRAPH_SHOW_ALL, "graph");

    stateChangeReturn = gst_element_set_state(this->pipeline, GST_STATE_NULL);
    if (stateChangeReturn == GST_STATE_CHANGE_FAILURE) {
        g_printerr("Unable to set the pipeline to NULL state.\n");
        return -1;
    }

    return 0;
}

void GstPlayer::processMessages() {

    bool hasMessages = true;

    GstMessageType types = (GstMessageType) (GST_MESSAGE_ERROR | GST_MESSAGE_EOS | GST_MESSAGE_STATE_CHANGED);
    //types = (GstMessageType) (types | GST_MESSAGE_NEED_CONTEXT | GST_MESSAGE_HAVE_CONTEXT);

    GstMessage* msg = NULL;
    while(hasMessages) {
        msg = gst_bus_pop_filtered(this->bus, types);
        if (msg != NULL) {
            GError* err;
            gchar* debug_info;
            const gchar* context_type;

            switch(GST_MESSAGE_TYPE(msg)) {
                case GST_MESSAGE_ERROR:
                    gst_message_parse_error(msg, &err, &debug_info);
                    g_printerr("Error received from element %s: %s\n", GST_OBJECT_NAME(msg->src), err->message);
                    g_printerr("Debugging information: %s\n", debug_info ? debug_info : "none");
                    g_clear_error(&err);
                    g_free(debug_info);
                    break;
                case GST_MESSAGE_EOS:
                    g_print("EOS reached.\n");
                    break;
                case GST_MESSAGE_STATE_CHANGED:
                    if (GST_MESSAGE_SRC(msg) == GST_OBJECT(this->pipeline)) {
                        GstState old_state, new_state, pending_state;
                        gst_message_parse_state_changed(msg, &old_state, &new_state, &pending_state);
                        g_print("Pipeline state changed from %s to %s:\n",
                                gst_element_state_get_name(old_state), gst_element_state_get_name(new_state));
                    }
                    break;
                case GST_MESSAGE_NEED_CONTEXT:
                    gst_message_parse_context_type(msg, &context_type);
//                    if (g_strcmp0(context_type, "gst.gl.app_context") == 0) {
//                        g_print("OpenGL Context Request Intercepted! %s\n", context_type);
//                        g_print("Current element: %s\n", GST_ELEMENT_NAME(msg->src));
//                        gst_element_set_context(GST_ELEMENT(msg->src), this->glcontext);
//                    }
//                    if (g_strcmp0(context_type, GST_GL_DISPLAY_CONTEXT_TYPE) == 0) {
//                        g_print("X11 Display Request Intercepted! %s\n", context_type);
//                        g_print("Current X11 element: %s\n", GST_ELEMENT_NAME(msg->src));
//                        g_print("Is object: %s\n", G_IS_OBJECT(this->x11context));
//                        gst_element_set_context(GST_ELEMENT(msg->src), this->x11context);
//                    }
                    break;
                case GST_MESSAGE_HAVE_CONTEXT:
                    //gst_message_parse_context_type(msg, &context_type);
                    //g_print("Created context type: %s\n", context_type);
                    g_print("==============\n");
                    g_print("Created Context\n");
                    g_print("Current element: %s\n", GST_ELEMENT_NAME(msg->src));
                    GList* list = gst_element_get_contexts(GST_ELEMENT(msg->src));
                    GList* l;
                    for (l = list; l != NULL; l = l->next) {
                        GstContext* c = static_cast<GstContext *>(l->data);
                        g_print("Context name: %s\n", gst_context_get_context_type(c));
                    }
                    g_print("==============\n");
                    break;
//                default:
//                    g_printerr("Unexpected message received: %s\n", GST_MESSAGE_TYPE_NAME(msg));
//                    break;
            }
            gst_message_unref(msg);
        } else {
            hasMessages = false;
        }
    }
}

void GstPlayer::setShader(Shader redrawShader) {
    this->redrawShader = redrawShader;
}
