cmake_minimum_required(VERSION 2.6)

project(kangaroo)
set(EXECUTABLE_NAME "kangaroo")
set(TEST_EXECUTABLE_NAME "${EXECUTABLE_NAME}_tests")
add_executable(${EXECUTABLE_NAME} src/main.cpp)

# Locate GTest
include_directories (./src/)
enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
add_executable(${TEST_EXECUTABLE_NAME} tests/main.cpp)
target_link_libraries(${TEST_EXECUTABLE_NAME} ${GTEST_BOTH_LIBRARIES})

target_link_libraries(${TEST_EXECUTABLE_NAME} pthread)

find_package(Eigen3 REQUIRED)
include_directories (${EIGEN3_INCLUDE_DIR})

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML 1.6 REQUIRED system window graphics network audio)
target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})

set(${SFML_LIBRARIES} -lsfml-graphics -lsfml-window -lsfml-system)

target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})
 
# Link runTests with what we want to test and the GTest and pthread library
target_link_libraries(${EXECUTABLE_NAME} ${GTEST_LIBRARIES} pthread)
