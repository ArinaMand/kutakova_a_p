#include "m3i.h"
#include <iostream>

M3i::M3i(const int x, const int y, const int z) {
    coordinates[0] = x;
    coordinates[1] = y;
    coordinates[2] = z;
    box = new int[x*y*z];
    ptr_counter = 0;
}
M3i::M3i(int x, int y, int z, int value) : M3i(x, y, z) {
    //Fill(value);
    for (int i=0; i < x * y * z; ++i){
        box[i] = value;
    }
}
M3i::M3i(const std::initializer_list<std::initializer_list<std::initializer_list<int>>>& list) {
    coordinates[0] = (int)list.size();
    coordinates[1] = (int)list.begin()->size();
    coordinates[2] = (int)list.begin()->begin()->size();
    box = new int[coordinates[0]*coordinates[1]*coordinates[2]];
    ptr_counter = 0;
    int position = 0;
    for (auto i : list) {
        for (auto j : i) {
            for (auto value : j) {
                box[position] = value;
                ++position;
            }
        }
    }
}
M3i::M3i(const M3i& copy) {
    coordinates[0] = copy.Size(0);
    coordinates[1] = copy.Size(1);
    coordinates[2] = copy.Size(2);
    box = copy.box;
    ptr_counter  = copy.ptr_counter + 1;
}
M3i::M3i(M3i&& copy) {
    coordinates[0] = copy.Size(0);
    coordinates[1] = copy.Size(1);
    coordinates[2] = copy.Size(2);
    box = copy.box;
    ptr_counter = copy.ptr_counter;

    copy.coordinates[0] = 0;
    copy.coordinates[1] = 0;
    copy.coordinates[2] = 0;
    copy.box = nullptr;
    copy.ptr_counter = 0;
};


int& M3i::At(const int x, const int y, const int z)
{
    if (x >= Size(0) || x < 0 || y >= Size(1) || y < 0 || z >= Size(2) || z < 0) {
        throw std::invalid_argument("value out of range");
    }
    return box[x * (coordinates[1] * coordinates[2]) + y * coordinates[2] + z];
}
int M3i::At(const int x, const int y, const int z) const
{
    if (x >= Size(0) || x < 0 || y >= Size(1) || y < 0 || z >= Size(2) || z < 0) {
        throw std::invalid_argument("value out of range");
    }
    return box[x * (coordinates[1] * coordinates[2]) + y * coordinates[2] + z];
}
M3i& M3i::Resize(const int x, const int y, const int z)//от трех значений, просто ставит новые данные
{
    if (x <= 0 || y <= 0 || z <= 0) {
        throw std::invalid_argument("value out of range");
    }
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
                    At(i, j, k) = 0;
                }
                else {
                    At(i, j, k) = old_box[i*old_coordinates[1] * old_coordinates[2]
                        + j * old_coordinates[2] + k];
                }
            }
        }
    }
    return *this;
}

int M3i::Size(const int dim) const//get size
{
    if (dim>2 || dim <0 ){
        throw std::invalid_argument("value out of range");
    }
    return coordinates[dim];
}
void M3i::Fill(const int val) {
    for (int x = 0; x < Size(0); ++x) {
        for (int y = 0; y < Size(1); ++y) {
            for (int z = 0; z < Size(2); ++z) {
                At(x, y, z) = val;
            }
        }
    }
}//поставить всем одно значение

M3i M3i::Clone() const {
    M3i copy(coordinates[0], coordinates[1], coordinates[2]);
    for (int x = 0; x < coordinates[0]; ++x) {
        for (int y = 0; y < coordinates[1]; ++y) {
            for (int z = 0; z < coordinates[2]; ++z) {
                copy.At(x, y, z) = At(x, y, z);
            }
        }
    }
    return copy;
};
M3i& M3i::operator=(const M3i& copy) {
    coordinates[0] = copy.Size(0);
    coordinates[1] = copy.Size(1);
    coordinates[2] = copy.Size(2);
    box = copy.box;
    ptr_counter = copy.ptr_counter + 1;
    return *this;
}
M3i& M3i::operator=(M3i&& copy) {
    coordinates[0] = copy.Size(0);
    coordinates[1] = copy.Size(1);
    coordinates[2] = copy.Size(2);
    box = copy.box;
    ptr_counter = copy.ptr_counter;

    copy.coordinates[0] = 0;
    copy.coordinates[1] = 0;
    copy.coordinates[2] = 0;
    copy.box = nullptr;
    copy.ptr_counter = 0;
    return *this;
}

std::ostream& M3i::WriteTo(std::ostream& strm) const noexcept
{
    strm << "size: " << Size(0) << " " << Size(1) << " " << Size(2) << "\n";
    for (int x = 0; x < Size(0); ++x){
        for (int y = 0; y < Size(1); ++y) {
            for (int z = 0; z < Size(2); ++z) {
                strm << At(x,y,z) << " ";
            }
            strm << std::endl;
        }
        strm << std::endl;
    }
    return strm;
}

std::istream& M3i::ReadFrom (std::istream& istrm)
{
    std::string str;
    int shape[3]  = {};
    for (int i = 0; i < 3; ++i) {
        if(!isdigit(istrm.peek())) {
            istrm.clear(std::ios_base::failbit);
            return istrm;
        } else {
            istrm >> shape[i];
            if(!istrm.good())
            {
                istrm.clear(std::ios_base::failbit);
                return istrm;
            }
            if( i != 2)
                istrm.get();
        }
    }
    if(shape[0] <= 0 || shape[1] <= 0 || shape[2] <= 0 || !istrm.good()) {
        istrm.clear(std::ios_base::failbit);
        return istrm;
    }

    Resize(shape[0], shape[1], shape[2]);
    int buffer = 0;
    for (int i = 0; i < Size(0); ++i) {
        for (int j = 0; j < Size(1); ++j) {
            for (int k = 0; k < Size(2); ++k) {
                int number;
                istrm >> number;
                if(istrm.good())
                    At(i, j, k) = number;
            }
        }
    }
    return istrm;
}

std::ostream& operator << (std::ostream& strm, M3i& r) noexcept {
    return r.WriteTo(strm);
}
std::istream& operator >> (std::istream& strm , M3i& r) {
    return r.ReadFrom(strm);
}
