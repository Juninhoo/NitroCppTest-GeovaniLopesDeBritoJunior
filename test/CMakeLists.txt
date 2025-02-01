cmake_minimum_required(VERSION 3.13)

set(This UnitTest)


set(Sources
    UnitTest.cpp
    ../rectangle.cpp  # Include the rectangle source file
)

add_executable(${This} ${Sources})


# Add include directories for Google Test
#target_include_directories(${This} PRIVATE ../googletest/googletest/include)

target_include_directories(${This} PRIVATE ${CMAKE_SOURCE_DIR}/googletest/googletest/include)


target_link_libraries(${This} PUBLIC
    gtest
    gtest_main
    NitroCppTestGeovaniLopesDeBritoJunior
)

include_directories(include(GoogleTest))

add_test(
    NAME ${This}
    COMMAND ${This}
)