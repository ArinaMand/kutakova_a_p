class m3i {
    public:
        m3i() = default;
        m3i(const int x, const int y, const int z);
        m3i(const m3i&);
        m3i(m3i&&);
        ~m3i() = default;

        m3i& operator=(const m3i&);
        m3i& operator=(m3i&&); //присваивание перемещением

        m3i clone() const;
        m3i& resize(const int x, const int y, const int z);
        int at(const int x, const int y, const int z) const;
        int& at(const int x, const int y, const int z);
        int size(const int dim) const;
        void fill(const int value);

    private:
        int* box = nullptr;
        int coordinates[3] = { 0, 0, 0 };
        int* ptr_counter;

    void deleteCurrent();
}