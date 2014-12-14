cmake_minimum_required(VERSION 2.6)

file(GLOB all_src
	"src/*/*.hpp"
	"src/*/*.cpp"
)

project(kangaroo)
set(EXECUTABLE_NAME "kangaroo")
set(TEST_EXECUTABLE_NAME "${EXECUTABLE_NAME}_tests")
set(CMAKE_BUILD_TYPE Debug)
add_executable(${EXECUTABLE_NAME} src/main.cpp ${all_src})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D__FILENAME__='\"$(subst ${CMAKE_SOURCE_DIR}/,,$(abspath $<))\"'")

add_definitions(
	-std=c++1y
	)
# Locate GTest
include_directories (./src/)
enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
add_executable(${TEST_EXECUTABLE_NAME} tests/main.cpp ${all_src})
target_link_libraries(${TEST_EXECUTABLE_NAME} ${GTEST_BOTH_LIBRARIES})

target_link_libraries(${TEST_EXECUTABLE_NAME} pthread)

find_package(Eigen3 REQUIRED)
include_directories (${EIGEN3_INCLUDE_DIR})

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})
find_package(SFML 1.6 REQUIRED system window graphics network audio)
target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})

file(GLOB SOURCES src/*.cpp)
 
# Link runTests with what we want to test and the GTest and pthread library
target_link_libraries(${EXECUTABLE_NAME} ${GTEST_MAIN_LIBRARIES} pthread)
