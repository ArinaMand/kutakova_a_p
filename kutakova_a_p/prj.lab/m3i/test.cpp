#include "m3i.h"
#include <cassert>
#include <iostream>

void TestConstruct(){
    M3i m = M3i();
    delete &m;
    M3i tensor(2, 4, 6);
    M3i tensor_2(tensor);
    assert(tensor.size(0) == tensor_2.size(0) && tensor.size(1) == tensor_2.size(1) && tensor.size(2) == tensor_2.size(2));

    M3i tensor_3 = M3i(std::move(tensor_2));
    assert(tensor.size(0) == tensor_3.size(0) && tensor.size(1) == tensor_3.size(1) && tensor.size(2) == tensor_3.size(2));

    /*M3i tensor_4 = M3i(*tensor_2);
    assert(tensor.size(0) == tensor_3.size(0) && tensor.size(1) == tensor_3.size(1) && tensor.size(2) == tensor_3.size(2));
    */
}

void TestEquality(){
    M3i tensor(2, 4, 6);
    M3i tensor_2 = tensor;
    assert(tensor.size(0) == tensor_2.size(0) && tensor.size(1) == tensor_2.size(1) && tensor.size(2) == tensor_2.size(2));
}

void TestClone(){
    M3i tensor(2, 4, 6);
    M3i tensor_2 = tensor.clone();
    assert(tensor.size(0) == tensor_2.size(0) && tensor.size(1) == tensor_2.size(1) && tensor.size(2) == tensor_2.size(2));
}

void TestResize(){
    M3i t = M3i(1, 1, 1);
    t.resize(3, 4, 5);
    assert(t.size(0) == 3 && t.size(1) == 4 && t.size(2) == 5);
}

void TestFill(){
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

int main(){
    
}