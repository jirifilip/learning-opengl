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


TEST(Experiments, TestIdentityMatrix) {
    auto identity = glm::mat4(1);

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            auto value = identity[i][j];
            if (i == j) {
                ASSERT_EQ(value, 1);
            } else {
                ASSERT_EQ(value, 0);
            }
        }
    }
}


TEST(Experiments, TestTranslationMatrix) {
    glm::vec4 vector1{ 1, 0, 0, 1 };
    glm::mat4 translationMatrix = glm::translate(glm::mat4(1), glm::vec3(1, 1, 0));

    auto translatedVector = translationMatrix * vector1;
    
    ASSERT_EQ(translatedVector.x, 2);
    ASSERT_EQ(translatedVector.y, 1);
    ASSERT_EQ(translatedVector.z, 0);
    ASSERT_EQ(translatedVector.w, 1);
}


TEST(Experiments, TestMultipleTransformations) {
    glm::mat4 identity = glm::mat4(1);
    auto rotated = glm::rotate(identity, glm::radians(90.0f), glm::vec3(0, 0, 1));
    [[maybe_unused]] auto scaled = glm::scale(rotated, glm::vec3(0.5, 0.5, 0.5));
}