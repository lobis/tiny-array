
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
        EXPECT_EQ(array.Get(pair.first), 0);
        array.Insert(pair.first, pair.second);
        EXPECT_EQ(array.Get(pair.first), pair.second);
    }

    for (const auto& pair: positionValueList) {
        EXPECT_EQ(array.Get(pair.first), pair.second);
    }
}
