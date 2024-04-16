cmake_minimum_required(VERSION 3.10)
project(RSCA) # Project name

# Add the executable target
add_executable(RSCA_executable
    hash.cpp
) 

# Include the headers directory
target_include_directories(RSCA_executable PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# Add the hashing directory
add_subdirectory(hashing)
add_subdirectory(murmur)

# Link the hashing library with the executable
target_link_libraries(RSCA_executable PRIVATE hashing)
