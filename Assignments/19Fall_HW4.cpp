//HW4: Due Sunday (Oct. 13) at 11:59PM
//Implement functions of class linked_list, class node,  class bag, class item
//All member functions listed need to be implemented.
//You will also need to implement initializer_list, and the needed overloaded operators
//If a class needs destructor, then you need to implement destructor, copy constructor, move constructor, Lvalue operator= and Rvalue operator= for the class
//You will also need to overload operator<< for vector, bag, linked_list, ThreeD using template
//See the sample output for formats when implementing operator<< for all classes
#include <iostream>
#include <stdlib.h>
#include <string>
#include <list>
#include <vector>

using namespace std;

template<class T>
class ThreeD {
public:
    T ht;
    T wid;
    T dep;

    ThreeD() { ht = wid = dep = 0; }

    ThreeD(T i) { ht = wid = dep = i; }

    ThreeD(T a, T b, T c) {
        ht = a;
        wid = b;
        dep = c;
    }

    T getVol() const { return ht * wid * dep; }
    //two objects are equal if their getVol() return the same value.
    bool operator==(const ThreeD<T> &d) { return this->getVol() == d.getVol(); }
};

template<class T>
class node {
public:
    T value;
    node<T> *next;
    node<T> *previous;

    node<T>() {
        next = nullptr;
        previous = nullptr;
    }

    node<T>(T v) {
        value = v;
        next = nullptr;
        previous = nullptr;
    }
};

template<class T>
class linked_list {
public:
    node<T> *head; //position of first node
    node<T> *tail; //position of last node
    linked_list() { head = tail = nullptr; }

    ~linked_list() {
        node<T> *current = head;
        while(current != nullptr) {
            node<T> *next = current->next;
            delete current;
            current = next;
        }
    }

    linked_list(const linked_list<T> &l) {
        if (l.head == nullptr || l.tail == nullptr) {
            head = nullptr;
            tail = nullptr;
        }

        node<T> *current = l.head;
        node<T> *newHead = nullptr, *newTail = nullptr;
        while(current != nullptr) {
            newTail = new node<T>(current->value);
            newTail->previous = newHead;
            if (newHead != nullptr) { newHead->next = newTail; }
            newHead = newTail;
            current = current->next;
        }
        tail = newHead;
        if (newHead != nullptr) {
            while (newHead->previous != nullptr) {
                newHead = newHead->previous;
            }
        }
        head = newHead;
    }

    linked_list(const linked_list<T> &&l) {
        head = l.head;
        tail = l.tail;
        l.head = nullptr;
        l.tail = nullptr;
    }

    linked_list<T> &operator=(const linked_list<T> &l) {
        node<T> *p1 = head;
        while (p1 != nullptr) {
            node<T> *next = p1->next;
            delete p1;
            p1 = next;
        }

        if (l.head == nullptr || l.tail == nullptr) {
            head = nullptr;
            tail = nullptr;
        }

        node<T> *current = l.head;
        node<T> *newHead = nullptr, *newTail = nullptr;
        while(current != nullptr) {
            newTail = new node<T>(current->value);
            newTail->previous = newHead;
            if (newHead != nullptr) { newHead->next = newTail; }
            newHead = newTail;
            current = current->next;
        }
        tail = newHead;
        if (newHead != nullptr) {
            while (newHead->previous != nullptr) {
                newHead = newHead->previous;
            }
        }
        head = newHead;
        return *this;
    }

    linked_list<T> &operator=(linked_list<T> &&l) {
        node<T> *p1 = head;
        while (p1 != nullptr) {
            node<T> *next = p1->next;
            delete p1;
            p1 = next;
        }

        head = l.head;
        tail = l.tail;
        l.head = nullptr;
        l.tail = nullptr;
        return *this;
    }


    void push_front(T t);

    void push_back(T t);

    bool operator==(const linked_list &l) const;

    linked_list(const initializer_list<T> &l): linked_list() {
        auto *p = l.begin();
        node<T> *newHead = nullptr, *newTail = nullptr;
        while (p != l.end()) {
            newTail = new node<T>(*p);
            newTail->previous = newHead;
            if (newHead != nullptr) { newHead->next = newTail; }
            newHead = newTail;
            p++;
        }
        tail = newHead;
        if (newHead != nullptr) {
            while (newHead->previous != nullptr) {
                newHead = newHead->previous;
            }
        }
        head = newHead;
    }

};


