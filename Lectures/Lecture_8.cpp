//
// Created by WCH on 2019-09-24.
//

#include <iostream>
#include <vector>

using namespace std;

int main() {
    int A[5];
    // cout << A[2]; -> error, primitive values are not initialized
    vector<int> v(5); // container comes up with initialized values
    for (auto i: v) { cout << i << endl; }
    vector<int> v2(10, 5); // initialize 10 elements with value 5

    v.assign(6, 9); // if 6th element does not exist, create one with 9
    // otherwise update the 6th element with 9

    v.insert(v.begin() + 2, 8); // insert 8 before v[2]
}