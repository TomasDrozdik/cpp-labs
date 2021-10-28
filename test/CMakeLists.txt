include_directories(..)

add_executable(runtests
    test_lab2.cpp ../lab2/foo.cpp
    test_lab4.cpp ../lab4/allocator.h
)

target_link_libraries(runtests gtest_main)

include(GoogleTest)
gtest_discover_tests(runtests)
