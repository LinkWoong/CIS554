//CIS554 HW1 by Chenhui Wang
//Due: 11:59PM, Friday (September 13)
//Do not modify main function.
//Do not introduce new functions
//In-place implementation is required.

#include <iostream>

using namespace std;

class Node {
public:
    int value;
    Node *next;
    Node *previous;

    Node(int i) {
        value = i;
        next = previous = nullptr;
    }

    Node() { next = previous = nullptr; }
};

class DoublyLinkedList {
public:
    Node *head;
    Node *tail;

    DoublyLinkedList() { head = tail = nullptr; }

    void makeRandomList(int m, int n);

    void printForward();

    void printBackward();

    //implement the following member functions:
    void sort();//sort all values based on frequency in ascending order.
    //In case  of ties, the smaller values will appear earlier
    //Example:  for list with values  7 6 12 4 33 12 6 6 7
    //sorted results: 4 33 7 7 12 12 6 6 6

    //If your algorithm is inefficient, you might lose points.
    //You will not modify L.
};


void DoublyLinkedList::sort() {
    // first sort the array by value ascending
    Node *begin = head, *current;
    while (begin != nullptr) {
        current = begin->next;
        while (current != nullptr) {
            if (current->value < begin->value) {
                int tmp = current->value;
                current->value = begin->value;
                begin->value = tmp;
            }
            current = current->next;
        }
        begin = begin->next;
    }

    delete begin;
    // then swap nodes based on their frequency
    Node *fcurrent = head;

    int k = 0, count = 0;
    Node *head1 = head;
    while (head1 != nullptr) {
        k++; // count the length of list
        head1 = head1->next;
    }

    int curNum = 0;
    for (int i = 1; i <= k; i++) { // frequency of each element must between 1 and the length of list (inclusive)
        while (fcurrent != nullptr) {
            curNum = 1;
            while (fcurrent->next != nullptr && fcurrent->next->value == fcurrent->value) {
                fcurrent = fcurrent->next;
                curNum++;
            }
            if (curNum == i) { // found
                Node *now = head;
                for (int j = 0; j < count; j++) { // move the starting node by count step
                    // to find the element to be swapped
                    now = now->next;
                }

                Node *swap = fcurrent;
                for (int m = 1; m < i; m++) {
                    swap = swap->previous; // find the element to be swapped
                }

                for (int m = 0; m < i; m++) { // swap value
                    int tmp = swap->value;
                    swap->value = now->value;
                    now->value = tmp;

                    if (i != 1) {
                        now = now->next;
                        swap = swap->next;
                    }
                    count++; // after each swap, update the count
                }
            }
            fcurrent = fcurrent->next;
        }

        // after frequency sorting for each i, sort the rest array by value again
        begin = head;
        for (int n = 0; n < count; n++) {
            begin = begin->next;
        }
        while (begin != nullptr) {
            current = begin->next;
            while (current != nullptr) {
                if (current->value < begin->value) {
                    int tmp = current->value;
                    current->value = begin->value;
                    begin->value = tmp;
                }
                current = current->next;
            }
            begin = begin->next;
        }
        fcurrent = head;
    }
}

void DoublyLinkedList::makeRandomList(int m, int n) {

    for (int i = 0; i < m; i++) {
        Node *p1 = new Node(rand() % n);
        p1->previous = tail;
        if (tail != nullptr) tail->next = p1;
        tail = p1;
        if (head == nullptr) head = p1;
    }
}

void DoublyLinkedList::printForward() {
    cout << endl;
    Node *p1 = head;
    while (p1 != nullptr) {
        if (p1->next != nullptr) { cout << p1->value << "->"; }
        else { cout << p1->value; }
        p1 = p1->next;
    }
}

void DoublyLinkedList::printBackward() {
    cout << endl;
    Node *p1 = tail;
    while (p1 != nullptr) {
        cout << p1->value << " ";
        p1 = p1->previous;
    }
}

