project(rational)
add_library(rational rational.h rational.cpp)
add_executable(test_rational unittest.cpp)
target_link_libraries(test_rational rational)