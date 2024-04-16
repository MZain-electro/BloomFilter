# Create a library target
add_library(murmur
    murmur3.c
    # Add all other .cpp files in the hashing folder
)

# Include the headers directory
target_include_directories(murmur PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
