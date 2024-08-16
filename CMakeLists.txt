cmake_minimum_required(VERSION 3.14)


# Insert custom CMake modules
list(INSERT CMAKE_MODULE_PATH 0 "${CMAKE_SOURCE_DIR}/cmake")

# Compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

# Print the source directory
message(STATUS "Source dir: ${CMAKE_SOURCE_DIR}")

# Project definition
project(MyExecutable VERSION 1.0.0)

# Include directories
include_directories("include/")

# Source files
file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS "source/*.cpp")

# Define the executable
add_executable(MyExecutable src/main.cpp)

# Installation rules
install(TARGETS MyExecutable DESTINATION bin)



# External libraries (example with Boost and a local library)
# Uncomment the following lines to include external libraries

# Find Boost
# find_package(Boost REQUIRED COMPONENTS system filesystem)
# if(Boost_FOUND)
#     include_directories(${Boost_INCLUDE_DIRS})
#     link_directories(${Boost_LIBRARY_DIRS})
# endif()

# Include a local library
# add_subdirectory(libs/MyLocalLib)
# include_directories(libs/MyLocalLib/include)

# Link external libraries
# if(Boost_FOUND)
#     target_link_libraries(MyExecutable ${Boost_LIBRARIES})
# endif()
# target_link_libraries(MyExecutable MyLocalLib)