include_directories(..)

add_executable(runtests_lab2 test_lab2.cpp ../lab2/foo.cpp)
target_link_libraries(runtests_lab2 gtest_main)
