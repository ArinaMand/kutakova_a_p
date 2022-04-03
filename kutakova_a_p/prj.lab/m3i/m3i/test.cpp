#include "m3i.h"
#include <iostream>

TEST_CASE("TestConstructor")
{
    M3i tensor = M3i();
    delete &tensor;
    M3i tensor(2, 4, 6);
    M3i tensor_2(tensor);
    assert(tensor.size(0) == tensor_2.size(0));
    assert(tensor.size(1) == tensor_2.size(1));
    assert(tensor.size(2) == tensor_2.size(2));

    M3i tensor_3 = (std::move(tensor_2));
    assert(tensor.size(0) == tensor_3.size(0));
    assert(tensor.size(1) == tensor_3.size(1));
    assert(tensor.size(2) == tensor_3.size(2));
}

TEST_CASE("TestEquality")
{
    M3i tensor = M3i(1, 3, 4);
    M3i tensor_2 = tensor;
    assert(tensor.size(0) == tensor_2.size(0));
    assert(tensor.size(1) == tensor_2.size(1));
    assert(tensor.size(2) == tensor_2.size(2));

    M3i tensor_3 = std::move(tensor_2);
    assert(tensor.size(0) == tensor_3.size(0));
    assert(tensor.size(1) == tensor_3.size(1));
    assert(tensor.size(2) == tensor_3.size(2));
}

TEST_CASE("TestClone")
{
    M3i tensor = M3i(1, 2, 3);
    M3i tensor_2 = tensor.clone();
    assert(tensor.size(0) == tensor_2.size(0));
    assert(tensor.size(1) == tensor_2.size(1));
    assert(tensor.size(2) == tensor_2.size(2));
}

TEST_CASE("TestResize")
{
    M3i t = M3i(1, 1, 1);
    t.resize(3, 4, 5);
    assert(t.size(0) == 3);
    assert(t.size(1) == 4;
    assert(t.size(2) == 5);
}

TEST_CASE("TestFill")
{
    M3i t = M3i(2, 4, 6);
    t.fill(17);
    for (int i = 0; i < t.size(0); ++i) {
        for (int j = 0; j < t.size(1); ++j) {
            for (int k = 0; k < t.size(2); ++k) {
                assert(t.at(i, j, k) == 1);
            }
        }
    }
}
