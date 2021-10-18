include_directories(..)

add_executable(runtests
    test_lab2.cpp ../lab2/foo.cpp
    test_lab3.cpp ../lab3/allocator.h ../lab3/allocator.cpp
)

target_link_libraries(runtests gtest_main)

include(GoogleTest)
gtest_discover_tests(runtests)
