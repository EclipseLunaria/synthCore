#include <gtest/gtest.h>
#include <osynth/structures/HistoryQueue.h>

const int TEST_QUEUE_SIZE = 16;
using namespace OSynthCore::Structures;
using CharQueue = HistoryQueue<char, 16>;
TEST(HistoryQueueTests, TestSinglePressRelease){
    CharQueue q = CharQueue();

    ASSERT_EQ(q.size(), 0);

    ASSERT_TRUE(q.press('k'));

    ASSERT_EQ(q.size(), 1);

    q.release('k');

    ASSERT_EQ(q.size(), 0);
}

TEST(HistoryQueueTests, TestReleaseUnpressedValue){
    CharQueue q = CharQueue();

    ASSERT_FALSE(q.release('i'));

    // check for when attempting to release when a value is already added
    q.press('k');

    ASSERT_FALSE(q.release('i'));
}

TEST(HistoryQueueTests, TestPressOnFullQueue){
    CharQueue q = CharQueue();

    for (int i = 0; i < TEST_QUEUE_SIZE; i++){
        ASSERT_TRUE(q.press('a' + i));
    }

    ASSERT_EQ(q.size(), TEST_QUEUE_SIZE);
    ASSERT_FALSE(q.press('z'));
}

TEST(HistoryQueueTests, TestPressDuplicateValue){
    CharQueue q = CharQueue();

    q.press('a');

    ASSERT_FALSE(q.press('a'));    
}

TEST(HistoryQueueTests, TestViewHistory){
    CharQueue q = CharQueue();
    char * buff[TEST_QUEUE_SIZE] = {nullptr};

    q.press('x');

    int n = q.view_history(buff);
    ASSERT_EQ(n, 1);

    ASSERT_EQ(*buff[0], 'x');
    ASSERT_EQ(buff[1], nullptr);

    q.press('y');
    q.press('z');

    n = q.view_history(buff);
    
    ASSERT_EQ(*buff[0], 'z');
    ASSERT_EQ(*buff[1], 'y');
    ASSERT_EQ(*buff[2], 'x');

    
    q.release('y');

    n = q.view_history(buff);

    ASSERT_EQ(n, 2);
    ASSERT_EQ(*buff[0], 'z');
    ASSERT_EQ(*buff[1], 'x');
    
    }

TEST(HistoryQueueTests, TestThreeKeyReleaseBug){
    auto q = CharQueue();

    ASSERT_TRUE(q.press('a'));
    ASSERT_EQ(*q.most_recent(), 'a');

    ASSERT_TRUE(q.press('s'));
    ASSERT_EQ(*q.most_recent(), 's');
    
    ASSERT_TRUE(q.press('d'));
    ASSERT_EQ(*q.most_recent(), 'd');

    ASSERT_TRUE(q.release('s'));
    ASSERT_EQ(*q.most_recent(), 'd');

    ASSERT_TRUE(q.release('d'));
    ASSERT_EQ(*q.most_recent(), 'a');
    ASSERT_TRUE(q.release('a'));

    ASSERT_EQ(q.most_recent(), nullptr);
}