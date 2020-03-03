//
// Created by julian on 2018/08/21.
//

#ifndef GSTSHARED_GSTPLAYER_H
#define GSTSHARED_GSTPLAYER_H

#include <iostream>

#define GST_USE_UNSTABLE_API 1


#include <GLFW/glfw3.h>

#define GLFW_EXPOSE_NATIVE_X11 1
#define GLFW_EXPOSE_NATIVE_GLX 1

#include <GLFW/glfw3native.h>

#include <gst/gst.h>
#include "Shader.h"

class GstPlayer {

public:
    GstPlayer();
    void setShader(Shader redrawShader);

    bool initPlayer(GLFWwindow* window);
    int startPlayback();
    int stopPlayback();
    void processMessages();


protected:
    GstElement* pipeline;
    static gboolean predraw_texture(GstElement* object, guint width, guint height, guint texID, gpointer user_data);
    static gboolean redraw_texture(GstElement* object, guint width, guint height, guint texID, gpointer user_data);
public:
    virtual ~GstPlayer();

protected:
    Shader redrawShader;

    GstElement* file;
    GstElement* glfilterapp;
    GstElement* glfilterapp2;

    GstBus* bus;

    GstStateChangeReturn stateChangeReturn;

    GstContext* x11context;
    GstContext* glcontext;

    int predraw_texID;

    int redrawEBO;
    int redrawVBO;

};


#endif //GSTSHARED_GSTPLAYER_H
