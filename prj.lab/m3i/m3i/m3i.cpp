#include "pch.h"
#include "m3i.h"
#include <iostream>

m3i::m3i(const int x, const int y, const int z) {
    coordinates[0] = x;
    coordinates[1] = y;
    coordinates[2] = z;
    box = new int[x*y*z];
    ptr_counter = 0;
}

m3i::m3i(const m3i& copy) {
    coordinates[0] = copy.size(0);
    coordinates[1] = copy.size(1);
    coordinates[2] = copy.size(2);
    box = copy.box;
    ptr_counter = copy.ptr_counter + 1;
}
m3i::m3i(m3i&& copy) {
    coordinates[0] = copy.size(0);
    coordinates[1] = copy.size(1);
    coordinates[2] = copy.size(2);
    ptr_counter = copy.ptr_counter;
    copy.ptr_counter = 0;
};


int& m3i::at(const int x, const int y, const int z)
{
    return box[x * (coordinates[1] * coordinates[2]) + y * coordinates[2] + z];
}
int m3i::at(const int x, const int y, const int z) const
{
    return box[x * (coordinates[1] * coordinates[2]) + y * coordinates[2] + z];
}
m3i& m3i::resize(const int x, const int y, const int z)//от трех значений, просто ставит новые данные
{
    int* old_box = box;
    int old_coordinates[3] = { coordinates[0], coordinates[1], coordinates[2] };
    coordinates[0] = x;
    coordinates[1] = y;
    coordinates[2] = z;
    box = new int[x*y*z];
    for (int i = 0; i < x; ++i) {
        for (int j = 0; j < y; ++j) {
            for (int k = 0; k < z; ++k) {
                if (i >= old_coordinates[0] || k >= old_coordinates[2]) {
                    at(i, j, k) = 0;
                }
                else {
                    at(i, j, k) = old_box[i*old_coordinates[1] * old_coordinates[2]
                        + j * old_coordinates[2] + k];
                }
            }
        }
    }
    return *this;
}

int m3i::size(const int dim) const//get size
{
    return coordinates[dim];
}
void m3i::fill(const int val) {
    for (int x = 0; x < size(0); ++x) {
        for (int y = 0; y < size(1); ++y) {
            for (int z = 0; z < size(2); ++z) {
                at(x, y, z) = 0;
            }
        }
    }
}//поставить всем одно значение

m3i m3i::clone() const {
    m3i copy(coordinates[0], coordinates[1], coordinates[2]);
    for (int x = 0; x < coordinates[0]; ++x) {
        for (int y = 0; y < coordinates[1]; ++y) {
            for (int z = 0; z < coordinates[2]; ++z) {
                copy.at(x, y, z) = at(x, y, z);
            }
        }
    }
    return copy;
};
m3i& m3i::operator=(const m3i& copy) {
    coordinates[0] = copy.size(0);
    coordinates[1] = copy.size(1);
    coordinates[2] = copy.size(2);
    box = copy.box;
    ptr_counter = copy.ptr_counter + 1;
    return *this;
}
m3i& m3i::operator=(m3i&& copy) {
    coordinates[0] = copy.size(0);
    coordinates[1] = copy.size(1);
    coordinates[2] = copy.size(2);
    box = copy.box;
    ptr_counter = copy.ptr_counter;
    return *this;
}

int main()
{
    std::cout << "Hello World!\n"; 

}
