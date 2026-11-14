#include <gtest/gtest.h>

#include "osynth/structures/SPSCQueue.h"
using namespace OSynth::Core::Structures;

// Test 1000 reads and writes on a single thread
TEST(SPSCQueueTests, TestPushPopAboveCapacityOnSingleThread){
    const int capacity = 64;
    SPSCQueue<int, capacity> queue;
    std::optional<int> val;
    for (int i = 0; i < 2*capacity; i++){
        queue.push(i);
        val = queue.pop();
    }

    ASSERT_EQ(val.value(), capacity * 2 - 1);

}


// Test push when queue is full
TEST(SPSCQueueTests, TestPushFullQueue){
    const int capacity = 16;
    SPSCQueue<int, capacity> queue;
    for (int i = 0; i < capacity; i++) {
        ASSERT_TRUE(queue.push(i));
    }
    ASSERT_FALSE(queue.push(capacity));
}


// Test pop when queue is empty
TEST(SPSCQueueTests, TestPopEmptyQueue){
    const int capacity = 64;
    SPSCQueue<int, capacity> queue;
    auto value = queue.pop();
    ASSERT_EQ(value, std::nullopt);
}

