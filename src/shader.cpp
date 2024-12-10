#include <iostream>
#include <glad/glad.h>

#include <shader.h>
#include <utils.h>


void Shader::compile() {
    internalID = glCreateShader(type);

    glShaderSource(internalID, 1, &internalCode, NULL);
    glCompileShader(internalID);

    checkCompilationSuccess();        
}

void Shader::checkCompilationSuccess() {
    int success;
    char infoLog[512];
    glGetShaderiv(internalID, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(internalID, 512, NULL, infoLog);
        abortProgram(std::string{ infoLog });
    }
}


Shader::Shader(const std::string& filename, unsigned int type) 
    : 
    filename { filename },
    type { type }, 
    code { readFileContent(filename) },
    internalCode { code.data() } {
        std::cout << "Shader: " << filename << std::endl;
        compile();
    }


unsigned int Shader::getID() const {
    return internalID;
}