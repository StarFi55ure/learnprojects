//
// Created by julian on 2018/08/15.
//

#include <iostream>
#include <cmath>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Shader.h"
#include "VideoSurface.h"
#include "glfwrender.h"
#include "GstPlayer.h"

int main(int argc, char *argv[]) {
    std::cout << "Hello World" << std::endl;

    // setup X11 with threads
    int x11_thread_status = XInitThreads();
    if (x11_thread_status == 0) {
        std::cout << "Could not initialize thread support" << std::endl;
        return -1;
    }

    // setup opengl stuff

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    glewExperimental = true;
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        std::cout << glewGetErrorString(err) << std::endl;
    }
    std::cout << "Using GLEW: " << glewGetString(GLEW_VERSION) << std::endl;

//    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
//        std::cout << "Failed to load GLAD" << std::endl;
//        return -1;
//    }

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    glViewport(0, 0, 800, 600);

    int nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    std::cout << "Max no attribs: " << nrAttributes << std::endl;
    glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &nrAttributes);
    std::cout << "Max no textures: " << nrAttributes << std::endl;

    Shader mainShader = Shader("shaders/mainShader.vert", "shaders/mainShader.frag");
    VideoSurface mainVideoSurface = VideoSurface(mainShader);

    // setup gstreamer
    GstPlayer gstplayer;
    if (!gstplayer.initPlayer(window)) {
        std::cout << "Error initializing player" << std::endl;
        //return -1;
    }
    gstplayer.startPlayback();

//    GstPlayer gstplayer2;
//    gstplayer2.initPlayer(window);
//    gstplayer2.startPlayback();

    while (!glfwWindowShouldClose(window)) {
        processInput(window);
        gstplayer.processMessages();
//        gstplayer2.processMessages();

        mainVideoSurface.use();
        drawObject();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    gstplayer.stopPlayback();
    gstplayer.processMessages();

    glfwTerminate();
    return 0;
}

