//
// Created by WCH on 2019-09-26.
//

// copy constructor and move constructor
// shallow copy and shallow assign
#include <iostream>
#include <vector>

using namespace std;

class SimpleData {
public:

    int first;
    int *pSecond;
    int *pThird;

    SimpleData() { pSecond = pThird = nullptr; }

    SimpleData(int i1, int i2, int i3) {
        first = i1;
        pSecond = new int(i2);
        pThird = new int(i3);
    }
};


class BigData {
public:
    bool is_Hundred;
    vector<int> *pBigVector;

    BigData() {
        pBigVector = new vector<int>;
        is_Hundred = false;
    }

    BigData(int i) {
        pBigVector = new vector<int>(i); // initialize an vector with size i
        if (i >= 100) { is_Hundred = true; }
        else { is_Hundred = false; }
    }

    BigData(const BigData &b);
    // destructor
    // automatically called when program ends
    ~BigData() { delete pBigVector; };

    void print();
    BigData getThreeTimes();
};

void BigData::print() {
    for (int i: *pBigVector) { cout << i << endl; }
}

BigData BigData::getThreeTimes() {
    // default copy is shallow
    // To implement deep copy, re-implement copy constructor
    BigData temp;
    temp.is_Hundred = is_Hundred;
    *temp.pBigVector = *pBigVector;
    for (int &i: *pBigVector) { i *= 3; }
    // have to manually delete stuff after this naming scope
    return temp; // return local variable may cause memory leak
}

BigData::BigData(const BigData &b): BigData() {
    is_Hundred = b.is_Hundred;
}

int main() {
    SimpleData s1(2, 3, 4);
    SimpleData s2{s1}; // shallow copy (invoking copy constructor)
    SimpleData s3(5, 6, 7), s4; // -> initialize s2 with content in s1
    // int i = 10, j = i;
    *s1.pSecond = 40;
    *s2.pThird = 50; // they both changed: s1 = (2, 40, 50); s2 = (2, 40, 50);
    s4 = s3; // shallow assign

    // Destructor & return by value
    BigData b1(10), b2;
    for (size_t i = 0; i <= b1.pBigVector->size(); i++) {
        (*b1.pBigVector)[i] = i;
    }

    b2 = b1.getThreeTimes(); // points to nowhere because destructor is executed
    // lvalue and rvalue
}