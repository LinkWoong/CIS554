//CIS554 HW3 by Chenhui Wang
//NetID: cwang106 SUID: 334027643
//Due: Saturday (10/5) at 11:59PM

#include <iostream>
#include <list>
#include <map>

using namespace std;

class course {
public:

    string name;
    int section;
    int credits;

    course() {}

    course(string n, int s, int c) {
        name = n;
        section = s;
        credits = c;
    }

    //Add additional needed member functions and implement them.
    //You also need to implement some needed functions for overloading operator<< .
    bool operator<(const course *c) const { return name < c->name; }
};

ostream &operator<<(ostream &str, const course &c);

ostream &operator<<(ostream &str, const list<course *> &list);

ostream &operator<<(ostream &str, const map<int, list <course * > *> &id);

ostream &operator<<(ostream &str, const map<int, map<int, list <course * > *> > &DB);

//Implement the following functions

void add_student(map<int, map<int, list<course *> *> > &DB, int id);

void remove_student(map<int, map<int, list<course *> *> > &DB, int id);

void add_course(map<int, map<int, list<course *> *> > &DB, int semester, int id,
                course c); //20171 Spring semester of 2017; 20172: Fall semester of 2017

void drop_course(map<int, map<int, list<course *> *> > &DB, int semester, int id, course c);

void print_student_semester_courses(map<int, map<int, list<course *> *> > &DB, int semester, int id);

void print_student_all_courses(map<int, map<int, list<course *> *> > &DB, int id);

void print_DB(map<int, map<int, list<course *> *> > &DB);

//For the print functions, you need to add more functions to overload operator<<.
//for example print_DB is simply cout << DB;
//Courses in a semester are sorted alphabetically.

int main() {
    //Do not change code for main function
    map<int, map<int, list <course*>*> > DB;
    add_student(DB, 11111);
    course C1("CIS554", 1, 3), C2("CSE674", 1, 3), C3("MAT296", 8, 4), C4("WRT205", 5, 3);

    add_course(DB, 20171, 11111, C1);
    add_course(DB, 20171, 11111, C4);
    add_course(DB, 20171, 11111, C3);
    add_course(DB, 20171, 11111, C2);
    print_student_semester_courses(DB, 20171, 11111);

    drop_course(DB, 20171, 11111, C1);
    print_student_semester_courses(DB, 20171, 11111);

    add_course(DB, 20172, 11111, C2);
    add_course(DB, 20172, 11111, C4);
    add_course(DB, 20172, 11111, C3);
    add_course(DB, 20172, 11111, C1);
    print_student_all_courses(DB, 11111);

    add_student(DB, 11112);
    add_course(DB, 20171, 11112, C2);
    add_course(DB, 20171, 11112, C4);
    add_course(DB, 20171, 11112, C3);
    add_course(DB, 20171, 11112, C1);
    print_student_semester_courses(DB, 20171, 11112);

    add_course(DB, 20172, 11112, C2);
    add_course(DB, 20172, 11112, C4);
    add_course(DB, 20172, 11112, C3);
    add_course(DB, 20172, 11112, C1);
    print_student_semester_courses(DB, 20172, 11112);
    print_student_all_courses(DB, 11112);
    print_DB(DB);
    remove_student(DB, 11111);
    print_DB(DB);
    getchar();
    getchar();
    return 0;
}

void add_student(map<int, map<int, list<course *> *> > &DB, int id) {
    if (DB.find(id) != DB.end()) { return; } // student already existed in database
    map<int, list<course *> *> temp;
    DB[id] = temp;
}

void remove_student(map<int, map<int, list<course *> *> > &DB, int id) {
    if (DB.find(id) == DB.end()) { return; }
    for (auto p1: DB[id]) {
        for (auto &p2: *DB[id][p1.first]) {
            // delete courses
            delete p2;
        }
        // delete list
        delete DB[id][p1.first];
    }
    DB.erase(id); // delete the student
}

