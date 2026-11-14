#pragma once
#include <atomic>
#include <concepts>
#include <cstddef>
#include <optional>
#ifndef OSYNTH_CACHE_LINE_SIZE
#define OSYNTH_CACHE_LINE_SIZE 64
#endif

namespace OSynth::Core::Structures {
    template <typename T, size_t Capacity>
    class SPSCQueue {
        // Ensure capacity is power of two
        static_assert( 
            (Capacity != 0) && ((Capacity & (Capacity - 1)) == 0),
            "Capacity must be a power of two for optimal routing."           
        );
        static_assert(std::is_trivially_copyable<T>());
        
        private:
        // Standard hardware cache lines size (usually 64 or 128 bytes)
        static constexpr size_t CacheLineSize = OSYNTH_CACHE_LINE_SIZE;


        // --- PRODUCER CACHE LINE ---
        // Pmly the producer modifies m_tail. The consumer reads it
        alignas(CacheLineSize)
        std::atomic<size_t>m_tail{0};

        // The producer's private, non_atomic copy of the m_head
        // This prevents the producer from having to constanly hit the atomic m_head
        size_t m_cached_head_for_producer{0};


        // --- Consumer Cache Line ---
        // Only the consumer modifies m_head. The producer reads it.
        alignas(CacheLineSize)
        std::atomic<size_t> m_head{0};

        // The consumer's private, non-atomic copy of the tail.
        size_t m_cached_tail_for_consumer{0};

        // --- DATA PAYLOAD CACHE LINE ---
        // The actual ring buffer isolated on its own cache boundary.
        alignas(CacheLineSize)
        T m_buffer[Capacity];

        public:
        SPSCQueue() = default;

        // disallowing copying to prevent accidental memory corruption
        SPSCQueue(const SPSCQueue&) = delete;
        SPSCQueue& operator=(const SPSCQueue&) = delete;

        bool push(const T& item) {
            // Read our local, non-atomic tail value.
            const size_t current_tail = m_tail.load(std::memory_order_relaxed);
            // Calculate the distance to our locally cached head
            if(current_tail - m_cached_head_for_producer == Capacity){
                // Our local cache says the buffer is full. We must double check the
                // actual atomic head to see if the consumer has freed up space.
                // We use memory_order_aquire to establish a synchronization point.
                m_cached_head_for_producer = m_head.load(std::memory_order_acquire);
                // If it is still full after checking the real head, we fail the push.
                if (current_tail - m_cached_head_for_producer == Capacity) {
                    return false;
                }
            }

            // We have space. Write the item to the array using the bitwise AND mask
            m_buffer[current_tail & (Capacity - 1)] = item;

            // Publish the new tail to the consumer.
            // memory_order_release guarentees the item is fully written to the array.
            // before the tail index increments, preventing the consumer from reading garbage.
            m_tail.store(current_tail + 1, std::memory_order_release);
            return true;
        }

        std::optional<T> pop(){
            // Read our local, non-atomic head value
            const size_t current_head = m_head.load(std::memory_order_relaxed);

            // Check against our locally cached tail to see if there is data
            if(current_head == m_cached_tail_for_consumer) {
                // Our local cache says the buffer is empty. We double-check the real tail.
                // We use memory_order_acquire to ensure we see all producer's data writes.
                m_cached_tail_for_consumer = m_tail.load(std::memory_order_acquire);
                // if it is still empty, return nothing
                if (current_head == m_cached_tail_for_consumer) {
                    return std::nullopt;
                }
            }

            // We have data. Read it from the array using the bitwise AND mask.
            T extracted_item = m_buffer[current_head&(Capacity - 1)];

            // Update the head, notifying the producer that a slot is free,
            // memory_order_release guarantees the item is fully read out of the array
            // before the producer is allowed to overwrite that index.
            m_head.store(current_head+1, std::memory_order_release);
            return extracted_item;
        }

    };
}