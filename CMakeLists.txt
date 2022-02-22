cmake_minimum_required(VERSION 3.6)

project(pizza)

include_directories(include)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED on)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -fsanitize=address")

add_executable(${PROJECT_NAME} ./impl.cpp ./main.cpp)
