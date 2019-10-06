//
// Created by WCH on 2019-08-30.
//
#include <iostream>
using namespace std;

int main() {
    int arr[5] = {1, 2, 3, 4, 5};
    std::cout << *arr << std::endl; // array name without index is the address of
    // its first element. *arr prints the same content as arr[0];

    cout << (*arr + 2) << endl; // arr[2]
    cout << 2[arr] << endl; // both 2[arr] and arr[2] will be converted to *(A+2)
    // C++ won't check for out-of-bound error

    // dynamic memory allocation
    int* p2;
    p2 = new int(100); // new is a function which asks system to create a storage space
    // and return address of this memory space
    // whatever object created by new is a global object
    delete p2; // return the object pointed by p2 to the system
    // delete only can be applied to the dynamic object (new)
    p2 = arr + 1;
    // delete p2;
    cout << *p2 << endl;

    p2 = new int[10];
    p2[3] = 25;
    cout << *(p2 + 3) << "is the same as" << p2[3] << endl;
    int i1 = *(p2 + 3);
    *(p2 + 3) = 10000;

    // pointer can never be deleted
    // delete p2; // only delete the first element
    delete [] p2; // delete the entire array
    p2 = arr;

    cout << sizeof(arr) << endl;
}