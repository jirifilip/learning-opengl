#include "gtest/gtest.h"
#include "gmock/gmock.h"

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