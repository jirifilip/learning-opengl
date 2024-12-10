#pragma once

#include <iostream>
#include <memory>
#include <functional>

#include <glad/glad.h>


class Texture {
private:
    int width;
    int height;
    int channels;

    unsigned int internalID;

    std::unique_ptr<unsigned char, std::function<void(unsigned char*)>> loadImage(const std::string& filename);

public:
    Texture(const std::string& filename);

    void use(GLenum unit = GL_TEXTURE0);

    unsigned int getID();
};