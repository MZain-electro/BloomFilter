# Create a library target
add_library(hashing
    crc32.cpp
    digest.cpp
    md5.cpp
    sha1.cpp
    sha256.cpp
    sha3.cpp
    keccak.cpp
    # Add all other .cpp files in the hashing folder
)

# Include the headers directory
target_include_directories(hashing PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
