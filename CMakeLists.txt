project(island)
cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y")
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(GLU REQUIRED)

add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} OpenGL::GL GLUT::GLUT OpenGL::GLU)
