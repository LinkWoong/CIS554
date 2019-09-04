//
// Created by WCH on 2019-09-03.
//
#include <iostream>
using namespace std;

class Node{
public:
    Node* next;
    int value;
    Node() { next = nullptr; }
    Node(int i) { value = i; }
};

class LinkedList {
public:
    Node* head;
    LinkedList() { head = nullptr; }
    void makeList(int m, int n);
    void printList();
    void reverse();
    void sort();
    void removeOne(int k);
};


void LinkedList::makeList(int m, int n) {
    Node* p1;
    for (int i = 0; i < m; i++) {
        p1 = new Node(rand() % n);
        p1->next = head;
        head = p1;
    }
}

void LinkedList::printList() {
    Node* current = head;
    while (current != nullptr) {
        if (current->next != nullptr) {
            cout << current->value << "->";
        } else {
            cout << current->value;
        }
        current = current->next;
    }
    cout << endl;
}

void LinkedList::reverse() {
    Node* prev = nullptr;
    Node* current = head;

    while (current != nullptr) {
        Node* next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    head = prev;
}

void LinkedList::sort() {
    // selection sort implementation
    if (head == nullptr || head->next == nullptr) { return; }
    Node *p1 = head;
    Node *p2, *p_min;
    int min;

    while (p1 != nullptr) {
        min = p1->value;
        p_min = p1;
        p2 = p1->next;

        while (p2 != nullptr) {
            if (p2->value < min) {
                min = p2->value;
                p_min = p2;
            }
            p2 = p2->next;
        }
        p_min->value = p1->value;
        p1->value = min;
        p1 = p1->next;
    }
}

void LinkedList::removeOne(int k) {
    if (!head) { return; }
    Node *p1 = head, *p2;
    if (head->value == k) {
        head = head->next;
        delete p1; // to avoid memory leak
        return;
    }

    p2 = p1->next;
    while (p2 != nullptr) {
        if (p2->value == k) {
            p1->next = p2->next;
            delete p2;
            return;
        }
        p1 = p2;
        p2 = p2->next;
    }
}

int main() {
    LinkedList l1;
    l1.makeList(10, 10);
    l1.printList();
    l1.reverse();
    l1.printList();
    l1.sort();
    l1.printList();
}
