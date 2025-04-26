cmake_minimum_required(VERSION 3.10)

project(FEM_Project)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Eigen3 REQUIRED)

# 包含目录
include_directories(
    ${EIGEN3_INCLUDE_DIR}
    ${PROJECT_SOURCE_DIR}/include
)

# 源文件
file(GLOB SOURCES "src/*.cpp" "src/*/*.cpp")

# 可执行文件
add_executable(FEM_Project ${SOURCES} main.cpp)

# 测试
enable_testing()
add_subdirectory(test)