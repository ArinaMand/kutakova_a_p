#include <iostream>

class BitSet {
private:
    class BitHolder;
public:
    BitSet();
    BitSet(const int length, const bool default_value=false);
    BitSet(const BitSet &);
    BitSet(BitSet &&);
    ~BitSet();

    BitSet& operator=(const BitSet &);
    BitSet& operator=(BitSet &&);

    BitSet& operator|=(const BitSet& other);
    BitSet& operator^=(const BitSet& other);
    BitSet& operator&=(const BitSet& other);
    const BitSet operator~() const;

    int Size() const;

    void Resize(const int new_size);
    void Fill(const bool value);
    BitHolder operator[](const int idx);
    bool operator[](const int idx) const;

private:
    class BitHolder {
    public:
        BitHolder() = default;

        BitHolder(const BitHolder &);
        BitHolder(BitHolder &&);

        BitHolder& operator=(const BitHolder &);
        BitHolder& operator=(bool);
        BitHolder& operator=(BitHolder &&);

        operator bool() const;
    private:
        int num;
    };
    BitHolder holder;
    int size;
    int capacity;
    int* data;
};

const BitSet operator|(const BitSet& first, const BitSet& second);
const BitSet operator&(const BitSet& first, const BitSet& second);
const BitSet operator^(const BitSet& first, const BitSet& second);

std::istream& operator>>(std::istream& istrm, BitSet& bs);
std::ostream& operator<<(std::ostream& ostrm, const BitSet& bs);
