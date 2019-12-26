cmake_minimum_required(VERSION 3.15)
project(matplotlibcpp)

set(CMAKE_CXX_STANDARD 17)

find_package(Boost COMPONENTS python3 numpy3)
find_package(Python3 COMPONENTS Interpreter Development NumPy)

add_library(matplotlibcpp INTERFACE)
target_include_directories(matplotlibcpp INTERFACE ${CMAKE_CURRENT_LIST_DIR}/inc)
target_link_libraries(matplotlibcpp INTERFACE Python3::Python Python3::NumPy Boost::python3 Boost::numpy3)


file(GLOB SRCS ${CMAKE_CURRENT_LIST_DIR}/test/*.cpp)
foreach(SRC ${SRCS})
    get_filename_component(TARGET_NAME ${SRC} NAME_WE)
    add_executable(${TARGET_NAME} ${SRC})
    target_link_libraries(${TARGET_NAME} matplotlibcpp)
endforeach()

