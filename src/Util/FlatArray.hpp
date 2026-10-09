#pragma once

#include <cstddef>
#include <cassert>
#include <concepts>

// might need to make a flatvector
template<typename T, size_t Size>
class FlatArray
{
public:
    static_assert(Size > 0);

    constexpr size_t size() const noexcept { return Capacity; }

    constexpr const T& operator[](size_t idx) const noexcept {
        return begin_[idx];
    }

    constexpr T& operator[](int x, int y, int z) noexcept {
        // assert(x < Size);
        // assert(y < Size);
        // assert(z < Size);
        return begin_[x + Size * (y + Size * z)];
    }
    constexpr const T& operator[](int x, int y, int z) const noexcept {
        // assert(x < Size);
        // assert(y < Size);
        // assert(z < Size);
        return begin_[x + Size * (y + Size * z)];
    }

    // template<typename I>
    // requires std::integral<I>
    // constexpr T& operator[](I x, I y, I z) noexcept {
    //     return begin_[x + k_Size * (y + k_Size * z)];
    // }
    // template<typename I>
    // requires std::integral<I>
    // constexpr const T& operator[](I x, I y, I z) const noexcept {
    //     return begin_[x + k_Size * (y + k_Size * z)];
    // }

    constexpr T* data() noexcept { return begin_; }
    constexpr const T* data() const noexcept { return begin_; }

    constexpr T* begin() noexcept { return begin_; }
    constexpr const T* begin() const noexcept { return begin_; }
    constexpr T* end() noexcept { return begin_ + Capacity; }
    constexpr const T* end() const noexcept { return begin_ + Capacity; }

    void fill(const T& value) {
        for(size_t i{}; i < Capacity; ++i) {
            begin_[i] = value;
        }
    }

private:
    static constexpr auto Capacity = Size * Size * Size;
    T begin_[Capacity]{};
};
