//
// Created by julian on 2018/08/21.
//

#ifndef GSTSHARED_GLFWRENDER_H
#define GSTSHARED_GLFWRENDER_H

#include <GLFW/glfw3.h>

void drawObject();

void framebuffer_size_callback(struct GLFWwindow *window, int width, int height);

void processInput(struct GLFWwindow *window);

#endif //GSTSHARED_GLFWRENDER_H
