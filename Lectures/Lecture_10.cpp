//
// Created by WCH on 2019-10-03.
//
// copy constructor and move constructor
// shallow copy and shallow assign
#include <iostream>
#include <vector>

using namespace std;

void addValue(int &value) {
    // lvalue reference
    cout << value + 10 << endl;
}

void addValue(int &&value) {
    // rvalue reference
    cout << value + 100 << endl;
}

int main() {
    int i{1}, j{2};
    addValue(i); // i is lvalue, calling addValue(int &value);
    addValue(j + 5); // j + 5 is rvalue, calling addValue(int &&value);
    addValue(500); // 500 is rvalue
    addValue(move(i)); // move(i) will temporarily cast i as rvalue
    addValue(i); // i still lvalue
}