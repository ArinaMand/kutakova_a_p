project(m3i)
add_library(m3i m3i.h m3i.cpp)
add_executable(test_1 test.cpp)
target_link_libraries(test_1 m3i)
