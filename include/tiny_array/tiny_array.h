#pragma once

#include <bitset>

template<std::size_t ResolutionInNumberOfBits = 12, std::size_t NumberOfElements = 512>
class TinyArray {
private:
    std::bitset<ResolutionInNumberOfBits * NumberOfElements> data;

public:
    inline constexpr TinyArray() = default;

    inline constexpr static std::size_t size() { return NumberOfElements; }

    inline constexpr static std::pair<std::size_t, std::size_t> GetRange() {
        unsigned int max = 1;
        for (std::size_t i = 0; i < ResolutionInNumberOfBits; i++) {
            max *= 2;
        }
        return {0, max - 1};
    }

    inline constexpr unsigned int at(size_t position) const {
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

    inline constexpr std::array<unsigned int, NumberOfElements> GetValues() const {
        std::array<unsigned int, NumberOfElements> result{};
        for (size_t i = 0; i < size(); i++) {
            result[i] = at(i);
        }
        return result;
    }

    inline constexpr void insert(size_t position, unsigned int value) {
        assert(position < size());
        assert(value <= GetRange().second);
        for (size_t i = 0; i < ResolutionInNumberOfBits; i++) {
            data[position * ResolutionInNumberOfBits + i] = value % 2;
            value /= 2;
        }
    }

    inline constexpr bool operator==(const TinyArray& rhs) const {
        return data == rhs.data;
    }

    inline constexpr bool operator!=(const TinyArray& rhs) const {
        return !(*this == rhs);
    }

    // Serialization
    using byte = unsigned char;
    inline constexpr std::array<byte, sizeof(data)> ToBytes() const {
        std::array<byte, sizeof(data)> bytes;

        const byte* begin = reinterpret_cast<const byte*>(std::addressof(data));
        std::copy(begin, begin + sizeof(data), std::begin(bytes));

        return bytes;
    }

    inline constexpr TinyArray<ResolutionInNumberOfBits, NumberOfElements> static FromBytes(const std::array<byte, sizeof(data)>& bytes) {
        auto array = TinyArray<ResolutionInNumberOfBits, NumberOfElements>();

        byte* begin = reinterpret_cast<byte*>(std::addressof(array.data));
        std::copy(std::begin(bytes), std::end(bytes), begin);

        return array;
    }

    // Other constructors
    inline constexpr TinyArray(const std::array<unsigned int, size()>& values) {
        for (size_t i = 0; i < values.size(); i++) {
            insert(i, values.at(i));
        }
    }

    inline constexpr TinyArray(const TinyArray& array) {
        data = array.data;
    }
};
