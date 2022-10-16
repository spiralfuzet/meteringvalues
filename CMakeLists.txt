cmake_minimum_required(VERSION 3.14)

# Note: Toolchain configuration should be before first project
if (NOT CMAKE_TOOLCHAIN_FILE)
	set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake CACHE STRING "Vcpkg toolchain file")
endif()

project(meteringvalues)

# Compiler requirements and configuration
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Testing
enable_testing()

# Source files
file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "include/*.h")

# Dependencies
find_package(jsoncpp CONFIG REQUIRED)
find_package(fmt REQUIRED)
find_package(magic_enum CONFIG REQUIRED)

# Executable and options
add_executable(meteringvalues ${SOURCES} ${HEADERS})
target_include_directories(meteringvalues PUBLIC "include")
target_link_libraries(meteringvalues PRIVATE
    JsonCpp::JsonCpp
    fmt::fmt
    magic_enum::magic_enum
)

# Tests
add_subdirectory(test)
