project(Google_tests)
add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(Google_Tests_run PathFindTest.cpp)

target_link_libraries(Google_Tests_run PathFinding_lib)

target_link_libraries(Google_Tests_run gtest gtest_main)



#project(Google_tests)
#add_subdirectory(lib)
#include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
#
#
#add_executable(Google_Tests_run ConverterTests.cpp AbsoluteDateTest.cpp)
#
#target_link_libraries(Google_Tests_run DateConverter_lib)
#
#target_link_libraries(Google_Tests_run gtest gtest_main)