#pragma once

#include <iostream>

#include <glad/glad.h>


class Shader {
private:
    std::string filename;
    unsigned int type;
    const std::string code;
    const char* internalCode;
    unsigned int internalID;

    void compile();

    void checkCompilationSuccess();

public:
    Shader(const std::string& filename, unsigned int type = GL_VERTEX_SHADER);

    unsigned int getID() const;
};