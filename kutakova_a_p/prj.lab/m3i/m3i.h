#include <iostream>

class M3i {
    public:
        M3i() = default;
        M3i(const int x, const int y, const int z);
        M3i(const int x, const int y, const int z, int value);
        M3i(const std::initializer_list<std::initializer_list<std::initializer_list<int>>>& list);
        M3i(const M3i&);
        M3i(M3i&&);
        ~M3i() = default;

        M3i& operator=(const M3i&);
        M3i& operator=(M3i&&); //������������ ������������

        M3i Clone() const;
        M3i& Resize(const int x, const int y, const int z);
        int At(const int x, const int y, const int z) const;
        int& At(const int x, const int y, const int z);
        int Size(const int dim) const;
        void Fill(const int value);

        std::ostream& WriteTo(std::ostream& strm) const noexcept;
        std::istream& ReadFrom(std::istream& strm);

    private:
        int* box = nullptr;
        int coordinates[3] = { 0, 0, 0 };
        int* ptr_counter;
};

std::istream& operator>>(std::istream& strm, M3i& m);
std::ostream& operator<<(std::ostream& strm, const M3i& m);