template<class X>
class item {
public:
    X data;
    item<X> *next;
    item<X> *previous;

    item<X>(X d) {
        data = d;
        next = nullptr;
        previous = nullptr;
    }
};

template<class X>
class bag {
public:
    item<X> *first; //position of first item
    item<X> *last; //position of last item
    int num_items;

    int size() { return num_items; }

    bag() {
        first = nullptr;
        last = nullptr;
        num_items = 0;
    }

    ~bag(){
        item<X> *current = first;
        while (current != nullptr) {
            item<X> *next = current->next;
            delete current;
            current = next;
        }
    }

    bag(const bag<X> &b) {
        if (b.first == nullptr || b.last == nullptr || b.num_items <= 0) {
            first = nullptr;
            last = nullptr;
        }
        num_items = b.num_items;
        auto *p = b.first;
        item<X> *newHead = nullptr, *newTail = nullptr;
        while (p != nullptr) {
            newTail = new item<X>(p->data);
            newTail->previous = newHead;
            if (newHead != nullptr) { newHead->next = newTail; }
            newHead = newTail;
            p = p->next;
        }
        last = newHead;
        if (newHead != nullptr) {
            while (newHead->previous != nullptr) {
                newHead = newHead->previous;
            }
        }
        first = newHead;
    }

    bag(const bag<X> &&b) {
        num_items = b.num_items;
        first = b.first;
        last = b.last;
        b.first = nullptr;
        b.last = nullptr;
    }

    void operator=(const bag<X> &b) {
        item<X> *p1 = first;
        while (p1 != nullptr) {
            auto *next = p1->next;
            delete p1;
            p1 = next;
        }
        if (b.first == nullptr || b.last == nullptr) {
            first = nullptr;
            last = nullptr;
        }
        num_items = b.num_items;
        auto *p = b.first;
        item<X> *newHead = nullptr, *newTail = nullptr;
        while (p != nullptr) {
            newTail = new item<X>(p->data);
            newTail->previous = newHead;
            if (newHead != nullptr) { newHead->next = newTail; }
            newHead = newTail;
            p = p->next;
        }
        last = newHead;
        if (newHead != nullptr) {
            while (newHead->previous != nullptr) {
                newHead = newHead->previous;
            }
        }
        first = newHead;
    }

    void operator=(const bag<X> &&b) {
        num_items = b.num_items;
        item<X> *p1 = first;
        while (p1 != nullptr) {
            auto *next = p1->next;
            delete p1;
            p1 = next;
        }

        first = b.first;
        last = b.last;
        b.first = nullptr;
        b.last = nullptr;
    }

    void push_back(X d);  //insert an item with data d to the back of the bag
    void push_front(X d); //insert an item with data d to the front of the bag
    void pop_back(); //delete the last item in the bag
    void pop_front(); //delete the first item in the bag
    X &operator[](int i); //Access bag item with index.
    X front() {  //it returns the data of the first item in the bag.
        //if (num_items == 0) do nothing;
        //else return first->data;
        // if (num_items == 0) { return NULL; }
        if (num_items != 0) {
            return first->data;
        }
    }

    X back() { //it returns the data of the last item in the bag
        /*
        if (num_items == 0) do nothing;
        else return last->data;
        */
        // if (num_items == 0) { return NULL; }
        if (num_items != 0) {
            return last->data;
        }
    }

    void clear(); //Delete all items in the bag
    item<X> *find(X d); //return nullptr if no match for find or if the bag is empty.
    //else, return the position of the matched item

    void erase(int index);

    void erase(item<X> *p);

    item<X> *insert(item<X> *p, X d); //insert data d to the position before p and return the position of the inserted item

    bag(const initializer_list<X> &l): bag() {
        auto *p = l.begin();
        item<X> *newHead = nullptr, *newTail = nullptr;
        while (p != l.end()) {
            num_items++;
            newTail = new item<X>(*p);
            newTail->previous = newHead;
            if (newHead != nullptr) { newHead->next = newTail; }
            newHead = newTail;
            p++;
        }
        last = newHead;
        if (newHead != nullptr) {
            while (newHead->previous != nullptr) {
                newHead = newHead->previous;
            }
        }
        first = newHead;
    }
};

