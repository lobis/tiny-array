#pragma once

#include <bitset>
#include <vector>

template<std::size_t ResolutionInNumberOfBits = 12, std::size_t NumberOfElements = 512>
class ADCArray {
private:
    std::bitset<ResolutionInNumberOfBits * NumberOfElements> data;

public:
    ADCArray() = default;

    inline constexpr static std::size_t size() { return NumberOfElements; }

    inline constexpr static std::pair<std::size_t, std::size_t> GetRange() {
        unsigned int max = 1;
        for (std::size_t i = 0; i < ResolutionInNumberOfBits; i++) {
            max *= 2;
        }
        return {0, max - 1};
    }

    inline unsigned int GetValue(size_t position) const {
        assert(position < size());
        unsigned int result = 0;
        unsigned int powerOf2 = 1;
        for (size_t i = 0; i < ResolutionInNumberOfBits; i++) {
            if (data[position * ResolutionInNumberOfBits + i]) {
                result += powerOf2;
            }
            powerOf2 *= 2;
        }
        return result;
    }

    inline std::array<unsigned int, NumberOfElements> GetValues() const {
        std::array<unsigned int, NumberOfElements> result{};
        for (size_t i = 0; i < size(); i++) {
            result[i] = GetValue(i);
        }
        return result;
    }

    inline void Insert(size_t position, unsigned int value) {
        assert(position < size());
        assert(value <= GetRange().second);
        for (size_t i = 0; i < ResolutionInNumberOfBits; i++) {
            data[position * ResolutionInNumberOfBits + i] = value % 2;
            value /= 2;
        }
    }

    // Serialization
    using byte = unsigned char;
    inline std::array<byte, sizeof(data)> ToBytes() const {
        std::array<byte, sizeof(data)> bytes;

        const byte* begin = reinterpret_cast<const byte*>(std::addressof(data));
        std::copy(begin, begin + sizeof(data), std::begin(bytes));

        return bytes;
    }

    ADCArray<ResolutionInNumberOfBits, NumberOfElements> static FromBytes(const std::array<byte, sizeof(data)>& bytes) {
        auto array = ADCArray<ResolutionInNumberOfBits, NumberOfElements>();

        byte* begin = reinterpret_cast<byte*>(std::addressof(array.data));
        std::copy(std::begin(bytes), std::end(bytes), begin);

        return array;
    }

    // Other constructors
    ADCArray(const std::array<unsigned int, size()>& values) {
        for (size_t i = 0; i < values.size(); i++) {
            Insert(i, values.at(i));
        }
    }

    ADCArray(const ADCArray& array) {
        data = array.data;
    }
};
