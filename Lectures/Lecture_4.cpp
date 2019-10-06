//
// Created by WCH on 2019-09-05.
//
#include <iostream>

using namespace std;
// operator overloading

class ThreeD { // user defined data type, members are private by default
public:
    int height;
    int width;
    int depth;

    // constructor
    ThreeD() { height = width = depth = 0; }

    ThreeD(int i, int j, int k) {
        height = i;
        width = j;
        depth = k;
    }

    ThreeD operator+(const ThreeD &t); // attribute of t won't be modified
    ThreeD operator++(); // prefix so ThreeD d; d++ works;
    ThreeD operator++(int neverUsed); // postfix so ++d;
    int &operator[](int k); // return by reference

    // member function
    int getArea() { return height * width * depth; }

    friend istream& operator>>(istream& str, ThreeD& t);
    friend ostream& operator<<(ostream& str, ThreeD& t);
};


ThreeD ThreeD::operator+(const ThreeD &t) {
    ThreeD temp;
    temp.height = height + t.height;
    temp.width = width + t.width;
    temp.depth = depth + t.depth;
    return temp;
}

ThreeD ThreeD::operator++() {
    height++;
    width++;
    depth++;

    return *this; // note return a this object
}

ThreeD ThreeD::operator++(int neverUsed) {
    height++;
    width++;
    depth++;

    return *this; // note return a this object
}

int &ThreeD::operator[](int k) { // return the address of an object
    // function to appear on the left hand side of a statement
    switch (k) {
        case 0:
            return height;
        case 1:
            return width;
        case 2:
            return depth;
    }
}

// input stream for reading lines then assign to ThreeD object
istream &operator>>(istream &str, ThreeD &t) {
    str >> t.height >> t.width >> t.depth;
    return str;
}

ostream &operator<<(ostream &str, ThreeD &t) {
    str << "(" << t.height << ", " << t.width << ", " << t.depth << ")";
    return str;
}


int main() {

    ThreeD t1(3, 4, 5), t2(10, 20, 30), t3;
    t3 = t1 + t2;
    t3++;
    cout << t3.height << endl;

    cin >> t3;
    cout << t3 << endl;

    t3[1] = 100; // overloading [] and return an address of height variable

    return 0;
}