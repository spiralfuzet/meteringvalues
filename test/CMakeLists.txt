find_package(Catch2 CONFIG REQUIRED)

file(GLOB_RECURSE TEST_SOURCE_FILES
    "*.cpp"
    "../src/visitor/*.cpp"
    "../src/utils/*.cpp"
)

add_executable(tests ${TEST_SOURCE_FILES})

target_include_directories(tests PRIVATE "../include")
target_link_libraries(tests PRIVATE
    Catch2::Catch2 Catch2::Catch2WithMain
    JsonCpp::JsonCpp
    fmt::fmt
    magic_enum::magic_enum
)

include(CTest)
include(Catch)
catch_discover_tests(tests)
