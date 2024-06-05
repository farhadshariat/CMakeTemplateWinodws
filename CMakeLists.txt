cmake_minimum_required(VERSION 3.25)
project(Test LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED on)


#set(SDL2_REQUIRED_DIR "C:\\Program Files\\SDL2\\cmake")
find_package(SDL2 REQUIRED)

#set(SDL2_INCLUDE_DIR "C:\\Program Files\\SDL2\\include")

add_executable(main main.cpp)
target_link_libraries(main PUBLIC SDL2::SDL2main SDL2::SDL2)
#target_include_directories(main PRIVATE ${SDL2_INCLUDE_DIR})