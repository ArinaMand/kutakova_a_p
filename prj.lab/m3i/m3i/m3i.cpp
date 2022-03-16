#include "pch.h"
#include <iostream>

class m3i {
    public:
        m3i() = default;
        m3i(const int x, const int y, const int z) {
            coordinates = [x, y, z];
            values = new int[x * y*z];
        }
        m3i(const m3i& copy) {
            coordinates = copy.coordinates;
            values = copy.values;
        }
        ~m3i();

        m3i& operator=(const m3i& copy) {
            coordinates = copy.coordinates;
            values = copy.values;
            return *this;
        }
        int& get_value(const int x, const int y, const int z) {
            return values[x * (coordinates[1] * coordinates[2]) + y * coordinates[2] + z];
        }

        int size(const int dim) const {
            return coordinates[dim];
        }
        void fill(const int value) {
            for (int x = 0; x < coordinates[0]; ++x) {
                for (int y = 0; y < coordinates[1]; ++y) {
                    for (int z = 0; z < coordinates[2]; ++z) {
                        get_value(x, y, z) = 0;
                    }
                }
            }
        }
    private:
        int* values = nullptr;
        int coordinates[3] = { 0, 0, 0 };
};

int main()
{
    std::cout << "Hello World!\n"; 
}
