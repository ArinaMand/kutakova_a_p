#include "BitSet.h"
#include <algorithm>
#include <stdexcept>
#include <iostream>

BitSet::BitHolder& BitSet::BitHolder::operator=(const BitHolder& val){
    *this = val;
    return *this;
}

BitSet::BitHolder& BitSet::BitHolder::operator=(BitHolder&& val){
    *this = val;
    return *this;
}

BitSet::BitHolder& BitSet::BitHolder::operator=(const bool val){
    value = val;
    return *this;
}

BitSet::BitHolder::operator bool() const{
    return true;
}

BitSet::BitHolder::BitHolder(const bool val){
    value = val;
}



BitSet::BitSet(){
    holder = {};
}
BitSet::BitSet(const int length, const bool default_value){
    std::cout<<default_value;
    BitHolder x(default_value);
    for (int i=0; i<length; ++i){
        holder.push_back(x);
    }
}

BitSet::BitSet(const BitSet & copy){
    holder = copy.holder;
}
BitSet::BitSet(BitSet && copy) = default;

BitSet& BitSet::operator=(const BitSet& copy){
    holder = copy.holder;
    return *this;
}
BitSet& BitSet::operator=(BitSet && copy){
    holder = copy.holder;
    return *this;
}

BitSet::~BitSet() = default;

BitSet& BitSet::operator|=(const BitSet& other){
    int size = std::min(holder.size(), other.holder.size());
    for (int i=0; i<size; ++i){
        this[i] = this[i] | other[i];
    }
    if (other.holder.size()>size){
        Resize(other.holder.size());
    }
    return *this;
}
BitSet& BitSet::operator^=(const BitSet& other){
    int size = std::min(holder.size(), other.holder.size());
    for (int i=0; i<size; ++i){
        this[i] = this[i] ^ other[i];
    }
    if (other.holder.size()>size){
        Resize(other.holder.size());
    }
    return *this;
}
BitSet& BitSet::operator&=(const BitSet& other){
    int size = std::min(holder.size(), other.holder.size());
    for (int i=0; i<size; ++i){
        this[i] = this[i] & other[i];
    }
    if (other.holder.size()>size){
        Resize(other.holder.size());
    }
    return *this;
}
const BitSet BitSet::operator~() const{
    BitSet set(holder.size());
    for (int i=0; i<holder.size(); ++i){
        set.Add(!holder[i]);
    }
    return set;
}

int BitSet::Size() const{
    return holder.size();
}

void BitSet::Resize(const int new_size){
    for (int i=holder.size(); i<new_size; ++i){
        Add(false);
    }
}
void BitSet::Fill(const bool value){
    int size = Size();
    for (int i=0; i<size; ++i){
        holder[i] = new BitHolder(value);
    }
}
BitSet::BitHolder BitSet::operator[](const int idx){
    return holder[idx];
}
bool BitSet::operator[](const int idx) const{
    return holder[idx].Value();
}

const BitSet operator|(const BitSet& first, const BitSet& second){
    return BitSet(first) |= second;
}

const BitSet operator&(const BitSet& first, const BitSet& second){
    return BitSet(first) &= second;
}
const BitSet operator^(const BitSet& first, const BitSet& second){
    return BitSet(first) ^= second;
}

std::istream& operator>>(std::istream& strm, BitSet& bs) {
    std::string num;
    strm >> num;
    if (strm.fail()) {
        return strm;
    }
    if (num.size() == 0) {
        strm.setstate(std::ios_base::failbit);
        return strm;
    }
    std::vector<bool> b(num.begin(), num.end());
    bs.ChangeHolder(b);
    return strm;
}
std::ostream& operator<<(std::ostream& strm, const BitSet& bs){
    std::string answer;
    for (int i=0; i<bs.Size(); ++i){
        bool c = bs[i];
        answer.append( c==0 ? "0":"1");
    }
    strm << answer;
    return strm;
}