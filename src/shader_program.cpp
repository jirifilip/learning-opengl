#include <vector>

#include "shader.h"
#include "shader_program.h"
#include "utils.h"
#include <gtc/type_ptr.hpp>


ShaderProgram::ShaderProgram(const std::vector<Shader>& shaders) : shaders(shaders) {
    internalID = glCreateProgram();

    for (auto& shader : shaders) {
        glAttachShader(internalID, shader.getID());
    }

    glLinkProgram(internalID);

    int success;
    char infoLog[512];

    glGetProgramiv(internalID, GL_LINK_STATUS, &success);

    if (!success) {
        glGetProgramInfoLog(internalID, 512, NULL, infoLog);
        abortProgram(std::string{ infoLog });
    }


    for (auto& shader : shaders) {
        glDeleteShader(shader.getID());
    }
}


void ShaderProgram::use() {
    glUseProgram(internalID);
}


unsigned int ShaderProgram::getID() {
    return internalID;
}


void ShaderProgram::setUniform(const std::string& name, float x, float y, float z, float alpha) {
    auto location = glGetUniformLocation(getID(), name.data());
    glUniform4f(location, x, y, z, alpha);
}


void ShaderProgram::setUniform(const std::string& name, int x) {
    auto location = glGetUniformLocation(getID(), name.data());
    glUniform1i(location, x);
}

void ShaderProgram::setUniform(const std::string &name, glm::mat4 matrix) {
    auto location = glGetUniformLocation(getID(), name.data());
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}
