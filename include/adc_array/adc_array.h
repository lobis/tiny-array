#pragma once

#include <bitset>
#include <vector>

template<std::size_t ResolutionInNumberOfBits = 12, std::size_t NumberOfElements = 512>
class ADCArray {
private:
    std::bitset<ResolutionInNumberOfBits * NumberOfElements> data;

public:
    inline constexpr std::size_t size() const { return NumberOfElements; }
    inline constexpr std::pair<std::size_t, std::size_t> GetRange() const {
        unsigned int max = 1;
        for (std::size_t i = 0; i < ResolutionInNumberOfBits; i++) {
            max *= 2;
        }
        return {0, max - 1};
    }

    inline unsigned int Get(size_t position) const {
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

    inline std::vector<unsigned int> GetValues() const {
        std::vector<unsigned int> result;
        for (size_t i = 0; i < size(); i++) {
            result.push_back(Get(i));
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
};