void add_course(map<int, map<int, list<course *> *> > &DB, int semester, int id, course c) {
    if (DB[id].find(semester) == DB[id].end()) { // semester does not exist
        auto *current = new list<course *>;
        DB[id][semester] = current;
        // insert the course at the beginning
        current->insert(current->begin(), new course(c.name, c.section, c.credits));
    } else {
        // check existence of course
        for (auto i = DB[id][semester]->begin(); i != DB[id][semester]->end(); i++) {
            if ((*i)->name == c.name) {
                return;
            } else if (c < *i) {
                DB[id][semester]->insert(i, new course(c.name, c.section, c.credits));
                return;
            }
        }
        // c is the greatest course in this list, so add at the end
        DB[id][semester]->push_back(new course(c.name, c.section, c.credits));
    }
}

void drop_course(map<int, map<int, list<course *> *> > &DB, int semester, int id, course c) {
    for (auto iter = DB[id][semester]->begin(); iter != DB[id][semester]->end();) {
        if ((*iter)->name == c.name) {
            delete *iter;
            iter = DB[id][semester]->erase(iter);
            return;
        } else {
            iter++;
        }
    }
}

void print_student_semester_courses(map<int, map<int, list<course *> *>> &DB, int semester, int id) {
    cout << "student id = " << id << endl;
    cout << "semester = " << semester << endl;
    cout << *DB[id][semester] << endl;
}

void print_student_all_courses(map<int, map<int, list<course *> *>> &DB, int id) {
    cout << "student id = " << id << endl;
    cout << DB[id];
    cout << endl;
}

void print_DB(map<int, map<int, list<course *> *> > &DB) {
    cout << DB;
}

//Some additional functions for overloading operator<<
ostream &operator<<(ostream &str, const course &c) {
    str << c.name << " " << c.section << " " << c.credits;
    return str;
}

ostream &operator<<(ostream &str, const list<course *> &list) {
    for (auto i: list) {
        str << *i << "  ";
    }
    str << endl;
    return str;
}

ostream &operator<<(ostream &str, const map<int, list <course * > *> &id) {
    for (auto i: id) {
        str << "semester = " << i.first << endl;
        str << *i.second;
    }
    return str;
}

ostream &operator<<(ostream &str, const map<int, map<int, list <course * > *> > &DB) {
    for (const auto &i: DB) {
        str << "student id = " << i.first << endl;
        str << i.second;
    }
    str << endl;
    return str;
}

/*
//Your output needs to keep the identical format
//Sample Screenshot
student id = 11111
semester = 20171
CIS554 1 3  CSE674 1 3  MAT296 8 4  WRT205 5 3

student id = 11111
semester = 20171
CSE674 1 3  MAT296 8 4  WRT205 5 3

student id = 11111
semester = 20171
CSE674 1 3  MAT296 8 4  WRT205 5 3
semester = 20172
CIS554 1 3  CSE674 1 3  MAT296 8 4  WRT205 5 3

student id = 11112
semester = 20171
CIS554 1 3  CSE674 1 3   MAT296 8 4  WRT205 5 3

student id = 11112
semester = 20172
CIS554 1 3  CSE674 1 3  MAT296 8 4  WRT205 5 3

student id = 11112
semester = 20171
CIS554 1 3  CSE674 1 3  MAT296 8 4  WRT205 5 3
semester = 20172
CIS554 1 3  CSE674 1 3  MAT296 8 4  WRT205 5 3

student id = 11111
semester = 20171
CSE674 1 3  MAT296 8 4  WRT205 5 3
semester = 20172
CIS554 1 3  CSE674 1 3  MAT296 8 4  WRT205 5 3
student id = 11112
semester = 20171
CIS554 1 3  CSE674 1 3  MAT296 8 4  WRT205 5 3
semester = 20172
CIS554 1 3  CSE674 1 3  MAT296 8 4  WRT205 5 3

student id = 11112
semester = 20171
CIS554 1 3  CSE674 1 3  MAT296 8 4  WRT205 5 3
semester = 20172
CIS554 1 3  CSE674 1 3  MAT296 8 4  WRT205 5 3
*/