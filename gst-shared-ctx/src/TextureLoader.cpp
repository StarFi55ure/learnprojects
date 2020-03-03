//
// Created by julian on 2018/08/16.
//

#include "TextureLoader.h"
#include <CImg.h>
//
#include <GL/glew.h>

#include <cstdlib>
#include <iostream>

TextureLoader::TextureLoader() {

}

int TextureLoader::loadTexture(const char *fileName) {

    unsigned int texture;
    glGenTextures(1, &texture);

    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels, depth;

    namespace ci = cimg_library;

    ci::CImg<unsigned char> image("images/background.jpg");
    image.mirror("y");
    width = image.width();
    height = image.height();
    depth = image.depth();
    nrChannels = image.spectrum();
    image.permute_axes("cxyz");

    std::cout << "Image Size: " << width << "x" << height << std::endl;
    std::cout << "Image channels: " << nrChannels << std::endl;
    std::cout << "Image Depth: " << depth << std::endl;

    size_t BUFSIZE = width * height * depth * nrChannels * sizeof(unsigned char);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image.data());
    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);

    std::cout << "Loaded TextureID: " << texture << std::endl;
    return texture;
}