template<class T>
void linked_list<T>::push_front(T t) {
    if (head == nullptr || tail == nullptr) {
        head = new node<T>(t);
        tail = head;
    } else {
        auto *newHead = new node<T>(t);
        newHead->next = head;
        head->previous = newHead;
        head = head->previous;
    }
}

template<class T>
void linked_list<T>::push_back(T t) {
    if (head == nullptr || tail == nullptr) {
        head = new node<T>(t);
        tail = head;
    } else {
        tail->next = new node<T>(t);
        tail = tail->next;
    }
}

template<class T>
bool linked_list<T>::operator==(const linked_list<T> &l) const {
    node<T> *p1 = head, *p2 = l.head;
    while (p1 != nullptr && p2 != nullptr) {
        if (p1->value == p2->value) {
            p1 = p1->next;
            p2 = p2->next;
        } else {
            return false;
        }
    }
    return p1 == nullptr && p2 == nullptr;
}

template<class X>
void bag<X>::push_back(X d) {
    if (first == nullptr || last == nullptr) {
        first = new item<X>(d);
        last = first;
        num_items++;
    } else {
        item<X> *p = new item<X>(d);
        p->previous = last;
        last->next = p;
        last = p;
        num_items++;
        // last->next = new item<X>(d);
        // last = last->next;
    }

}

template <class X>
void bag<X>::push_front(X d) {
    if (first == nullptr || last == nullptr) {
        first = new item<X>(d);
        last = first;
    } else {
        auto *newHead = new item<X>(d);
        newHead->next = first;
        first->previous = newHead;
        first = newHead;
    }
    num_items++;
}

template <class X>
void bag<X>::pop_back() {
    if (first == nullptr || last == nullptr || num_items <= 0) { return; }
    item<X> *p = first;
    if (p == last) {
        delete p;
        first = nullptr;
        last = nullptr;
    } else {
        while (p->next != last) {
            p = p->next;
        }
        p->next = nullptr;
        last = p;
    }
    num_items--;
}

template <class X>
void bag<X>::pop_front() {
    if (first == nullptr || last == nullptr || num_items <= 0) { return; }
    item<X> *p = first->next;
    if (p == nullptr) {
        first = nullptr;
        last = nullptr;
    } else {
        first->next = nullptr;
        p->previous = nullptr;
        first = p;
    }
    num_items--;
}

template <class X>
void bag<X>::clear() {
    if (first == nullptr || last == nullptr || num_items <= 0) { return; }
    item<X> *p = first;
    while (p != nullptr) {
        item<X> *next = p->next;
        delete p;
        p = next;
        num_items--;
    }
    first = nullptr;
    last = nullptr;
}

template <class X>
X &bag<X>::operator[](int i) {
    item<X> *p = first;
    for (int k = 0; k < i; k++) {
        p = p->next;
    }
    return p->data;
}

template <class X>
item<X> *bag<X>::find(X d) {
    if (first == nullptr || last == nullptr || num_items <= 0) { return nullptr; }
    item<X> *p = first;
    while (p != nullptr) {
        if (p->data == d) { return p; }
        p = p->next;
    }
    return nullptr;
}

template <class X>
void bag<X>::erase(item<X> *p) {
    if (first == nullptr || last == nullptr || num_items <= 0) { return; }
    if (p == first) {
        auto *next = first->next;
        delete first;
        first = next;
        if (first != nullptr) {
            first->previous = nullptr;
        }
        num_items--;
    } else if (p == last) {
        auto *prev = last->previous;
        delete last;
        last = prev;
        if (last != nullptr) {
            last->next = nullptr;
        }
        num_items--;
    } else {
        auto *current = first, *next = current->next;
        while (next != nullptr) {
            if (next == p) {
                current->next = next->next;
                delete next;
                current->next->previous = current;
                num_items--;
                return;
            }
            current = next;
            next = next->next;
        }
    }
}

template <class X>
void bag<X>::erase(int index) {
    if (first == nullptr || last == nullptr || index < 0 || num_items <= 0) { return; }
    if (index == 0) {
        auto *next = first->next;
        delete first;
        first = next;
        if (first != nullptr) {
            first->previous = nullptr;
        }
        num_items--;
    }else {
        auto *prev = first, *current = prev->next;
        for (int i = 0; i < index - 1; i++) {
            prev = prev->next;
            current = current->next;
        }
        prev->next = current->next;
        delete current;
        if (prev->next != nullptr) {
            prev->next->previous = prev;
        }
        num_items--;
    }
}

