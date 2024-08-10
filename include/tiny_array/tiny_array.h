#pragma once

#include <bitset>
#include <initializer_list>

namespace tiny_array {

using resolution_type = unsigned short;
template<resolution_type ResolutionInNumberOfBits, std::size_t NumberOfElements>
class TinyArray {
    using number_type = unsigned long long;
    static_assert(ResolutionInNumberOfBits <= sizeof(number_type) * 8,
                  "ResolutionInNumberOfBits exceeds the number of bits available in unsigned long long");

private:
    std::bitset<ResolutionInNumberOfBits * NumberOfElements> data;

public:
    inline constexpr TinyArray() = default;

    inline constexpr static std::size_t size() { return NumberOfElements; }

    inline constexpr static std::pair<std::size_t, std::size_t> range() {
        return {0, (1ULL << ResolutionInNumberOfBits) - 1};
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

    inline constexpr void insert(size_t position, number_type value) {
        if (position >= size()) {
            throw std::out_of_range("Index " + std::to_string(position) + " out of range for size " + std::to_string(size()));
        }
        if (value > range().second) {
            throw std::out_of_range("Value " + std::to_string(value) + " out of range for resolution " + std::to_string(ResolutionInNumberOfBits) + " bits. Max value is " + std::to_string(range().second));
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
        return !(*this == rhs);
    }

    // Initialize from an iterable
    template<typename Iterable>
    inline constexpr explicit TinyArray(const Iterable& values) {
        size_t i = 0;
        for (auto it = values.begin(); it != values.end() && i < size(); ++it, ++i) {
            insert(i, *it);
        }
    }

    inline constexpr number_type operator[](size_t position) const {
        return at(position);
    }

private:
    template<typename T>
    inline void constexpr InitializeFromInitializerList(std::initializer_list<T> values) {
        static_assert(std::is_convertible<T, number_type>::value, "Initializer list element type must be convertible to number_type");

        if (values.size() > size()) {
            throw std::out_of_range("Initializer list size exceeds the number of elements in the array");
        }

        size_t i = 0;
        for (const auto value: values) {
            insert(i++, value);
        }
    }

public:
    // Constructor to initialize from an initializer list
    inline constexpr TinyArray(std::initializer_list<number_type> values) {
        InitializeFromInitializerList(values);
    }

    // Explicitly initialize from an initializer list of integers to avoid warnings
    inline constexpr TinyArray(std::initializer_list<int> values) {
        InitializeFromInitializerList(values);
    }

    // Copy constructor
    inline constexpr TinyArray(const TinyArray& array) {
        data = array.data;
    }

    class Iterator {
    private:
        const TinyArray* array;
        std::size_t position;

    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = number_type;
        using difference_type = std::ptrdiff_t;
        using pointer = const number_type*;
        using reference = number_type;

        Iterator(const TinyArray* arr, std::size_t pos) : array(arr), position(pos) {}

        // Dereference operator
        number_type operator*() const {
            return array->at(position);
        }

        // Increment operator
        Iterator& operator++() {
            ++position;
            return *this;
        }

        // Equality operator
        bool operator==(const Iterator& other) const {
            return position == other.position;
        }

        // Inequality operator
        bool operator!=(const Iterator& other) const {
            return position != other.position;
        }
    };

    inline constexpr Iterator begin() const {
        return Iterator(this, 0);
    }

    inline constexpr Iterator end() const {
        return Iterator(this, size());
    }
};

// method to create an array without explicitly specifying the number of elements - https://stackoverflow.com/questions/26351587/how-to-create-stdarray-with-initialization-list-without-providing-size-directl
template<resolution_type resolution, typename... N>
auto make_array(N&&... args) -> TinyArray<resolution, sizeof...(args)> {
    return {std::forward<N>(args)...};
}

} // namespace tiny_array
