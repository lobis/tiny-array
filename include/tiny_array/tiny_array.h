#pragma once

#include <bitset>

template<std::size_t ResolutionInNumberOfBits = 12, std::size_t NumberOfElements = 512>
class TinyArray {
private:
    typedef unsigned long long number_type;

    std::bitset<ResolutionInNumberOfBits * NumberOfElements> data;

public:
    inline constexpr TinyArray() = default;

    inline constexpr static std::size_t size() { return NumberOfElements; }

    inline constexpr static std::pair<std::size_t, std::size_t> range() {
        return {0, (1 << ResolutionInNumberOfBits) - 1};
    }

    inline constexpr number_type at(size_t position) const {
        if (position >= size()) {
            throw std::out_of_range("Index out of range");
        }

        // Calculate the starting bit index for the element at the given position
        size_t startBit = position * ResolutionInNumberOfBits;

        // Extract the bits corresponding to the value
        number_type result = 0;
        for (size_t i = 0; i < ResolutionInNumberOfBits; ++i) {
            if (data[startBit + i]) {
                result |= (1U << i);
            }
        }

        return result;
    }

    inline constexpr std::array<number_type, NumberOfElements> GetValues() const {
        std::array<number_type, NumberOfElements> result{};
        for (size_t i = 0; i < size(); i++) {
            result[i] = at(i);
        }
        return result;
    }

    inline constexpr void insert(size_t position, number_type value) {
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

    // Initialize from an iterable
    template<typename Iterable>
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
