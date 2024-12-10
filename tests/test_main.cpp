#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <stb_image.h>


TEST(Experiments, StreamIterators) {
    auto iterator = std::istreambuf_iterator<char>();  

    ASSERT_EQ(*iterator, '\xFF');
}


TEST(Experiments, LoadImage) {
    int width, height, channelCount;
    
    unsigned char* image = stbi_load(
        "resources/wall.jpg",
        &width,
        &height,
        &channelCount,
        0
    );

    ASSERT_FALSE(image == nullptr);
    ASSERT_EQ(channelCount, 3);
    ASSERT_GE(width, 200);
    ASSERT_GE(height, 200);
}


TEST(Experiments, TestGLM) {
    glm::vec4 vector1{ 1, 0, 0, 1 };
    glm::mat4 translationMatrix = glm::translate(glm::mat4(1), glm::vec3(1, 1, 0));
    
    ASSERT_GE((translationMatrix * vector1).x, 1);
}