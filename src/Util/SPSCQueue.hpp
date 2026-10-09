#pragma once

#include <atomic>
#include <cstddef>
#include <new>
#include <array>

template<typename T, size_t Capacity>
class SPSCQueue
{
public:
    static_assert(Capacity > 0 && (Capacity & (Capacity - 1)) == 0, "Capacity must be a power of 2");

    bool push(const T& item)
    {
        size_t head = head_.load(std::memory_order_relaxed);
        if((head - tail_.load(std::memory_order_acquire)) == Capacity)
        {
            // todo: signal that queue is full
            return false;
        }

        buffer_[head & kMask] = item;
        head_.store(head + 1, std::memory_order_release);

        return true;
    }

    bool pop(T& item)
    {
        size_t tail = tail_.load(std::memory_order_relaxed);
        if(tail == head_.load(std::memory_order_acquire))
        {
            return false; // queue empty
        }

        item = buffer_[tail & kMask];
        tail_.store(tail + 1, std::memory_order_release);
        return true;
    }

private:
    static constexpr size_t kMask = Capacity - 1;

#ifdef __cpp_lib_hardware_interference_size
    static constexpr size_t kCacheLineSize = std::hardware_destructive_interference_size;
#else
    constexpr size_t kCacheLineSize = 64;
#endif

    alignas(kCacheLineSize) std::atomic<size_t> head_{0};
    alignas(kCacheLineSize) std::atomic<size_t> tail_{0};
    std::array<T, Capacity> buffer_;
};
