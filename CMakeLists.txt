cmake_minimum_required(VERSION 3.24)
project (OSynthCore VERSION 1.0)
# Configure and build core static library
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Set the default profile to full if it is not provided in the cache variables
set(OSYNTH_PROFILE "full" CACHE STRING "Build profile")

set(availableProfiles
    full
    lite 
    )


set_property(CACHE OSYNTH_PROFILE PROPERTY STRINGS ${availableProfiles})


# Setup configuration config values


# Retrieve build profile



#build profile defined
if (NOT OSYNTH_PROFILE IN_LIST availableProfiles)
    message(FATAL_ERROR "OSynth Core: ${OSYNTH_PROFILE} not in available profiles: ${availableProfiles}")
endif()

message(STATUS "OSynth Core: profile selected ${OSYNTH_PROFILE}")

# The Core static library holding all the DSP code.
# For now its public interface does one thing report:
# its version, the active profile name and that profiles limits.


set(coreSources 
    src/oscillator.cpp
    src/config.cpp
    src/gain.cpp
    src/smoothableFloat.cpp
    src/engine.cpp
) 
# create library target and alias
add_library(osynth_core STATIC ${coreSources})
add_library(OSynth::Core ALIAS osynth_core)

# enforce c++ 20 standard for consuming projects
target_compile_features(osynth_core PUBLIC cxx_std_20)

target_include_directories(osynth_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_definitions(osynth_core PUBLIC OSYNTH_PROFILE="${OSYNTH_PROFILE}")

# provided overrides for profile configurations
set(profileVars
    OSYNTH_MAX_VOICES 
    OSYNTH_MAX_BLOCK_SIZE 
    OSYNTH_WAVETABLE_LENGTH
    OSYNTH_OVERSAMPLING_FACTOR
    OSYNTH_COMMAND_QUEUE_SIZE
    OSYNTH_CACHE_LINE_SIZE
    )

# Profile configurations that require to be the power of 2
set(powerOf2Vars
    OSYNTH_COMMAND_QUEUE_SIZE
    OSYNTH_CACHE_LINE_SIZE
    )

foreach(profileVar IN LISTS profileVars)
    set(${profileVar} "" CACHE STRING "profile override for ${profileVar}" )
endforeach()

# Set config for overrides when provided through cache variables
foreach(profileVar IN LISTS profileVars)
    set(profileValue "${${profileVar}}")
    if(NOT profileValue STREQUAL "")

        # ensure that the number is a positive integer.
        if (NOT profileValue MATCHES "^[1-9][0-9]*$")
            message(FATAL_ERROR "OSynth Core: ${profileVar} must be a positive whole number.")
        endif()

        # if the variable that must be to the power of 2
        # check value and throw error if it is not.

        if (profileVar IN_LIST powerOf2Vars)
            math(EXPR remainder "${profileValue} & (${profileValue} - 1)")
            if(NOT remainder EQUAL 0)
                message(FATAL_ERROR "OSynth Core: ${profileVar} must be a power of 2, got ${profileValue}")
            endif()
        endif()
        message(STATUS "OSynth Core: ${profileVar}: ${profileValue}")
        target_compile_definitions(synthCore PUBLIC ${profileVar}=${profileValue})
    else()
        message(VERBOSE "OSynth Core: ${profileVar} not provided, using default config value")
    endif()
endforeach()



# Add core include directories
# CACHE LINE OPTIMIZATION
# If the target uses a cache line of less than 64 bytes
# such as ARM chips. you may set the cache line size below.


# Treat warnings as errors
if(PROJECT_IS_TOP_LEVEL)
    set_target_properties(osynth_core PROPERTIES 
        COMPILE_WARNING_AS_ERROR ON)
endif()

# Set compiler specific flags

# Disable C++ exceptions and Runtime Type Information (RTTI)
if(MSVC)
    # Remove default exception and RTTI flags if they exist and explicitly disable them
    target_compile_options(osynth_core PRIVATE
        /EHs-c- # Disable Exceptions
        /GR-    # Disable RTTI
        # Set warning flags to be caught
        /W4
        /permissive-
    )
    # turn off exceptions in the Microsoft Standard Library (STL)
    target_compile_definitions(osynth_core PRIVATE _HAS_EXCEPTIONS=0)
else()
    # For GCC and Clang (Linux, macOS, MinGW)
    target_compile_options(osynth_core PRIVATE
        # Disable exceptions
        -fno-exceptions
        -fno-rtti
        # Set Warning flags
        -Wall
        -Wextra
        -Wpedantic
    )
endif()

# Enable 
# Special handling if you are targeting Apple Xcode generator specifically
if(CMAKE_GENERATOR MATCHES "Xcode")
    set_target_properties(osynth_core PROPERTIES
        XCODE_ATTRIBUTE_GCC_ENABLE_CPP_EXCEPTIONS "NO"
        XCODE_ATTRIBUTE_GCC_ENABLE_CPP_RTTI "NO"
    )
endif()

if(PROJECT_IS_TOP_LEVEL AND NOT CMAKE_CROSSCOMPILING)
    enable_testing()
    add_subdirectory(tests)
endif()
