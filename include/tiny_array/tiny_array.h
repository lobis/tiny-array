#pragma once

#include <bitset>

template<std::size_t ResolutionInNumberOfBits = 12, std::size_t NumberOfElements = 512>
class TinyArray {
private:
    std::bitset<ResolutionInNumberOfBits * NumberOfElements> data;

public:
    inline constexpr TinyArray() = default;

    inline constexpr static std::size_t size() { return NumberOfElements; }

    inline constexpr static std::pair<std::size_t, std::size_t> range() {
        return {0, (1 << ResolutionInNumberOfBits) - 1};
    }

    inline constexpr unsigned int at(size_t position) const {
        if (position >= size()) {
            throw std::out_of_range("Index out of range");
        }

        // Calculate the starting bit index for the element at the given position
        size_t startBit = position * ResolutionInNumberOfBits;

        // Extract the bits corresponding to the value
        unsigned int result = 0;
        for (size_t i = 0; i < ResolutionInNumberOfBits; ++i) {
            if (data[startBit + i]) {
                result |= (1U << i);
            }
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
        if (position >= size()) {
            throw std::out_of_range("Index out of range");
        }
        if (value > range().second) {
            throw std::out_of_range("Value out of range");
        }

        size_t startBit = position * ResolutionInNumberOfBits;
        for (size_t i = 0; i < ResolutionInNumberOfBits; i++) {
            data[startBit + i] = (value >> i) & 1U;
        }
    }

    inline constexpr bool operator==(const TinyArray& rhs) const {
        return data == rhs.data;
    }

    inline constexpr bool operator!=(const TinyArray& rhs) const {
        return *this != rhs;
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

    // Initialize from an iterable
    template <typename Iterable>
    inline constexpr explicit TinyArray(const Iterable& values) {
        size_t i = 0;
        for (auto it = values.begin(); it != values.end() && i < size(); ++it, ++i) {
            insert(i, *it);
        }
    }

    // Copy constructor
    inline constexpr TinyArray(const TinyArray& array) {
        data = array.data;
    }
};
