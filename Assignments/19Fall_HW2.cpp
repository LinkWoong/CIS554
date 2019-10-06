//CIS554 HW2
//Due: 11:59PM, Monday ( September 23)
/*
-   Implement two member functions, merge and remove, of the DoublyLinkedList class of HW1.
The descriptions of the two member functions are given below.
-   In the implementation of merge and remove, you are not allowed to modify values of nodes.
You only can modify pointers of nodes.
-   Again, you are not allowed to create new nodes in your implementation.
 No external structures (such as arrays,
linked list, map, etc.) are allowed.  You can use some temporary pointers or variables for your
implementation.
-   In implementing merge and remove, you are not allowed to call sort() in HW1

When you submit your code, do not modify main function.

Do not introduce new functions
In-place implementation is required.
(This means all operations should directly performed on the list.)
*/

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

    void sort();//sort all values based on frequency in ascending order.
    //In case of ties, the smaller values will appear earlier
    //Example:  for list with values  7 6 12 4 33 12 6 6 7
    //sorted results: 4 33 7 7 12 12 6 6 6


    void merge(DoublyLinkedList &L);

    /*
    Given an already sorted DoublyLinkedList (i.e., the result of HW1) , take
    another unsorted list L as function argument, and merge L into the current
    list to form a single sorted DoublyLinkedList.  The result of merge is a sorted list.
    You are not allowed to invoke sort() in HW1 in your implementation of merge.
    */

    void remove(int m, int n);
    /*
    Given an already sorted DoublyLinkedList (i.e., the result of the HW1),
    remove n times of value m from the DoublyLinkedList.
    If n is more than the total number of m's in the DoublyLinkedList,
    then remove all m's from the list.
    If m does not exist in the list, then do nothing.
    The result of remove will be a sorted list.
    You are not allowed to invoke sort() in HW1 in your implementation of remove.
    */
};

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
    Node* p1 = head;
    while (p1 != nullptr) {
        cout << p1->value << " ";
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

void DoublyLinkedList::merge(DoublyLinkedList &L) {
    Node *current = head, *start = nullptr, *end = nullptr;
    Node *merge_current = L.head;

    while (merge_current != nullptr) {
        int count = 0; // count the apperance of d2's node in d1
        while (current != nullptr) {
            if (current->value == merge_current->value) {
                count++;
                if (count == 1) { start = current; }
                end = current;
            }
            current = current->next;
        }

        if (count == 0) { // cannot find the same element in d1
            Node *temp = head; // then search correct position for node insertion
            while (temp->next != nullptr && temp->value < merge_current->value) { //  && temp->next->value != temp->value
                temp = temp->next;
            }
            Node *next = merge_current->next;
            merge_current->next = temp;
            merge_current->previous = temp->previous;
            if (temp->previous != nullptr) {
                temp->previous->next = merge_current;
            } else {
                head = merge_current; // insert the node at the previous position of d1's head
            }
            temp->previous = merge_current;
            merge_current = next;
        } else {
            // there exists same node as d2 in d1
            // retrieve the sublist from d1 starting from node start to node end

            if (start->previous != nullptr && end->next != nullptr) {
                start->previous->next = end->next;
                end->next->previous = start->previous;
                end->next = nullptr;
                start->previous = nullptr;
            } else if (start->previous == nullptr && end->next != nullptr) {
                head = end->next;
                head->previous = nullptr;
            } else if (start->previous != nullptr && end->next == nullptr) {
                tail = start->previous;
                tail->next = nullptr;
            } else { break; }

            Node *substart = tail; // starting node of insertion point
            current = tail;

            // then connect the node with sublist
            Node *next = merge_current->next;
            end->next = merge_current;
            merge_current->previous = end;
            merge_current->next = nullptr;
            end = merge_current;
            merge_current = next;
            count++;

            // now start from the end of d1 to find position to insert the sublist
            // frequency must be the same and value must be smaller
            while (current != nullptr) {
                int temp = 1;
                while (current->previous != nullptr && current->previous->value == current->value) {
                    current = current->previous;
                    temp++;
                }
                // if the node frequency in d1 is smaller, append sublist after it
                if (temp < count) {
                    if (substart->next == nullptr) {
                        // append sublist after the tail
                        start->previous = substart;
                        substart->next = start;
                        tail = end;
                    } else {
                        start->previous = substart->previous;
                        substart->previous->next = start;
                        end->next = substart;
                        substart->previous = end;
                    }
                    break;
                } else if (temp == count) { // if the node frequency is the same
                    // insert sublist after the node which has smaller value
                    if (current->value < start->value) {
                        if (substart->next == nullptr) {
                            start->previous = substart;
                            substart->next = start;
                            tail = end;
                        } else {
                            start->previous = substart->previous;
                            substart->previous->next = start;
                            end->next = substart;
                            substart->previous = end;
                        }
                        break;
                    } else {
                        substart = current;
                    }
                } else {
                    substart = current;
                }
                current = current->previous;
            }
        }
        current = head;
    }
}

void DoublyLinkedList::remove(int m, int n) {
    Node *current = head, *start = nullptr, *end = nullptr;
    int count = 0;
    while (current != nullptr) {
        if (current->value == m) {
            count++;
            if (count == 1) { start = current; }
            end = current;
        }
        current = current->next;
    }

    if (count <= 0) { return; } // does not exist
    if (n >= count) { // remove all of them
        if (start->previous == nullptr) { // head
            head = end->next;
            end->next = nullptr;
            head->previous = nullptr;
        } else if (end->next == nullptr) { // tail
            tail = start->previous;
            start->previous = nullptr;
            tail->next = nullptr;
        } else { // general case
            start->previous->next = end->next;
            end->next->previous = start->previous;
            start->previous = nullptr;
            end->next = nullptr;
        }
    }

    if (n < count) { // remove part of them
        Node *temp = start, *substart = nullptr;
        for (int i = 0; i < n - 1; i++) {
            temp = temp->next;
        }
        substart = temp->next;
        if (start->previous == nullptr) {
            head = end->next;
            end->next = nullptr;
            head->previous = nullptr;
        } else if (end->next == nullptr) {
            tail = start->previous;
            start->previous = nullptr;
            tail->next = nullptr;
        } else {
            start->previous->next = end->next;
            end->next->previous = start->previous;
            start->previous = nullptr;
            end->next = nullptr;
        }

        // then extract the rest
        temp->next = nullptr;
        substart->previous = nullptr;

        // and merge the rest into l1 again
        Node *new_start = tail;
        current = tail;
        count -= n;

        while (current != nullptr) {
            int tmp = 1;
            while (current->previous != nullptr && current->previous->value == current->value) {
                tmp++;
                current = current->previous;
            }

            if (tmp < count) {
                if (new_start == tail) {
                    substart->previous = new_start;
                    new_start->next = substart;
                    tail = end;
                } else {
                    substart->previous = new_start->previous;
                    new_start->previous->next = substart;
                    end->next = new_start;
                    new_start->previous = end;
                }
                break;
            } else if (tmp == count) {
                if(current->value < substart->value) {
                    // cout << "current value is " << current->value << " and new start value is " << new_start->value << endl;
                    if (new_start == tail) {
                        substart->previous = new_start;
                        new_start->next = substart;
                        tail = end;
                    } else {
                        substart->previous = new_start->previous;
                        new_start->previous->next = substart;
                        end->next = new_start;
                        new_start->previous = end;
                    }
                    break;
                } else {
                    new_start = current;
                }
            } else {
                new_start = current;
            }
            current = current->previous;
        }
    }
}

int main() {
    DoublyLinkedList d1, d2;
    d1.makeRandomList(50, 20);
    d1.printForward();
    d1.printBackward();

    d1.sort();
    d1.printForward();
    d1.printBackward();

    d2.makeRandomList(50, 20);
    d1.printForward();
    d1.printBackward();

    d1.merge(d2);
    d1.printForward();
    d1.printBackward();

    d1.remove(13, 3);
    d1.printForward();
    d1.printBackward();
    getchar();
    getchar();
    return 0;
}