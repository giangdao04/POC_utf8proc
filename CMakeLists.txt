# Build open vino Inference engine for mobilenet model
cmake_minimum_required(VERSION 2.8)
project(utf8proc_test)
# include(${CMAKE_CURRENT_SOURCE_DIR}/neo-ai-dlr/CMakeLists.txt)
set(TARGET_NAME "utf8proc_test")
set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")
set(CMAKE_BUILD_TYPE "Release")

file (GLOB SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp
)

find_package(CUDA)

source_group("src" FILES ${SRC})

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/dep/utf8proc/include
)

# Create library file from sources.
add_executable(${TARGET_NAME} ${SRC})

target_link_libraries(${TARGET_NAME}  
    ${CMAKE_CURRENT_SOURCE_DIR}/dep/utf8proc/lib/libutf8proc.a
)
