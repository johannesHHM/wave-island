project(islands)
cmake_minimum_required(VERSION 3.23)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y -Wall -Wextra")
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(GLU REQUIRED)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} OpenGL::GL GLUT::GLUT OpenGL::GLU)
 
add_executable(test model.cpp)
target_link_libraries(test OpenGL::GL GLUT::GLUT OpenGL::GLU)

