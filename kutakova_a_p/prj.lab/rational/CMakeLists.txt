project(rational)
add_library(rational rational.h rational.cpp)
add_executable(unittest unittest.cpp)
target_link_libraries(unittest rational)
