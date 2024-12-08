#include <iostream>
#include <fstream>

#include <glad.c>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <memory>
#include <functional>


void abortProgram(const std::string message) {
    std::cerr << message << std::endl;
    std::abort();
}


void processInput(GLFWwindow* window) {
    auto keyStatus = glfwGetKey(window, GLFW_KEY_ESCAPE);
    
    if (keyStatus == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}


std::string readFileContent(const std::string fileName) {
    std::ifstream inputFileStream{ fileName };
    // TODO: look more into how this std::string constructor from range works 
    std::string content {
        std::istreambuf_iterator<char>{ inputFileStream },
        std::istreambuf_iterator<char>()
    };

    return content;
}


class Shader {
private:
    std::string filename;
    unsigned int type;
    const std::string code;
    const char* internalCode;
    unsigned int internalID;

    void compile() {
        internalID = glCreateShader(type);

        glShaderSource(internalID, 1, &internalCode, NULL);
        glCompileShader(internalID);

        checkCompilationSuccess();        
    }

    void checkCompilationSuccess() {
        int success;
        char infoLog[512];
        glGetShaderiv(internalID, GL_COMPILE_STATUS, &success);

        if (!success) {
            glGetShaderInfoLog(internalID, 512, NULL, infoLog);
            abortProgram(std::string{ infoLog });
        }
    }

public:
    Shader(const std::string filename, unsigned int type = GL_VERTEX_SHADER) 
        : 
        filename { filename },
        type { type }, 
        code { readFileContent(filename) },
        internalCode { code.data() } {
            std::cout << "Shader: " << filename << std::endl;
            compile();
        }

    unsigned int getID() const {
        return internalID;
    }
};


class ShaderProgram {
private:
    unsigned int internalID;
    const std::vector<Shader>& shaders;

public:
    ShaderProgram(const std::vector<Shader>& shaders) : shaders(shaders) {
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

    void use() {
        glUseProgram(internalID);
    }
};


typedef std::function<void(GLFWwindow*)> GLFWWindowDeleter;

class GLFW {
public:
    GLFW() {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    }

    ~GLFW() {
        glfwTerminate();
    }

    std::unique_ptr<GLFWwindow, GLFWWindowDeleter> createWindow() {
        GLFWwindow* rawWindow = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);

        if (rawWindow == nullptr) {
            abortProgram("Failed to initialize window");
        }

        return std::unique_ptr<GLFWwindow, GLFWWindowDeleter>(
            rawWindow,
            [](GLFWwindow* rawWindow) {
                if (rawWindow != nullptr) {
                 glfwDestroyWindow(rawWindow);
                }   
            }    
        );
    } 

    void setCurrent(GLFWwindow* window) {
        glfwMakeContextCurrent(window);
    }
};


void loadGLAD() {
    auto success = gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
    if (!success) {
        abortProgram("Failed to initialize GLAD");
    }
}


int main() {
    auto glfw = GLFW();
    auto window = glfw.createWindow();
    glfw.setCurrent(window.get());

    // TODO: explore further
    loadGLAD();

    glViewport(0, 0, 800, 600);


    float vertices[] { 
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f,
    };
    
    Shader vertexShader{ "src/shader.vert", GL_VERTEX_SHADER };
    Shader fragmentShader { "src/shader.frag", GL_FRAGMENT_SHADER };
    std::vector shaders { vertexShader, fragmentShader };
    
    ShaderProgram program { shaders };


    unsigned int vertexBufferID, vertexArrayID;
    glGenVertexArrays(1, &vertexArrayID);
    glGenBuffers(1, &vertexBufferID);

    glBindVertexArray(vertexArrayID);

    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(vertices),
        vertices,
        GL_STATIC_DRAW
    );

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);
    glEnableVertexAttribArray(0);
    
    while (!glfwWindowShouldClose(window.get())) {
        glfwSwapBuffers(window.get());

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        program.use();
        glBindVertexArray(vertexArrayID);
        glDrawArrays(GL_TRIANGLES, 0, 3);
     
        glfwPollEvents();
        processInput(window.get());
    }

    return 0;
}