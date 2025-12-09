cmake_minimum_required(VERSION 3.10)

project(FEM_Project)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(EIGEN3_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/3rdParty/Eigen")

# 包含目录
include_directories(
    ${EIGEN3_INCLUDE_DIR}
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/src
)

# 添加子目录
add_subdirectory(Element)
add_subdirectory(ElementCheck)
add_subdirectory(FEM)
add_subdirectory(IO)
add_subdirectory(Mesh)
add_subdirectory(Utils)
# 源文件
file(GLOB SOURCES "src/*.cpp" "src/*/*.cpp")

# 可执行文件
add_executable(FEM_Project ${SOURCES} main.cpp)

# 测试
add_subdirectory(test)