template <class X>
item<X> *bag<X>::insert(item<X> *p, X d) {
    if (first == nullptr || last == nullptr || num_items <= 0) {
        first = new item<X>(d);
        last = first;
        this->num_items++;
        return first;
    } else if (p == first){
        item<X> *newHead = new item<X>(d);
        newHead->next = first;
        first->previous = newHead;
        first = newHead;
        this->num_items++;
        return first;
    } else if (p == last){
        item<X> *p1 = new item<X>(d);
        item<X> *current = last->previous;
        current->next = p1;
        p1->previous = current;
        last->previous = p1;
        p1->next = last;
        this->num_items++;
        return p1;
    } else {
        item<X> *current = first;
        while (current->next != nullptr) {
            if (current->next->data == p->data) {
                item<X> *next = current->next;
                item<X> *p1 = new item<X>(d);
                current->next = p1;
                p1->previous = current;
                p1->next = next;
                next->previous = p1;
                this->num_items++;
                return p1;
            }
            current = current->next;
        }
    }
    return nullptr;
}

template <class X>
ostream &operator<<(ostream &str, const ThreeD<X> &t) {
    str << "( " << t.ht << ", " << t.wid << ", " << t.dep << " )";
    return str;
}

template <class X>
ostream &operator<<(ostream &str, const bag<X> &b) {
    if (b.first == nullptr || b.last == nullptr) { return str; }
    item<X> *p = b.first;
    while (p != nullptr) {
        str << p->data << " ";
        p = p->next;
    }
    return str;
}

template <class X>
ostream &operator<<(ostream &str, node<X> &t) {
    str << t.value;
    return str;
}

template <class X>
ostream &operator<<(ostream &str, linked_list<X> &l) {
    if (l.head == nullptr || l.tail == nullptr) { return str; }
    node<X> *current = l.head;
    while (current != nullptr) {
        str << current->value << " ";
        current = current->next;
    }
    return str;
}

template <class X>
ostream &operator<<(ostream &str, vector<X> &v) {
    str << "[";
    for (int i = 0; i < v.size(); i++) {
        str << v[i];
        if (i != v.size() - 1) { str << ", "; }
    }
    str << "]";
    return str;
}

template <class X>
ostream &operator<<(ostream &str, list<X> &l) {
    str << "[";
    int count = 0;
    for (auto i = l.begin(); i != l.end(); i++) {
        str << *i;
        if (count != l.size() - 1) { str << ", "; }
        count++;
    }
    str << "]";
    return str;
}

