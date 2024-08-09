
#include <gtest/gtest.h>

#include <tiny_array/tiny_array.h>

#include <array>
#include <iostream>

using namespace std;

TEST(TinyArray, Info) {
    const size_t size = 100;
    auto array = TinyArray<12, size>();
    EXPECT_EQ(array.size(), size);
    EXPECT_EQ(array.range().first, 0);
    EXPECT_EQ(array.range().second, 4095);
}

TEST(TinyArray, InsertionAndRetrieval) {
    auto array = TinyArray<4, 100>();

    // values should be unique
    vector<pair<size_t, size_t>> positionValueList = {{0, 3}, {3, 5}, {1, 11}, {2, 15}};

    for (const auto& pair: positionValueList) {
        EXPECT_EQ(array.at(pair.first), 0);
        array.insert(pair.first, pair.second);
        EXPECT_EQ(array.at(pair.first), pair.second);
    }

    for (const auto& pair: positionValueList) {
        EXPECT_EQ(array.at(pair.first), pair.second);
    }
}

TEST(TinyArray, ToArray) {
    const size_t resolution = 5;
    const size_t size = 20;

    array<unsigned int, size> data = {4, 2, 1, 3, 2, 1, 10, 8, 4, 2, 2, 1, 2, 1, 1, 11, 2, 3, 12, 10};

    const auto array = TinyArray<resolution, size>(data);

    const auto arrayData = array.GetValues();
    EXPECT_EQ(arrayData.size(), size);
    for (size_t i = 0; i < size; i++) {
        EXPECT_EQ(arrayData.at(i), array.at(i));
    }
}
