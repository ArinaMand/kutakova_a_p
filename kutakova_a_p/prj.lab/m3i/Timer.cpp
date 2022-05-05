#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include "m3i.h"
#include <cassert>

int main(){
    printf("sjdfskjfnlk");
    std::ofstream f ("Timer.txt", std::ofstream::out);
    if (!f.is_open()){
        printf("agagagagag");
    }
    const int ten = 10;
    int t = clock();
    M3i aaa(ten, ten, ten);
    int t2 = clock();
    int res = (t2-t)/CLOCKS_PER_SEC;
    std::cout<<std::to_string(res);
    f<<std::to_string(res);
    f<<"jjnlkkjm";
}