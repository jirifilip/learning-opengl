#include <iostream>
#include <memory>
#include <functional>

#include <glad/glad.h>
#include <stb_image.h>

#include "texture.h"
#include "utils.h"


std::unique_ptr<unsigned char, std::function<void(unsigned char*)>> Texture::loadImage(const std::string& filename) {
    auto pixelValues = std::unique_ptr<unsigned char, std::function<void(unsigned char*)>>(
        stbi_load(filename.data(), &width, &height, &channels, 0),
        [](unsigned char* pixelValues) {
            stbi_image_free(pixelValues);
        }
    );

    if (!pixelValues.get()) {
        abortProgram("Could not load texture image: " + filename);
    }

    return pixelValues;
}


Texture::Texture(const std::string& filename) {
    auto pixelValues = loadImage(filename);

    glGenTextures(1, &internalID);
    glBindTexture(GL_TEXTURE_2D, internalID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    glTexImage2D(
        GL_TEXTURE_2D, 
        0, 
        GL_RGB,
        width,
        height, 
        0,
        channels == 3 ? GL_RGB : GL_RGBA,
        GL_UNSIGNED_BYTE,
        pixelValues.get()
    );
    glGenerateMipmap(GL_TEXTURE_2D);
}


void Texture::use(GLenum unit) {
    glActiveTexture(unit);
    glBindTexture(GL_TEXTURE_2D, getID());
}


unsigned int Texture::getID() {
    return internalID;
}
