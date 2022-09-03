
#include <gtest/gtest.h>

#include <adc_array/adc_array.h>

#include <iostream>

using namespace std;

TEST(ADCArray, Info) {
    const size_t size = 100;
    auto array = ADCArray<12, size>();
    EXPECT_EQ(array.size(), size);
    EXPECT_EQ(array.GetRange().first, 0);
    EXPECT_EQ(array.GetRange().second, 4095);
}

TEST(ADCArray, InsertionAndRetrieval) {
    auto array = ADCArray<4, 100>();

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

TEST(ADCArray, ToArray) {
    const size_t resolution = 5;
    const size_t size = 10;

    array<unsigned int, size> data = {4, 2, 1, 5, 2, 1, 15, 8, 22, 2};

    const auto array = ADCArray<resolution, size>(data);

    const auto arrayData = array.GetValues();
    EXPECT_EQ(arrayData.size(), size);
    for (size_t i = 0; i < size; i++) {
        EXPECT_EQ(arrayData.at(i), array.at(i));
    }
}

TEST(ADCArray, Bytes) {
    const size_t resolution = 4;
    const size_t size = 20;

    array<unsigned int, size> data = {4, 2, 1, 3, 2, 1, 10, 8, 4, 2, 2, 1, 2, 1, 1, 11, 2, 3, 12, 10};

    const auto array = ADCArray<resolution, size>(data);

    for (size_t i = 0; i < size; i++) {
        EXPECT_EQ(array.at(i), data.at(i));
    }

    const auto bytes = array.ToBytes();

    const auto arrayFromBytes = ADCArray<resolution, size>::FromBytes(bytes);

    for (size_t i = 0; i < size; i++) {
        EXPECT_EQ(arrayFromBytes.at(i), data.at(i));
    }

    // Check operator == works
    EXPECT_EQ(array, arrayFromBytes);
    const auto arrayEmpty = ADCArray<resolution, size>();
    EXPECT_TRUE(array != arrayEmpty);
}
