#include <iostream>
#include <vector>

class BitSet {
private:
    class BitHolder;
public:
    BitSet();
    BitSet(const int length, const bool default_value = false);

    BitSet(const BitSet &);
    BitSet(BitSet &&);

    BitSet& operator=(const BitSet &);
    BitSet& operator=(BitSet &&);

    ~BitSet();

    BitSet& operator|=(const BitSet& other);
    BitSet& operator^=(const BitSet& other);
    BitSet& operator&=(const BitSet& other);
    const BitSet operator~() const;

    int Size() const;

    void Resize(const int new_size);
    void Fill(const bool value);
    BitHolder operator[](const int idx);
    bool operator[](const int idx) const;


    void ChangeHolder(std::vector<bool>& data){
        int amount = std::min(data.size(), holder.size());
        for (int i=0; i<amount; ++i){
            holder[i] = data[i];
        }
        for (int i=amount; i<data.size(); ++i){
            holder.push_back(BitHolder(data[i]));
        }
    }
    void Add(const bool val){
        BitHolder h(val);
        holder.push_back(h);
    }

private:
    class BitHolder {
    public:
        BitHolder();
        BitHolder(const bool value);
        BitHolder(const BitHolder&);
        BitHolder(BitHolder &&) = default;

        ~BitHolder() = default;

        BitHolder& operator=(const BitHolder &);
        BitHolder& operator=(bool);
        BitHolder& operator=(BitHolder &&);

        operator bool() const;


        bool Value() const {
            return value;
        }
    private:
        bool value;
    };
    std::vector<BitHolder> holder;
};
// except: first.size != second.size
const BitSet operator|(const BitSet& first, const BitSet& second);
// except: first.size != second.size
const BitSet operator&(const BitSet& first, const BitSet& second);
// except: first.size != second.size
const BitSet operator^(const BitSet& first, const BitSet& second);

std::istream& operator>>(std::istream& istrm, BitSet& bs);
std::ostream& operator<<(std::ostream& ostrm, const BitSet& bs);
