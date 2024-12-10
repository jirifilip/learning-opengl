#include <iostream>
#include <fstream>


void abortProgram(const std::string message) {
    std::cerr << message << std::endl;
    std::abort();
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
