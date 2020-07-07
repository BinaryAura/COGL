cmake_minimum_required(VERSION 3.16)
project(COGL VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 17)
set( CMAKE_VERBOSE_MAKEFILE on )

find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)
find_library(GLEW PATHS /lib /lib64)
find_library(GL PATHS /lib /lib64)

add_executable(opengl_test tests/ogltest.cpp)
add_library(cogl src/renderer.cpp src/vertexBuffer.cpp include/vertexBuffer.h src/indexBuffer.cpp include/indexBuffer.h)

target_include_directories(cogl PRIVATE ${OPENGL_INCLUDE_DIR} ${GLEW_INCLUDE_DIRS} PUBLIC include)

add_dependencies(opengl_test cogl)

target_link_libraries(cogl PRIVATE ${OPENGL_LIBRARIES} GLEW)
target_link_libraries(opengl_test PRIVATE glfw cogl)
