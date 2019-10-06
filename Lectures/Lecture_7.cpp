#include <iostream>
#include <string>
#include <map>
#include <list>
#include <vector>

using namespace std;
// template
/*
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
    const ThreeD operator++(int neverUsed); // postfix so ++d;
    int &operator[](int k); // return by reference

    // member function
    int getArea() { return height * width; }

    int getVolume() const { return height * width * depth; } // returning const
    // const, otherwise map<ThreeD, int> will not compile
    bool operator<(const ThreeD &t) const { return (ThreeD::getVolume() < t.getVolume()); }

    bool operator==(const ThreeD &t) const { return (ThreeD::getVolume() == t.getVolume()); }
};
*/
template <typename T> class ThreeD {
public:
    T height;
    T width;
    T depth;

    // constructor
    ThreeD() { height = width = depth = 0; }

    ThreeD(T i, T j, T k) {
        height = i;
        width = j;
        depth = k;
    }

    T getVol();
    T getArea();
};

template <class T> T ThreeD<T>::getArea() {
    return 2 * (height * width + height * depth + width * depth);
}

template <class X> X ThreeD<X>::getVol() {
    return height * width * depth;
}

template <class X> ostream& operator<<(ostream& str, const ThreeD<X> &t) {
    str << "(" << t.height << ", " << t.width << ", " << t.depth;
    return str;
}

template <class X> ostream& operator<<(ostream& str, const map<int, ThreeD<X>> &t) {
    for (auto i: t) { str << i; }
    return str;
}

template <class X> ostream& operator<<(ostream& str, const list<ThreeD<X>> &t) {
    for (auto i: t) {
        str << i;
    }
    return str;
}

int main() {
    // template
    ThreeD<int> t1(3, 4, 5);
    ThreeD<float> t2(3.1, 3.5, 3.8);
}
