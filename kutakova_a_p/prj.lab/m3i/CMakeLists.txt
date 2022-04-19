project(m3i)
add_library(m3i m3i.h m3i.cpp)
add_executable(test test.cpp)
target_link_libraries(test m3i)
