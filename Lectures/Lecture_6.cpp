#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <map>

// using namespace std;
// Standard Template Library (STL)
// vector, list, map, queue, stack, set

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
    int getArea() { return height * width; }

    int getVolume() const { return height * width * depth; } // returning const
    // const, otherwise map<ThreeD, int> will not compile
    bool operator<(const ThreeD &t) const { return (ThreeD::getVolume() < t.getVolume()); }

    bool operator==(const ThreeD &t) const { return (ThreeD::getVolume() == t.getVolume()); }
};

std::ostream &operator<<(std::ostream &str, const ThreeD &t) {
    str << "(" << ", " << t.width << ", " << t.depth << ")";
    return str;
}

std::ostream &operator<<(std::ostream &str, const std::vector<int> &v) {
    str << "[";
    for (auto i: v) { str << i << ", "; }
    str << "]";
    return str;
}

std::ostream &operator<<(std::ostream &str, const std::vector<ThreeD> &v) {
    str << "[";
    for (auto i: v) { str << i << ", "; }
    str << "]";
    return str;
}

std::ostream &operator<<(std::ostream &str, const std::map<int, std::string> m) {
    str << "{";
    for (std::pair<int, std::string> i: m) {
        std::cout << "{" << i.first << ", " << i.second << "}," << std::endl;
    }
    str << "}";
}

std::ostream &operator<<(std::ostream &str, const std::map<ThreeD, int> m) {
    str << "{";
    for (std::pair<ThreeD, int> i: m) {
        std::cout << "{" << i.first << ", " << i.second << "}," << std::endl;
    }
    str << "}";
}

int main() {
    std::vector<int> v1 = {0, 1, 2, 3, 4};
    // front: first element, back: last element
    std::cout << v1.size() << v1.front() << v1.back() << std::endl;
    v1.push_back(5);
    v1.pop_back();

    // iterator(a special pointer) to iterate through vector v1
    std::vector<int>::iterator iter = v1.begin();
    // auto iter = v1.begin();
    while (iter != v1.end()) {
        std::cout << *iter << std::endl;
        iter++;
    }

    // indexing: size_t: non negative integer
    for (size_t i = 0; i < v1.size(); i++) {
        std::cout << v1[i] << std::endl;
    }

    iter = std::find(v1.begin(), v1.end(), 3); // find value 3 in vector 1
    // if not found, return v1.end();

    if (iter != v1.end()) { v1.erase(iter); } // erase the element given by
    std::list<int> l1 = {5, 2, 11, 1, 6};
    l1.push_back(1);
    l1.push_front(100);
    l1.pop_back();
    l1.pop_front();

    // iterator
    std::list<int>::iterator iter2 = l1.begin();
    while (iter2 != l1.end()) {
        std::cout << *iter2 << std::endl;
    }

    // indexing for list is not allowed.
    l1.sort(); // list has built-in sorting function

    iter2 = std::find(l1.begin(), l1.end(), 3);
    l1.remove(2); // won't crash even value 2 is not contained in l1.

    // generics
    ThreeD t1(3, 4, 5), t2(1, 8, 7), t3(2, 3, 9);
    // std::vector<ThreeD> v2 = {t1, t2, t3};
    std::list<ThreeD> l2 = {t1, t2, t3};
    l2.sort(); // use operator overloading to define comparison between two ThreeD objects
    // define criteria for comparing two ThreeD Objects

    std::vector<ThreeD> v3 = {t1, t2, t3};
    std::cout << v3 << std::endl;

    // map, automatically sort element based on the key (Red-Black tree based)
    std::map<int, std::string> m1 = {{11, "Ass"},
                                     {8,  "Link"},
                                     {10, "wang"}};

    for (std::pair<int, std::string> i: m1) {
        std::cout << i.first << " " << i.second << std::endl;
    }

    // add new element to map
    m1[3] = "fuck"; // add {3, "fuck"}
    std::cout << m1 << std::endl;
    std::map<ThreeD, int> m2 = {{t1, 1} ,{t2, 2}, {t3, 3}};
    std::cout << "m2 is " << m2 << std::endl;

    // map iterator
    auto it = m1.begin();
    while (it != m1.end()) { std:: cout << it->first << it->second << std::endl; }

    // delete map key-value pair thru key
    m2.erase(t1);
    return 0;
}