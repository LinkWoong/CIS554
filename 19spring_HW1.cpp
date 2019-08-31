//CIS554 HW1
//Due: 11:59PM, Friday (Feb. 1st)
//Do not modify main funciton.
//Do not introduce new functions

#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Freq {
    unordered_map<int, int> *map{};
    unordered_map<int, int> *index_map{};
public:
    Freq(unordered_map<int, int> *map, unordered_map<int, int> *index_map) :
            map{map}, index_map{index_map} {};


    // map{map}左边的是要初始化的成员变量，右边是初始化内容
    bool operator()(int i, int j) {
        size_t frequency_i = (*map)[i];
        size_t frequency_j = (*map)[j];
        size_t index_i = (*index_map)[i];
        size_t index_j = (*index_map)[j];

        if (frequency_i != frequency_j) {
            return frequency_i > frequency_j;
        }
        return index_i < index_j;
    }
};


class node {
public:
    int value;
    node *next;
    node *previous;

    node(int i) {
        value = i;
        next = previous = nullptr;
    }

    node() { next = previous = nullptr; }
};

class doubly_linked_list {
public:
    node *head;
    node *tail;

    doubly_linked_list() { head = tail = nullptr; }

    void make_random_list(int m, int n);

    void print_forward();

    void print_backward();

    // implement the following member functions:

    void sort();//sort all values based on frequency.

    // In case of ties, the values occur earlier will appear earlier
    // Example: for list with values  7 6 12 4 33 12 6 6 7
    // sorted results: 6 6 6 7 7 12 12 4 33

    doubly_linked_list operator+(const doubly_linked_list &L);
    // L is read-only
    // return a frequency_sorted list by combining the current frequency_sorted list with another
    // frequency_sorted list L
    // If your algorithm is inefficient, you might lose points.
    // The values in the current list occur before that of L.
    // You will not modify L.

    void insert(int k);

    // after insert(12) to the above,
    // we have 6 6 6 12 12 12 7 7 4 33
    // Insert value k to a frequency_sorted list
    // After insert, the list remains frequency_sorted


    void remove(int k, int n);
    //remove value k n times from a frequency_sorted list.
    //if there are fewer than n occurrences of k, then remove all occurrences of k
    //The final result will remain a frequency_sorted list.
    //For example, if the list is 7 7 7 2 2 4 4 5 5 44 3
    //After remove(2,5), the list will become 7 7 7 4 4 5 5 44 3
};

void doubly_linked_list::make_random_list(int m, int n) {
    for (int i = 0; i < m; i++) {
        node *p1 = new node(rand() % n);
        p1->previous = tail;
        if (tail != nullptr) { tail->next = p1; }
        tail = p1;
        if (head == nullptr) { head = p1; }
    }
}

void doubly_linked_list::print_forward() {
    cout << endl;
    node *current = head;
    while (current != nullptr) {
        cout << current->value << " ";
        current = current->next;
    }
}

void doubly_linked_list::print_backward() {
    cout << endl;
    node *current =
            tail;
    while (current != nullptr) {
        cout << current->value << " ";
        current = current->previous;
    }
}

void doubly_linked_list::sort() {
    node *current = head;
    vector<int> arr;
    int count = 1;
    unordered_map<int, int> index_map;
    while (current != nullptr) {
        arr.push_back(current->value);
        if (index_map[current->value] == 0) {
            index_map[current->value] = count;
        }
        current = current->next;
        count++;
    }

    unordered_map<int, int> map;
    for (auto i: arr) {
        map[i]++;
    }

    Freq freq(&map, &index_map);
    std::sort(arr.begin(), arr.end(), freq);

    cout << endl;
    current = head;
    count = 0;
    while (current != nullptr) {
        current->value = arr.at(count);
        current = current->next;
        count++;
    }
}

doubly_linked_list doubly_linked_list::operator+(const doubly_linked_list &L) {
    return doubly_linked_list();
}

void doubly_linked_list::insert(int k) {
    node * current = head;
    while (current != nullptr) {
        if (current->next->value == k) {
            node *next = current->next;
            node *newNode = new node(k);
            current->next = newNode;
            newNode->next = next;
        }
        current = current->next;
    }
}

void doubly_linked_list::remove(int k, int n) {
    cout << "remove" << endl;
}

void print_array(vector<int> v) {
    for (auto i: v) {
        cout << i << " ";
    }
    cout << endl;
}
/*
int main() {
    doubly_linked_list d1;
    d1.make_random_list(15, 10);
    cout << "before sorting ";
    d1.print_forward();
    // d1.print_backward();

    cout << endl;
    cout << "after sorting ";
    d1.sort();
    d1.print_forward();
    cout << endl;
}
*/
/*
    // two ways to call a constructor
    struct S {
        int n;
        S(int); // constructor declaration
        // 1. use default S() takes empty and initialize n(7) with 7, empty function body{}
        S() : n(7) {} // constructor definition.
                      // ": n(7)" is the initializer list
                      // ": n(7) {}" is the function body
    };
    // 2. use S(int x) which takes x as an argument and initialize n with x;
    S::S(int x) : n{x} {} // constructor definition. ": n{x}" is the initializer list

    int main()
    {
        S s; // calls S::S()
        std::cout << s.n << std::endl; // n = 7
        S s2(10); // calls S::S(int)
        std::cout << s2.n << std::endl; // n2 = 10
    }
*/