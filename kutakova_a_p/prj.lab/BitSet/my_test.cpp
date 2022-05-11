#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <iostream>
#include <iosfwd>
#include <vector>
#include <sstream>
#include "../doctest/doctest/doctest.h"
#include "BitSet.h"


/*
bool operator==(const BitSet& l, const BitSet& r) {
    if (l.Size() != r.Size()) {
        return false;
    }
    for (int i = 0; i < l.Size(); ++i) {
        if (l[i] != r[i]) {
            return false;
        }
    }
    return true;
}

TEST_CASE("construct"){
    BitSet set;
    CHECK(set.Size()==0);

    int size = 10;
    BitSet set2(size, false);
    BitSet set3(size, true);
    for (int i=0; i<size;++i){
        bool t = set2[i];
        CHECK(t == false);
        t = set3[i];
        CHECK(t == true);
    }

    BitSet set4(set3);
    BitSet set5(std::move(set3));
    CHECK(set4.Size() == size);
    CHECK(set5.Size() == size);
    for (int i=0; i<size; ++i){
        bool t = set4[i];
        CHECK(t== true);
        t = set5[i];
        CHECK(t== true);
    }
}

TEST_CASE("="){
    int size = 8;
    BitSet set(8, true);
    set[4] = false;
    BitSet set2 = set;
    BitSet set3 = std::move(set);

    CHECK(set.Size() == 0);
    CHECK(set2.Size() == size);
    bool t = set2[0];
    CHECK(t== true);
    t = set2[4];
    CHECK(t == false);

    CHECK(set3.Size() == size);
    t = set3[2];
    CHECK(t == true);
    t = set3[4];
    CHECK(t == false);
}

TEST_CASE("|= &= ^= ~"){
    int size = 8;
    BitSet set(8);
    set[3] = true;
    set[5] = true;
    set[7] = true;
    //00010101

    BitSet set2(size, false);
    set2[0] = true;
    set2[1] = true;
    set2[5] = true;
    //11000100

    set |= set2;
    BitSet answer1(size,true);
    answer1[2] = false;
    answer1[4] = false;
    answer1[6] = false;
    //11010101
    CHECK(set == answer1);

    BitSet answer2(size, false);
    answer2[3] = true;
    answer2[7] = true;
    //00010001

    set ^= set2;
    CHECK(set == answer2);

    ~set;

    BitSet answer3(size, true);
    answer3[3] = false;
    answer3[7] = false;
    //11101110

    CHECK(set == answer3);

    BitSet answer4(size);
    set2[0] = true;
    set2[1] = true;
    set2[5] = true;
    //11000100
    set &= set2;
    CHECK(set == answer4);
}

TEST_CASE("modify"){
    BitSet set(8);
    set.Resize(20);
    BitSet set2(20);
    CHECK(set == set2);

    set.Fill(true);
    BitSet set3(20, true);
    CHECK(set == set3);
}

TEST_CASE("input/output"){
    std::vector<std::string> eof_input{"10101001110111",
                                       " 01100101010"};
    std::vector<std::string> good_input{"111101010100101 ",
                                        "1100101001010  "};

    std::vector<std::string> fail_input{"yagabka ",
                                        "101010010210101",
                                        "10010101r01010101",
                                        ""};

    std::vector<std::string> output{"011001001101101",
                                    "101010010110101",
                                    "10010101001010101",
                                    "0",
                                    "1"};
    BitSet set;

    for (auto str : eof_input) {
        std::stringstream strm;
        strm << str;
        strm >> set;
        CHECK(strm.eof());
    }

    for (auto str : good_input) {
        std::stringstream strm(str);
        strm >> set;
        CHECK(strm.good());
    }

    for (auto str : fail_input) {
        std::stringstream strm(str);
        strm >> set;
        CHECK(strm.fail());
    }

    for (auto str : output) {
        std::stringstream strm(str);
        strm >> set;
        CHECK(strm.eof());
        strm << set;
        CHECK(strm.str() == str);
    }
}

*/
