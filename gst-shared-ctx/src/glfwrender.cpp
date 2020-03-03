//
// Created by julian on 2018/08/21.
//

#include "glfwrender.h"

void drawObject() {
    glViewport(0, 0, 800, 600);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void framebuffer_size_callback(struct GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(struct GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}