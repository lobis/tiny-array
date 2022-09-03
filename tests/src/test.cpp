
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
        EXPECT_EQ(array.GetValue(pair.first), 0);
        array.Insert(pair.first, pair.second);
        EXPECT_EQ(array.GetValue(pair.first), pair.second);
    }

    for (const auto& pair: positionValueList) {
        EXPECT_EQ(array.GetValue(pair.first), pair.second);
    }
}

TEST(ADCArray, Bytes) {
    const size_t resolution = 4;
    const size_t size = 10;

    const auto array = ADCArray<resolution, size>({4, 2, 1, 3, 2, 1, 10, 8, 4, 2});
    EXPECT_EQ(array.GetValue(0), 4);

    const auto bytes = array.ToBytes();

    const auto arrayFromBytes = ADCArray<resolution, size>::FromBytes(bytes);
    EXPECT_EQ(arrayFromBytes.GetValue(0), 4);
}
