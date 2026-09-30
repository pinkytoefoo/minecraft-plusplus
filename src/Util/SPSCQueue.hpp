#pragma once


#include <atomic>
#include <cstddef>
#include <new>
#include <array>

constexpr size_t k_CacheLineSize = std::hardware_destructive_interference_size;

template<typename T, size_t Capacity>
class SPSCQueue
{
public:
    static_assert(Capacity > 0 && (Capacity & (Capacity - 1)) == 0, "Capacity must be a power of 2");

    bool Push(const T& item)
    {
        size_t head = m_Head.load(std::memory_order_relaxed);
        if((head - m_Tail.load(std::memory_order_acquire)) == Capacity)
        {
            // todo: signal that queue is full
            return false;
        }

        m_Buffer[head & k_Mask] = item;
        m_Head.store(head + 1, std::memory_order_release);

        return true;
    }

    bool Pop(T& item)
    {
        size_t tail = m_Tail.load(std::memory_order_relaxed);
        if(tail == m_Head.load(std::memory_order_acquire))
        {
            return false; // queue empty
        }

        item = m_Buffer[tail & k_Mask];
        m_Tail.store(tail + 1, std::memory_order_release);
        return true;
    }

private:
    static constexpr size_t k_Mask = Capacity - 1;
    std::array<T, Capacity> m_Buffer;
    alignas(k_CacheLineSize) std::atomic<size_t> m_Head;
    alignas(k_CacheLineSize) std::atomic<size_t> m_Tail;
};
