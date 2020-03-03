//
// Created by julian on 2018/08/17.
//

#include <GL/glew.h>

#include "VideoSurface.h"
#include "TextureLoader.h"

VideoSurface::VideoSurface(const Shader &shader) : shader(shader) {

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

    glGenVertexArrays(1, &this->VAO);
    glBindVertexArray(this->VAO);

    // upload indices to buffer
    glGenBuffers(1, &this->EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // upload vertices to buffer
    glGenBuffers(1, &this->VBO);
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    this->shader.use();

    // link attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glUniform1i(glGetUniformLocation(this->shader.ID, "ourTexture"), GL_TEXTURE0);

    glBindVertexArray(0);

    // load textures
    TextureLoader loader = TextureLoader();
    glTextures.push_back(loader.loadTexture("background.jpg"));

}

void VideoSurface::use() {
    this->shader.use();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, glTextures[0]);

    glBindVertexArray(this->VAO);
}
