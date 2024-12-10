#pragma once

#include <vector>

#include "shader.h"


class ShaderProgram {

private:
    unsigned int internalID;
    const std::vector<Shader>& shaders;

public:
    ShaderProgram(const std::vector<Shader>& shaders);

    void use();

    unsigned int getID();

    void setUniform(const std::string& name, float x, float y, float z, float alpha);
    
    void setUniform(const std::string&name, int x);
};