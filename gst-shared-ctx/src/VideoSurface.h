//
// Created by julian on 2018/08/17.
//

#ifndef GSTSHARED_VIDEOSURFACE_H
#define GSTSHARED_VIDEOSURFACE_H

#include <vector>

#include "Shader.h"

class VideoSurface {
public:
    VideoSurface(const Shader &shader);

    void use();

protected:
    Shader shader;

    std::vector<int> glTextures;

    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;
};


#endif //GSTSHARED_VIDEOSURFACE_H
