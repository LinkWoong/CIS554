//template and Multi_leve_Containers
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <map>

using namespace std;

template<class T>
class ThreeD {  //template allow us to view
//data type as argument passed to a stucture, such as a class, a funciton, etc.
public:
    T ht;
    T wid;
    T dep;

    ThreeD() { ht = wid = dep = (T) 0; }

    ThreeD(T i, T j, T k) {
        ht = i;
        wid = j;
        dep = k;
    }

    T getVol() { return ht * wid * dep; }
    T getArea();
};

template <class X>
X ThreeD<X>::getArea() {
    return (ht * wid + ht * dep + wid * dep);
}

template <class X>
ostream& operator<<(ostream& str, const ThreeD<X>& t) {
    str << t.ht << " " << t.dep << " " << t.wid << endl;
    return str;
}

template <class X>
ostream& operator<<(ostream& str, const list<ThreeD<X>> &t) {
    str << "[";
    for (auto i: t) { str << i << ", "; }
    str << "]";
    return str;
}
template <class X1, class X2>
ostream& operator<<(ostream& str, const map<X1, X2>& m) {
    str << "{";
    for (pair<X1, X2> i: m) { str << i.first << i.second; }
    str << "}";
    return str;
}


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