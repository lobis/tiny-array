## tiny_array

[![CMake](https://github.com/lobis/adc-array/actions/workflows/cmake.yml/badge.svg)](https://github.com/lobis/adc-array/actions/workflows/cmake.yml)

A simple library to work efficiently with n-bit digital data arrays typically produced by ADC units.

### Motivation

Let's say you are working with a sensor that has a 10 bit resolution, which means the data values range from 0 to 1023.

In order to store a sequence of this values one could use a `std::vector<unsigned short>`.
However, 4 bytes (16 bit) is the minimum amount of memory that needs to be allocated for each value, meaning we are
not being as efficient as possible with our memory.
This issue usually becomes more relevant if we are storing this data on disk.

This library provides a class, `TinyArray`, that allows to store the data in a more efficient way, using
a [`std::bitset`](https://en.cppreference.com/w/cpp/utility/bitset) behind the scenes.
In the above example a naive approach using `std::vector<unsigned short>` would require 4 bytes per value, while
with `TinyArray` we would only need 10 bits (1.25 bytes) per value on average.

Data can still be accessed in its original form via the `at` method or inserted via the `insert` method.
The drawback of this approach is that we introduce a small overhead when accessing or inserting the data.
The main motivation of this library is to improve disk storage efficiency.

### Installation

This library is header-only, so you can just copy the `include/tiny_array` folder to your project.

### Usage

```cpp
# include "tiny_array/tiny_array.h"

const size_t resolutionInBits = 10;
const size_t numberOfElements = 4;

// use list initializer
auto tinyArray = TinyArray<resolutionInBits, numberOfElements>({10, 0, 7, 4});
// or manually insert values
tinyArray.insert(2, 7);

// values can be accessed individually
tinyArray.at(2); // 7
// or be iterated through
for (const auto& value: tinyArray.GetValues()){
    // value is of type 'unsigned int'
}
```

Memory usage vs `std::vector<unsigned short>`

```cpp
# include "tiny_array/tiny_array.h"

const size_t resolutionInBits = 10;
const size_t numberOfElements = 1000000; // 1E6

auto tinyArray = TinyArray<resolutionInBits, numberOfElements>();

std::srand(0);
for (int i = 0; i < numberOfElements; ++i){
    tinyArray.insert(i, rand() % 1024);
}

sizeof(tinyArray); // 1250000 bytes

auto values = std::array<unsigned short, numberOfElements>{};
for (int i = 0; i < numberOfElements; ++i){
    values[i] = tinyArray.at(i);
}

sizeof(values); // 2000000 bytes, 60% more memory usage
```

Serialization

```cpp
# include "tiny_array/tiny_array.h"

const size_t resolutionInBits = 10;
const size_t numberOfElements = 4;

// use list initializer
auto tinyArray = TinyArray<resolutionInBits, numberOfElements>({10, 0, 7, 4});

const auto bytes = tinyArray.ToBytes();

// save these bytes into disk

const auto adcArrayFromBytes = TinyArray<resolutionInBits, numberOfElements>::FromBytes(bytes);
```
