#include <iostream>

using namespace std;

void increase(int x) { x++; } // x is local variable
void decrease(int &x) { x--; } // x is address
void arr_increase(int A[]) { A[0]++; }; // arr_increase(int *A) is the same

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

    // member function
    int getArea() { return height * width * depth; }
};

class node {
public:
    int value;
    node *next;

    node() { next = nullptr; }
    node(int i) { value = i; }
};

class linked_list {
public:
    node *head;
    linked_list() { head = nullptr; }

    void MakeList(int m, int n) {
        for (int i = 0; i < m; i++) {
            node *p = new node(rand() % n);
            p->next = head;
            head = p;
        }
    }
};

int main() {
    /** ===========================Week 1 Lecture 2===========================*/
    int *p1 = new int{5}; // (5) will also work
    int j1 = 10;
    p1 = &j1; // will cause memory leak -> the biggest problem for C++
    // A memory leak occurs when you call new without calling a corresponding delete later

    int *p2 = new int[5]{1, 2, 3, 4, 5};
    // delete p2; will cause memory leak
    delete[] p2; // this will delete the whole thing
    p2 = &j1; // no problem

    int B[100000]; // cannot be deleted using delete keyword, because it is not created using new
    int A[3][4] = {{0, 1, 2,  3},
                   {4, 5, 6,  7},
                   {8, 9, 10, 11}};

    cout << A[1][2] << endl; // 6
    cout << *(*(A + 1) + 2) << endl; // A[1][2], *(A + 1) giving the address of A[1]
    cout << *(A[1] + 2) << endl; // A[1][2]
    cout << *(&A[0][0] + 4 * 1 + 2) << endl; // A[1][2], generally A[i][j] = *(&A[0][0] + i*4 + j)

    // call by value / call by reference
    int a = 10;
    increase(a); // call by value: create a new copy to be used inside a function, won't affect
    cout << a << endl;
    decrease(a); // call by reference: it uses original copy inside a function.
    // any manipulation to the original copy will affect the original one.
    cout << a << endl;

    // Array only supports call by reference
    int test[] = {1, 2, 3, 4, 5};
    arr_increase(test);

    for (int i = 0; i < 5; i++) {
        cout << test[i] << ", ";
    }
    cout << endl;

    for (int i: test) { i++; } // call by value which doesn't work.
    for (int i: test) { cout << i << ", "; } // nothing works

    // LinkedList
    ThreeD j, k(3, 4, 5);
    cout << "j has height " << j.height << ", width" << j.width << " and depth" << j.width << endl;

    ThreeD *p = &j;
    cout << (*p).getArea() << endl; // identical
    cout << p->getArea() << endl; // identical
}