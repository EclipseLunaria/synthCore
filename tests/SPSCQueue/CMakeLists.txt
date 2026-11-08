set(SPSCQueueSources
    ${CMAKE_CURRENT_LIST_DIR}/SPSCQueueTests.cpp
    )

add_executable(testSPSCQueue ${SPSCQueueSources})

target_link_libraries(
    testSPSCQueue
    PRIVATE
    synthCore
    GTest::gtest_main
    )

gtest_discover_tests(testSPSCQueue)