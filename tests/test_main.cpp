#include "gtest/gtest.h"
#include "gmock/gmock.h"


TEST(Experiments, StreamIterators) {
    auto iterator = std::istreambuf_iterator<char>();  

    ASSERT_EQ(*iterator, '\xFF');
}