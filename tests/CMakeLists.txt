# Test suite CMake File
include(FetchContent)

# Enable testing for OSynth
enable_testing()

# Fetch Google Tests
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.18.0.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Test Sources
set(synthTestSources
    OscillatorTests.cpp
    ConfigTests.cpp
    )
add_executable(testSynthCore ${synthTestSources}
    structures/HistoryQueueTests.cpp)

target_link_libraries(
    testSynthCore
    PRIVATE
    synthCore
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(testSynthCore)

# Restore Exceptions and RTTI for testing
if(MSVC)
    target_compile_options(synthCore PRIVATE
        /EH # Disable Exceptions
        /GR    # Disable RTTI
    )
    # turn off exceptions in the Microsoft Standard Library (STL)
    target_compile_definitions(synthCore PRIVATE _HAS_EXCEPTIONS=1)
endif()
add_subdirectory(SPSCQueue)
