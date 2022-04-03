class M3i {
    public:
        M3i() = default;
        M3i(const int x, const int y, const int z);
        M3i(const M3i&);
        M3i(M3i&&);
        ~M3i() = default;

        M3i& operator=(const M3i&);
        M3i& operator=(M3i&&); //присваивание перемещением

        M3i clone() const;
        M3i& resize(const int x, const int y, const int z);
        int at(const int x, const int y, const int z) const;
        int& at(const int x, const int y, const int z);
        int size(const int dim) const;
        void fill(const int value);

    private:
        int* box = nullptr;
        int coordinates[3] = { 0, 0, 0 };
        int* ptr_counter;
};
