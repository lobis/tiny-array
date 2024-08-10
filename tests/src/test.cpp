
#include <gtest/gtest.h>

#include <tiny_array/tiny_array.h>

#include <array>
#include <chrono>
#include <iostream>
#include <random>

using namespace std;
using namespace tiny_array;

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

TEST(TinyArray, RangeBasedForLoop) {
    const size_t resolution = 5;
    const size_t size = 20;

    array<unsigned int, size> data = {4, 2, 1, 3, 2, 1, 10, 8, 4, 2, 2, 1, 2, 1, 1, 11, 2, 3, 12, 10};

    const auto array = TinyArray<resolution, size>(data);

    int i = 0;
    for (const auto& value: array) {
        EXPECT_EQ(value, data.at(i++));
    }
}

TEST(TinyArray, ToArray) {
    const size_t resolution = 5;
    const size_t size = 20;

    array<unsigned int, size> data = {4, 2, 1, 3, 2, 1, 10, 8, 4, 2, 2, 1, 2, 1, 1, 11, 2, 3, 12, 10};

    const auto array = TinyArray<resolution, size>(data);

    EXPECT_EQ(array.size(), data.size());
    for (size_t i = 0; i < size; i++) {
        EXPECT_EQ(data.at(i), array.at(i));
    }
}

TEST(TinyArray, InitializerList) {
    TinyArray<4, 10>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
}

TEST(TinyArray, make_array) {
    make_array<4>(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
}

TEST(TinyArray, SizeComparison) {
    const size_t resolution = 14;
    const size_t size = 10000;
    using number_type = uint32_t;

    vector<number_type> data(size, 0);
    for (size_t i = 0; i < data.size(); i++) {
        data[i] = i;
    }

    const auto vector_size = sizeof(number_type) * data.size() + sizeof(data);

    const auto array = TinyArray<resolution, size>(data);

    const auto array_size = sizeof(array);

    EXPECT_LT(array_size, vector_size);
    EXPECT_EQ(vector_size, 40024);
    EXPECT_EQ(array_size, 17504);
}

TEST(TinyArray, TimeBenchmark) {
    const size_t resolution = 12;
    const size_t size = 1000000;
    using number_type = uint32_t;

    std::random_device rd;                                                      // Obtain a random seed from hardware
    std::mt19937 gen(rd());                                                     // Mersenne Twister engine with the seed
    std::uniform_int_distribution<number_type> dist(0, pow(2, resolution) - 1); // range 0 to 2^32 - 1

    vector<number_type> data(size, 0);
    for (unsigned int& entry: data) {
        // random between 0 and size
    }

    auto data_vector = data;
    auto data_tiny_array = TinyArray<resolution, size>(data);

    const auto vector_size = sizeof(number_type) * data.size() + sizeof(data_vector);
    const auto array_size = sizeof(data_tiny_array);

    auto start = chrono::high_resolution_clock::now();
    for (const auto& value: data_vector) {
        //
        auto result = value * 2;
    }
    auto vector_time = chrono::duration_cast<chrono::microseconds>(chrono::high_resolution_clock::now() - start).count();
    cout << "Vector read time: " << vector_time << " microseconds" << endl;

    // write all zeros
    start = chrono::high_resolution_clock::now();
    for (size_t i = 0; i < size; i++) {
        data_vector[i] = 0;
    }
    auto vector_write_time = chrono::duration_cast<chrono::microseconds>(chrono::high_resolution_clock::now() - start).count();
    cout << "Vector write time: " << vector_write_time << " microseconds" << endl;

    // measure time to iterate over the array
    start = chrono::high_resolution_clock::now();
    for (const auto& value: data_tiny_array) {
        //
        auto result = value * 2;
    }
    auto array_time = chrono::duration_cast<chrono::microseconds>(chrono::high_resolution_clock::now() - start).count();

    cout << "Array read time: " << array_time << " microseconds" << endl;

    // write all zeros
    start = chrono::high_resolution_clock::now();
    for (size_t i = 0; i < size; i++) {
        data_tiny_array.insert(i, 0);
    }
    auto array_write_time = chrono::duration_cast<chrono::microseconds>(chrono::high_resolution_clock::now() - start).count();
    cout << "Array write time: " << array_write_time << " microseconds" << endl;
}
