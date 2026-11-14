cmake_minimum_required(VERSION 3.31)
project (OSynthCore VERSION 1.0)
# Configure and build core static library

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Setup configuration config values
set(availableProfiles full lite custom)
set(profileVars MAX_VOICES MAX_BLOCK_SIZE WAVETABLE_LENGTH OVERSAMPLING_FACTOR COMMAND_QUEUE_SIZE)

set(coreSources 
    src/oscillator.cpp
    src/config.cpp
    src/gain.cpp
    src/smoothableFloat.cpp
    src/engine.cpp
    include/osynth/structures/HistoryQueue.h
) 

set(OSYNTH_PROFILE "$CACHE{OSYNTH_PROFILE}" CACHE STRING "Build profile")
set_property(CACHE OSYNTH_PROFILE PROPERTY STRINGS ${availableProfiles})

foreach(profileVar IN LISTS profileVars)
    set(${profileVar} "$CACHE{${profileVar}}" CACHE STRING "Custom profile override for ${profileVar}")
endforeach()

# Retrieve build profile
message("profile selected ${OSYNTH_PROFILE}")

if (NOT BUILD_PROFILE)
    message("Build Profile not selected, defaulting to full profile")
    set(BUILD_PROFILE "full")
else()
#build profile defined
    set(profileFound NO)
    foreach(profile IN LISTS availableProfiles)
        if(BUILD_PROFILE STREQUAL ${profile})
            set(profileFound YES)
        endif()
    endforeach()
    if(NOT profileFound)
        message(FATAL_ERROR "profile ${BUILD_PROFILE} is not valid")
    endif()
endif()


# CACHE LINE OPTIMIZATION
# If the target uses a cache line of less than 64 bytes
# such as ARM chips. you may set the cache line size below.

# Cache line size defaults to 32 if building under lite configuration
if (${BUILD_PROFILE} STREQUAL "lite")
    add_compile_definitions(OSynthCore PUBLIC OSYNTH_CACHE_LINE_SIZE=32)
endif()

# The Core static library holding all the DSP code.
# For now its public interface does one thing report:
# its version, the active profile name and that profiles limits.

add_library(synthCore STATIC ${coreSources})
target_include_directories(synthCore PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_definitions(synthCore PUBLIC BUILD_PROFILE="${BUILD_PROFILE}")

# Set config for custom configuration
if(BUILD_PROFILE STREQUAL "custom")
    foreach(profileVar IN LISTS profileVars)
        set(profileValue "${${profileVar}}")
        if(NOT profileValue STREQUAL "")
            message("${profileVar}: ${profileValue}")
            target_compile_definitions(synthCore PUBLIC ${profileVar}=${profileValue})
        else()
            message("${profileVar} not provided, using default config value")
        endif()
    endforeach()
endif()

# Add core include directories

# Treat warnings as errors
set_target_properties(synthCore PROPERTIES 
    COMPILE_WARNING_AS_ERROR ON)

# Disable C++ exceptions and Runtime Type Information (RTTI)
if(MSVC)
    # Remove default exception and RTTI flags if they exist and explicitly disable them
    target_compile_options(synthCore PRIVATE
        /EHs-c- # Disable Exceptions
        /GR-    # Disable RTTI
    )
    # turn off exceptions in the Microsoft Standard Library (STL)
    target_compile_definitions(synthCore PRIVATE _HAS_EXCEPTIONS=0)
else()
    # For GCC and Clang (Linux, macOS, MinGW)
    target_compile_options(synthCore PRIVATE
        -fno-exceptions
        -fno-rtti
    )
endif()

# Disable features based on toolchain

set(DISABLED_THREADS $CACHE{DISABLED_THREADS})
if($CACHE{DISABLED_THREADS})
    target_compile_definitions(synthCore PUBLIC DISABLED_THREADS)

endif()

if($CACHE{DISABLED_FILESYSTEM})
    target_compile_definitions(synthCore PRIVATE DISABLED_FILESYSTEM)
endif()


# Special handling if you are targeting Apple Xcode generator specifically
if(CMAKE_GENERATOR MATCHES "Xcode")
    set_target_properties(synthCore PROPERTIES
        XCODE_ATTRIBUTE_GCC_ENABLE_CPP_EXCEPTIONS "NO"
        XCODE_ATTRIBUTE_GCC_ENABLE_CPP_RTTI "NO"
    )
endif()

enable_testing()
add_subdirectory(tests)
