## adc_array

[![CMake](https://github.com/lobis/adc-array/actions/workflows/cmake.yml/badge.svg)](https://github.com/lobis/adc-array/actions/workflows/cmake.yml)

A simple library to work efficiently with n-bit digital data arrays typically produced by ADC units.

### Motivation

Let's say you are working with a sensor that has a 10 bit resolution, which means the data values range from 0 to 1023.

In order to store a sequence of this values one could use a `std::vector<unsigned short>`.
However, 4 bytes (16 bit) is the minimum amount of memory that needs to be allocated for each value, meaning we are
not being as efficient as possible with our memory.
This issue usually becomes more relevant if we are storing this data on disk.

This library provides a class, `ADCArray`, that allows to store the data in a more efficient way, using
a [`std::bitset`](https://en.cppreference.com/w/cpp/utility/bitset) behind the scenes.
In the above example a naive approach using `std::vector<unsigned short>` would require 4 bytes per value, while
with `ADCArray` we would only need 10 bits (1.25 bytes) per value on average.

Data can still be accessed in its original form via the `at` method or inserted via the `insert` method.
The drawback of this approach is that we introduce a small overhead when accessing or inserting the data.
The main motivation of this library is to improve disk storage efficiency.

### Installation

This library is header-only, so you can just copy the `include/adc_array` folder to your project.

### Usage

```cpp
# include "adc_array/adc_array.h"

const size_t resolutionInBits = 10;
const size_t numberOfElements = 4;

// use list initializer
auto adcArray = ADCArray<resolutionInBits, numberOfElements>({10, 0, 7, 4});
// or manually insert values
adcArray.insert(2, 7);

// values can be accessed individually
adcArray.at(2); // 7
// or be iterated through
for (const auto& value: adcArray.GetValues()){
    // value is of type 'unsigned int'
}
```

Memory usage vs `std::vector<unsigned short>`

```cpp
# include "adc_array/adc_array.h"

const size_t resolutionInBits = 10;
const size_t numberOfElements = 1000000; // 1E6

auto adcArray = ADCArray<resolutionInBits, numberOfElements>();

std::srand(0);
for (int i = 0; i < numberOfElements; ++i){
    adcArray.insert(i, rand() % 1024);
}

sizeof(adcArray); // 1250000 bytes

auto values = std::array<unsigned short, numberOfElements>{};
for (int i = 0; i < numberOfElements; ++i){
    values[i] = adcArray.at(i);
}

sizeof(values); // 2000000 bytes, 60% more memory usage
```

Serialization

```cpp
# include "adc_array/adc_array.h"

const size_t resolutionInBits = 10;
const size_t numberOfElements = 4;

// use list initializer
auto adcArray = ADCArray<resolutionInBits, numberOfElements>({10, 0, 7, 4});

const auto bytes = adcArray.ToBytes();

// save these bytes into disk

const auto adcArrayFromBytes = ADCArray<resolutionInBits, numberOfElements>::FromBytes(bytes);
```
