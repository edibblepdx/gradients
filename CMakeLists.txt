cmake_minimum_required(VERSION 3.12)
project(gradients VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -g")

# find python3
find_package(Python3 REQUIRED COMPONENTS Interpreter Development)

# Add the executable and include all source files
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
file(GLOB CXX_SRCS "${SRC_DIR}/*.cpp")
add_executable(gradients ${CXX_SRCS})

# Add include directories
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(gradients PRIVATE ${INCLUDE_DIR})

#set(scripts "${CMAKE_SOURCE_DIR}/../py_color")
#add_compile_definitions(PYTHONFILE="${scripts}/colorspaces.py")

# Link libraries
target_link_libraries(gradients PRIVATE
    Python3::Python
    curses
)
