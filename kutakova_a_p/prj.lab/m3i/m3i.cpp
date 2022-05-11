#include "m3i.h"
#include <iostream>
#include <cstring>

M3i::M3i(){
    int c[3] = {0, 0, 0};
    data = new Data(c, new int[0], 1);
}

M3i::M3i(const int x, const int y, const int z) {
    if (x<=0 || y<=0 || z<=0){
        throw std::invalid_argument("invalid parameters");
    }
    int c[3] = {x, y, z};
    /*coordinates[0] = x;
    coordinates[1] = y;
    coordinates[2] = z;
    box = new int[x*y*z];
    ptr_counter = 0;*/
    data = new Data(c, new int[x*y*z], 1);
}
M3i::M3i(int x, int y, int z, int value) {
    if (x<=0 || y<=0 || z<=0){
        throw std::invalid_argument("invalid parameters");
    }
    //Fill(value);
    /*coordinates[0] = x;
    coordinates[1] = y;
    coordinates[2] = z;
    box = new int[x*y*z];
    ptr_counter = 0;*/
    int c[3] = {x, y, z};
    data = new Data(c, new int[x*y*z], 1);
    for (int i=0; i < x * y * z; ++i){
        data->box[i] = value;
    }
}
M3i::M3i(const std::initializer_list<std::initializer_list<std::initializer_list<int>>>& list) {
    /*coordinates[0] = (int)list.size();
    coordinates[1] = (int)list.begin()->size();
    coordinates[2] = (int)list.begin()->begin()->size();*/
    int c[3] = {(int)list.size(), (int)list.begin()->size(), (int)list.begin()->begin()->size()};
    if (c[0] <=0 || c[1] <=0 || c[2] <=0){
        throw std::invalid_argument("invalid parameters");
    }
    data = new Data(c, new int[c[0]*c[1]*c[2]], 1);
    //box = new int[coordinates[0]*coordinates[1]*coordinates[2]];
    //ptr_counter = 0;
    int x=0;
    for (auto i : list) {
        for (auto j : i) {
            for (auto value : j) {
                //std::cout<<x<<y<<z<<"\n\r";
                //std::cout<<x * (coordinates[1] * coordinates[2]) + y * coordinates[2] + z<<" : "<<value<<"\n\r";
                data->box[x] = value;
                ++x;
            }
        }
    }
}
M3i::M3i(const M3i& copy) {
    /*coordinates[0] = copy.Size(0);
    coordinates[1] = copy.Size(1);
    coordinates[2] = copy.Size(2);
    box = copy.box;
    ptr_counter  = copy.ptr_counter + 1;*/
    data = copy.data;
    data->ptr_counter++;
}
M3i::M3i(M3i&& copy) {
    /*coordinates[0] = copy.Size(0);
    coordinates[1] = copy.Size(1);
    coordinates[2] = copy.Size(2);
    box = copy.box;
    ptr_counter = copy.ptr_counter;

    copy.coordinates[0] = 0;
    copy.coordinates[1] = 0;
    copy.coordinates[2] = 0;
    copy.box = nullptr;
    copy.ptr_counter = 0;*/
    data = copy.data;
    data->ptr_counter++;
};


int& M3i::At(const int x, const int y, const int z)
{
    if (x >= Size(0) || x < 0 || y >= Size(1) || y < 0 || z >= Size(2) || z < 0) {
        throw std::invalid_argument("value out of range");
    }
    //std::cout<<box[x * (coordinates[1] * coordinates[2]) + y * coordinates[2] + z]<<"\n\r";
    return data->box[x * (data->coordinates[1] * data->coordinates[2]) + y * data->coordinates[2] + z];
}
int M3i::At(const int x, const int y, const int z) const
{
    if (x >= Size(0) || x < 0 || y >= Size(1) || y < 0 || z >= Size(2) || z < 0) {
        throw std::invalid_argument("value out of range");
    }
    return data->box[x * (data->coordinates[1] * data->coordinates[2]) + y * data->coordinates[2] + z];
}
M3i& M3i::Resize(const int x, const int y, const int z)//от трех значений, просто ставит новые данные
{
    if (x <= 0 || y <= 0 || z <= 0) {
        throw std::invalid_argument("value out of range");
    }
    int* old_box = data->box;
    int old_coordinates[3] = { data->coordinates[0], data->coordinates[1], data->coordinates[2] };
    data->coordinates[0] = x;
    data->coordinates[1] = y;
    data->coordinates[2] = z;
    data->box = new int[x*y*z];
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
    return data->coordinates[dim];
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
    M3i copy(data->coordinates[0], data->coordinates[1], data->coordinates[2]);
    for (int x = 0; x < data->coordinates[0]; ++x) {
        for (int y = 0; y < data->coordinates[1]; ++y) {
            for (int z = 0; z < data->coordinates[2]; ++z) {
                copy.At(x, y, z) = At(x, y, z);
            }
        }
    }
    return copy;
};
M3i& M3i::operator=(const M3i& copy) {
    /*coordinates[0] = copy.Size(0);
    coordinates[1] = copy.Size(1);
    coordinates[2] = copy.Size(2);
    box = copy.box;
    ptr_counter = copy.ptr_counter + 1;*/
    data = copy.data;
    data->ptr_counter++;
    return *this;
}
M3i& M3i::operator=(M3i&& copy) {
    /*coordinates[0] = copy.Size(0);
    coordinates[1] = copy.Size(1);
    coordinates[2] = copy.Size(2);
    box = copy.box;
    ptr_counter = copy.ptr_counter;

    copy.coordinates[0] = 0;
    copy.coordinates[1] = 0;
    copy.coordinates[2] = 0;
    copy.box = nullptr;
    copy.ptr_counter = 0;*/
    data = copy.data;
    copy.data = nullptr;
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

std::istream& M3i::ReadFrom (std::istream& strm)
{
    std::string size;
    strm >> size;
    std::cout<<size<<"\n\r";
    if (strm.rdstate() == std::ios_base::failbit || size != "size:") {
        strm.setstate(std::ios_base::failbit);
        return strm;
    }
    int x;
    int y;
    int z;
    strm >> x >> y >> z;
    if (strm.rdstate() == std::ios_base::failbit || x <= 0 || y <= 0 || z <= 0) {
        strm.setstate(std::ios_base::failbit);
        return strm;
    }
    *this = M3i(x, y, z);
    for (int i = 0; i < x; ++i)
    {
        for (int j = 0; j < y; ++j)
        {
            for (int k = 0; k < z; ++k)
            {
                int number;
                strm >> number;
                if (strm.rdstate() == std::ios_base::failbit) {
                    return strm;
                }
                At(i, j, k) = number;
            }
        }
    }
    return strm;
}

std::ostream& operator << (std::ostream& strm, M3i& r) noexcept {
    return r.WriteTo(strm);
}
std::istream& operator >> (std::istream& strm , M3i& r) {
    return r.ReadFrom(strm);
}