int main() {
    DoublyLinkedList d1;
    d1.makeRandomList(40, 20); // (20, 10), (10, 15)
    d1.printForward();
    d1.printBackward();

    d1.sort();
    cout << endl;
    d1.printForward();
    d1.printBackward();

    // getchar();
    // getchar();
    return 0;
}

/*
 * // swap nodes pointed by p1 and p2
    Node *p1 = d1.head->next;
    Node *p2 = d1.tail->previous;

    Node *p3 = p1->next;
    Node *p4 = p1->previous;
    p1->next->previous = p2;
    p2->next->previous = p1;
    p1->previous->next = p2;
    p2->previous->next = p1;
    p1->next = p2->next;
    p2->next = p3;
    p1->previous = p2->previous;
    p2->previous = p4;

    // swap two consecutive nodes
    p1 = d1.head->next;
    p2 = d1.head->next->next;

    p4 = p1->previous;

    p2->next->previous = p1;
    p1->previous->next = p2;
    p1->next = p2->next;
    p1->previous = p2;
    p2->next = p1;
    p2->previous = p4;


        prev = adding->next;
        while (prev != nullptr) {
            scurrent = prev->next;
            while (scurrent != nullptr) {
                if (scurrent->value < prev->value) {
                    int temp = scurrent->value;
                    scurrent->value = prev->value;
                    prev->value = temp;
                    prev = prev->next;
                    printForward();
                }
                scurrent = scurrent->next;
            }
            prev = prev->next;
        }
    if (adding->next != fcurrent) {
                    Node *atail = adding->next;
                    Node *after = fcurrent->next;
                    adding->next = fcurrent;
                    fcurrent->previous = adding;
                    fcurrent->next = atail;
                    atail->previous = fcurrent;
                    prev->next = after;

                    adding = fcurrent;
                    fcurrent = after;
                } else {
                    adding = fcurrent;
                    prev = current;
                    fcurrent = fcurrent->next;
                }

 */

/*
    Node *newHead = new Node(0);
    Node *current = head, *pre = newHead;
    Node *next = nullptr;
    // insertion sort based on values
    while (current != nullptr) {
        next = current->next;
        while (pre->next != nullptr && pre->next->value < current->value) {
            pre = pre->next;
        }
        current->next = pre->next;
        pre->next = current;
        current->previous = pre;

        pre = newHead;
        current = next;
    }
    head = newHead->next;
     */


/*
            while (temp != nullptr) {
                if (temp->next != nullptr && temp->next->value != temp->value && temp->value < merge_current->value) {
                    temp = temp->next;
                } else {
                    if (temp == head) {
                        Node *next = merge_current->next;
                        merge_current->next = temp;
                        temp->previous = merge_current;
                        merge_current->previous = nullptr;
                        head = merge_current;
                        merge_current = next;
                    } else {
                        // if (merge_current == nullptr) { break; }
                        Node *next = merge_current->next;
                        merge_current->previous = temp->previous;
                        if (temp->previous != nullptr) {
                            temp->previous->next = merge_current;
                        }
                        merge_current->next = temp;
                        temp->previous = merge_current;
                        merge_current = next;
                    }
                    break;
                }
                temp = temp->next;
            }*/

// int temp = 1;
/*
while (current != nullptr) {
    if (current->previous != nullptr && current->previous->value == current->value) {
        temp++;
    } else {
        if ((temp < count) || (temp == count && current->value < start->value)) {
            if (substart == tail) {
                substart->next = start;
                start->previous = substart;
                tail = end;
                break;
            } else {
                start->previous = substart->previous;
                substart->previous->next = start;
                substart->previous = end;
                end->next = substart;
                break;
            }
        }

        if (temp == count) {
            if (current->value > start->value) {
                substart = current;
            }
        } else { substart = current; }
        temp = 1;
    }
    current = current->previous;
}*/