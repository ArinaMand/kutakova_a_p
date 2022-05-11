project(BitSet)
add_library(BitSet BitSet.h BitSet.cpp)
add_executable(my_test my_test.cpp)
target_link_libraries(my_test BitSet)