int main() {
    bag<double> bag_d;
    bag_d.push_back(5.5);
    bag_d.push_back(6.6);
    bag_d.push_front(4.4);
    bag_d.push_front(3.3);
    bag_d.pop_front();
    bag_d.pop_back();
    cout << bag_d << endl;;
    bag<int> bag_i;
    bag_i.push_back(5);
    bag_i.push_back(6);
    bag_i.push_front(4);
    bag_i.push_front(3);
    bag_i.pop_front();
    bag_i.pop_back();
    cout << bag_i << endl;

    ThreeD<int> td3(3), td4(4), td5(5), td6(6), td7(100, 200, 300);
    bag<ThreeD<int>> bag_3D;
    bag_3D.push_back(td5);
    bag_3D.push_back(td6);
    bag_3D.push_front(td4);
    bag_3D.push_front(td3);
    bag_3D.pop_front();
    bag_3D.pop_back();
    cout << bag_3D << endl;;
    cout << bag_3D.front() << bag_3D.back();
    cout << bag_3D[0] << " " << bag_3D[1] << endl;
    bag_3D[1] = td7;
    cout << bag_3D[0] << " " << bag_3D[1] << endl;
    bag_3D.clear();
    cout << bag_3D << endl;;
    cout << bag_3D.size() << endl;
    linked_list<string>ls_1;
    ls_1.push_front("David");
    ls_1.push_front("John");
    ls_1.push_front("Pat");
    ls_1.push_front("Ben");
    ls_1.push_front("Jeff");
    cout << ls_1 << endl;

    linked_list<string>ls_2;
    ls_2.push_front("Wendy");
    ls_2.push_front("Mary");
    ls_2.push_front("Nancy");
    ls_2.push_front("Jennifer");
    cout << ls_2 << endl;

    bag<linked_list<string>> bag_string;

    bag_string.push_back(ls_1);

    bag_string.push_back(ls_2);

    cout << bag_string << endl;
    cout << bag_string[1] << endl;


    ThreeD<double> t10(3.2, 7.4, 8.9), t11(5.6, 7.7, 2.987), t12(4.6, 7.5, 3.1416), t13(55.6, 66.8, 333.45);
    linked_list<ThreeD<double>> LTD1;
    LTD1.push_front(t10);

    LTD1.push_front(t11);
    linked_list<ThreeD<double>> LTD2;
    LTD2.push_front(t13);
    LTD2.push_front(t12);
    LTD2.push_front(t10);
    LTD2.push_front(t11);

    bag<linked_list<ThreeD<double> > > BLTD;
    BLTD.push_back(LTD1);
    BLTD.push_back(LTD2);
    cout << BLTD << endl;

    item<linked_list<ThreeD<double>>> * p2;

    p2 = BLTD.find(LTD1);
    BLTD.erase(p2);
    cout << BLTD << endl;
    BLTD.push_back(LTD1);
    cout << BLTD << endl;
    BLTD.erase(0);
    cout << BLTD << endl;

    vector<ThreeD<int>> V1 = { { 1,2,3 },{ 4,5,6 },{ 7,8,9 } };
    cout << V1 << endl;
    //bag<bag<int>> V2 = { {1,2,3}, {4,5,6}, {7,8,9} };
    vector<bag<ThreeD<int>>> V2 = { { { 1,2,3 },{ 4,5,6 },{ 7,8,9 } },{ { 20,30,40 },{ 11,22, 33 } } };
    cout << V2 << endl;

    list<bag<linked_list<int>>> V3 = { { { 1, 2, 3 },{ 4, 5 } },{ { 6,7 },{ 8, 9, 10 } } };
    cout << V3 << endl;

    bag<int> B10 = { 1,2,3,4,5 };
    bag<int> B11 = B10, B12;
    B12 = B10;
    cout << B10 << endl;
    B10.first->data = 1000;
    cout << B10 << endl;
    cout << B11 << endl;
    cout << B12 << endl;

    bag<list<linked_list<ThreeD<int>>>> B13 = { { { { 1,2,3 },{ 4,5,6 } },{ { 7,8,9 },{ 10,11,12 },{ 13,14,15 } } },{ { { 16,17,18 },{ 19,20,21 },{ 22,23,24 } },{ { 25,26,27 },{ 28,29,30 } },{ { 31,32,33 },{ 34,35,36 },{ 37,38,39 },{ 40,41,42 } } } };
    cout << B13 << endl;

    bag<bag<bag<ThreeD<int>>>> B14 = { { { { 1,2,3 },{ 4,5,6 } },{ { 7,8,9 },{ 10,11,12 },{ 13,14,15 } } },{ { { 16,17,18 },{ 19,20,21 },{ 22,23,24 } },{ { 25,26,27 },{ 28,29,30 } },{ { 31,32,33 },{ 34,35,36 },{ 37,38,39 },{ 40,41,42 } } } };
    cout << B14 << endl;

    bag<linked_list<int>> * p10 = new bag<linked_list<int>>({ { 1,2,3,4 },{ 5,6,7 } });
    cout << *p10 << endl;
    delete p10;
    bag<list<linked_list<ThreeD<int>>>> B15 = { { { { 1,2,3 },{ 4,5,6 } },{ { 7,8,9 },{ 10,11,12 },{ 13,14,15 } } },{ { { 16,17,18 },{ 19,20,21 },{ 22,23,24 } },{ { 25,26,27 },{ 28,29,30 } },{ { 31,32,33 },{ 34,35,36 },{ 37,38,39 },{ 40,41,42 } } } };
    cout << B15 << endl;
    B15.erase(1);
    cout << B15 << endl;
    bag<list<linked_list<ThreeD<int>>>> B16 = { { { { 1,2,3 },{ 4,5,6 } },{ { 7,8,9 },{ 10,11,12 },{ 13,14,15 } } },{ { { 16,17,18 },{ 19,20,21 },{ 22,23,24 } },{ { 25,26,27 },{ 28,29,30 } },{ { 31,32,33 },{ 34,35,36 },{ 37,38,39 },{ 40,41,42 } } } };
    list<linked_list<ThreeD<int>>> V4 = { { { 6,1,1 },{ 2,5,12 } },{ { 9,8,7 },{ 11,10,12 },{ 26,7,15 } } };
    list<linked_list<ThreeD<int>>> V5 = { { { 6,1,1 },{ 2,5,12 } },{ { 9,8,7 },{ 11,10,12 },{ 26,7,5 } },{ { 6,1,1 },{ 2,5,12 } } };
    B16.insert(B16.first, V5);
    cout << B16.front().size() << endl;
    item<list<linked_list<ThreeD<int>>> > * p20=  B16.find(V4);
    if (p20 != nullptr) cout << (p20->data).size() << endl;
    getchar();
    getchar();
    return 0;
}

