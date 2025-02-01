cmake_minimum_required(VERSION 3.13)

set(This NitroCppTestGeovaniLopesDeBritoJunior)

project(${This} CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_subdirectory(googletest)

# Add the main program target
add_executable(rectangle_build main.cpp rectangle.cpp)

# Add the test target
enable_testing()

add_executable(rectangle_tests test/UnitTest.cpp rectangle.cpp)

# Include Google Test headers
target_include_directories(rectangle_tests PRIVATE googletest/googletest/include)

# Link Google Test libraries
target_link_libraries(rectangle_tests PRIVATE gtest gtest_main)

# Add test command
add_test(NAME RectangleTests COMMAND rectangle_tests)

set(Headers
    rectangle.hpp
    json.hpp
)

set(Sources
    main.cpp
    rectangle.cpp
)

add_library(${This} STATIC ${Sources} ${Headers})

add_subdirectory(test)

# Custom CMake rules for clarity
add_custom_target(build_tests ALL DEPENDS rectangle_tests COMMENT "Building tests")
add_custom_target(run_all_tests COMMAND ctest --output-on-failure COMMENT "Running all tests")
add_custom_target(build_code ALL DEPENDS rectangle_build COMMENT "Building main code")
add_custom_target(run_code COMMAND rectangle_build ${CMAKE_BINARY_DIR}/rectangles.json COMMENT "Running main program with rectangles.json")


# Platform-specific flags for portability
if(WIN32)
    message(STATUS "Configuring for Windows...")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
elseif(APPLE)
    message(STATUS "Configuring for macOS...")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
elseif(UNIX)
    message(STATUS "Configuring for Linux...")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY /mnt/${CMAKE_BINARY_DIR}/bin)
endif()