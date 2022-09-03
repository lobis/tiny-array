
#include <gtest/gtest.h>

#include <adc_array/library.h>

#include <iostream>

using namespace std;

TEST(ADCArray, Initialization) {
    const auto array = ADCArray();

    EXPECT_TRUE(array.GetData().empty());
}