//The following is a screenshot of a sample output
/*
4.4 5.5
4 5
( 4, 4, 4 ) ( 5, 5, 5 )
( 4, 4, 4 )( 5, 5, 5 )( 4, 4, 4 ) ( 5, 5, 5 )
( 4, 4, 4 ) ( 100, 200, 300 )
0
Jeff Ben Pat John David
Jennifer Nancy Mary Wendy
Jeff Ben Pat John David  Jennifer Nancy Mary Wendy
Jennifer Nancy Mary Wendy
( 5.6, 7.7, 2.987 ) ( 3.2, 7.4, 8.9 )  ( 5.6, 7.7, 2.987 ) ( 3.2, 7.4, 8.9 ) ( 4.6, 7.5, 3.1416 ) ( 55.6, 66.8, 333.45 )
( 5.6, 7.7, 2.987 ) ( 3.2, 7.4, 8.9 ) ( 4.6, 7.5, 3.1416 ) ( 55.6, 66.8, 333.45 )
( 5.6, 7.7, 2.987 ) ( 3.2, 7.4, 8.9 ) ( 4.6, 7.5, 3.1416 ) ( 55.6, 66.8, 333.45 )  ( 5.6, 7.7, 2.987 ) ( 3.2, 7.4, 8.9 )
( 5.6, 7.7, 2.987 ) ( 3.2, 7.4, 8.9 )
[( 1, 2, 3 ), ( 4, 5, 6 ), ( 7, 8, 9 )]
[( 1, 2, 3 ) ( 4, 5, 6 ) ( 7, 8, 9 ) , ( 20, 30, 40 ) ( 11, 22, 33 ) ]
[1 2 3  4 5  , 6 7  8 9 10  ]
1 2 3 4 5
1000 2 3 4 5
1 2 3 4 5
1 2 3 4 5
[( 1, 2, 3 ) ( 4, 5, 6 ) , ( 7, 8, 9 ) ( 10, 11, 12 ) ( 13, 14, 15 ) ] [( 16, 17, 18 ) ( 19, 20, 21 ) ( 22, 23, 24 ) , ( 25, 26, 27 ) ( 28, 29, 30 ) , ( 31, 32, 33 ) ( 34, 35, 36 ) ( 37, 38, 39 ) ( 40, 41, 42 ) ]
( 1, 2, 3 ) ( 4, 5, 6 )  ( 7, 8, 9 ) ( 10, 11, 12 ) ( 13, 14, 15 )   ( 16, 17, 18 ) ( 19, 20, 21 ) ( 22, 23, 24 )  ( 25, 26, 27 ) ( 28, 29, 30 )  ( 31, 32, 33 ) ( 34, 35, 36 ) ( 37, 38, 39 ) ( 40, 41, 42 )
1 2 3 4  5 6 7
[( 1, 2, 3 ) ( 4, 5, 6 ) , ( 7, 8, 9 ) ( 10, 11, 12 ) ( 13, 14, 15 ) ] [( 16, 17, 18 ) ( 19, 20, 21 ) ( 22, 23, 24 ) , ( 25, 26, 27 ) ( 28, 29, 30 ) , ( 31, 32, 33 ) ( 34, 35, 36 ) ( 37, 38, 39 ) ( 40, 41, 42 ) ]
[( 1, 2, 3 ) ( 4, 5, 6 ) , ( 7, 8, 9 ) ( 10, 11, 12 ) ( 13, 14, 15 ) ]
3
2
*/