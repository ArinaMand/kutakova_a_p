#include "m3i.h"
#include <cassert>
#include <iostream>

void TestConstruct(){
    M3i* m = new M3i();
    delete m;
    M3i tensor(2, 4, 6);
    M3i tensor_2(tensor);
    assert(tensor.Size(0) == tensor_2.Size(0) && tensor.Size(1) == tensor_2.Size(1) && tensor.Size(2) == tensor_2.Size(2));

    M3i tensor_3 = M3i(std::move(tensor_2));
    assert(tensor.Size(0) == tensor_3.Size(0) && tensor.Size(1) == tensor_3.Size(1) && tensor.Size(2) == tensor_3.Size(2));

    /*M3i tensor_4 = M3i(*tensor_2);
    assert(tensor.size(0) == tensor_3.size(0) && tensor.size(1) == tensor_3.size(1) && tensor.size(2) == tensor_3.size(2));
    */
}

void TestEquality(){
    M3i tensor(2, 4, 6);
    M3i tensor_2 = tensor;
    assert(tensor.Size(0) == tensor_2.Size(0) && tensor.Size(1) == tensor_2.Size(1) && tensor.Size(2) == tensor_2.Size(2));
}

void TestClone(){
    M3i tensor(2, 4, 6);
    M3i tensor_2 = tensor.Clone();
    assert(tensor.Size(0) == tensor_2.Size(0) && tensor.Size(1) == tensor_2.Size(1) && tensor.Size(2) == tensor_2.Size(2));
}

void TestResize(){
    M3i t = M3i(1, 1, 1);
    t.Resize(3, 4, 5);
    assert(t.Size(0) == 3 && t.Size(1) == 4 && t.Size(2) == 5);
}

void TestFill(){
    M3i t = M3i(2, 4, 6);
    t.Fill(17);
    for (int i = 0; i < t.Size(0); ++i) {
        for (int j = 0; j < t.Size(1); ++j) {
            for (int k = 0; k < t.Size(2); ++k) {
                assert(t.At(i, j, k) == 17);
            }
        }
    }
}

int main(){
    TestConstruct();
    std::cout<<"Construct ok\n\r";
    TestEquality();
    std::cout<<"equality ok\n\r";
    TestClone();
    std::cout<<"clone ok\n\r";
    TestResize();
    std::cout<<"resize ok\n\r";
    TestFill();
    std::cout<<"fill ok\n\r";
}