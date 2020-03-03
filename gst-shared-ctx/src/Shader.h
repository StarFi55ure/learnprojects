//
// Created by julian on 2018/08/16.
//

#ifndef GSTSHARED_SHADER_H
#define GSTSHARED_SHADER_H

#include <string>

class Shader {
public:
    unsigned int ID = 0;

    Shader(const char* vertexPath, const char* fragmentPath);

    Shader();

    void use();

    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;

};


#endif //GSTSHARED_SHADER_H
