#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <queue>
#include <map>
using namespace std;

class node {
public:
	/*
	node * next;
	int value;
	node() { next = nullptr; }
	node(int i) { next = nullptr; value = i; }
	*/
	shared_ptr<node> next;
	int value;
	node() {}
	node(int i) { value = i; }
};

template <class T> class dnode {
public:
	T value;
	shared_ptr<dnode<T>> next;
	weak_ptr<dnode<T>> previous;

	dnode<T>() {};
	dnode<T>(T v) { value = v; }
	bool operator==(const dnode<T>& t) {
		return t.value == value;
	}
};

template <class T> class dlinked_list {
	shared_ptr<dnode<T>> first, last;
	dlinked_list() {}
	dlinked_list(const initializer_list<T>& V);
	void push_front(T t);
	void push_back(T t);
	bool operator==(const dlinked_list<T>& L) const;
	dlinked_list(const dlinked_list<T>& L); //copy constructor
	void operator=(const dlinked_list<T>& L);//L-value operator=
	// template <class T> friend ostream& operator<<(ostream& s, const dlinked_list<T>& L);
};

template <class T> dlinked_list<T>::dlinked_list(const initializer_list<T>& V) : dlinked_list() {
	first.reset();
	last.reset();

	auto i = V.begin();
	while (i != V.end()) {
		push_back(*i);
		i++;
	}
}

template <class T> dlinked_list<T>::dlinked_list(const dlinked_list<T>& L) : dlinked_list() { //copy constructor
	shared_ptr<dnode<T>> p = L.first;
	while (p) {
		push_back(p->value);
		p = p->next;
	}
}

template <class T> void dlinked_list<T>::operator=(const dlinked_list<T>& L) { //operator= left ref
	first.reset();
	last.reset();
	shared_ptr<dnode<T>> p = L.first;
	while (p) {
		push_back(p->value);
		p = p->next;
	}
}

template <class T> void dlinked_list<T>::push_front(T t) {
	shared_ptr<dnode<T>> d = make_shared<dnode<T>>(t);
	if (!first) {
		first = last = d;
	}
	else {
		d->next = first;
		first->previous = d;
		first = d;
	}
}

template <class T> void dlinked_list<T>::push_back(T t) {
	shared_ptr<dnode<T>> d = make_shared<dnode<T>>(t);
	if (!last) {
		first = last = d;
	}
	else {
		d->previous = last;
		last->next = d;
		last = d;
	}
}

template <class T> bool dlinked_list<T>::operator==(const dlinked_list<T>& L) const {
	return true;
}

class linked_list {
public:
	//node * head;
	shared_ptr<node> head;
	//linked_list() { head = nullptr; }
	linked_list() {}
	linked_list(const initializer_list<int>& V) {
		auto it1 = V.end() - 1;
		while (it1 != V.begin() - 1) {
			//node * p1 = new node(*it1);
			shared_ptr<node> p1 = make_shared<node>(*it1);
			p1->next = head;
			head = p1;
			it1--;
		}
	}
};

template <class T> class ThreeD {  //template allow us to view
//data type as argument passed to a stucture, such as a class, a funciton, etc.
public:
	T ht;
	T wid;
	T dep;
	ThreeD() { ht = wid = dep = (T)0; }
	ThreeD(T i, T j, T k) { ht = i; wid = j; dep = k; }
	T getVol() { return ht * wid * dep; }
	T getArea();
	T operator() (int i, int j, int k) { return i * ht + j * wid + k * dep; }
	ThreeD(const initializer_list<T>& list) {
		auto it = list.begin();
		ht = *it * 100;
		it++;
		wid = *it * 100;
		it++;
		dep = *it * 100;
	}
};

template <class T> T
ThreeD<T>::getArea() {
	return ht * wid;
}

template <class X>
ostream& operator<<(ostream& str, const ThreeD<X>& t) {
	str << t.ht << t.wid << t.dep;
	return str;
}

template <class T>
ostream& operator<<(ostream& str, const list<T> &list) {
	str << "(";
	for (auto i : list) { str << i << ","; }
	str << ")";
	return str;
}

template <class X>
ostream& operator<<(ostream& str, const vector<X>& v) {
	for (auto i : v) {
		str << i << " ";
	}
	return str;
}

template <class X1, class X2>
ostream& operator<<(ostream& str, const map<X1, X2>& m) {
	for (auto i : m) {
		str << i.first << " " << i.second;
	}
	return str;
}


class BigData {
public:
	bool is_Hundred;
	vector<int>* pBigVector;
	BigData() { pBigVector = new vector<int>; is_Hundred = false; }
	BigData(int i) {//destructor: will be called when an object goes out of scope; 
		//or when delte p; //where p is pointer to object of this type
		pBigVector = new vector<int>(i); if (i >= 100) is_Hundred = true; else false;
	}
	~BigData() {
		delete pBigVector;
		cout << "Leaving Destructor" << endl; 
	}

	BigData(const BigData& B) {//copy constructor
		is_Hundred = B.is_Hundred;
		pBigVector = nullptr;
		pBigVector = new vector<int>;
		*pBigVector = *(B.pBigVector);

		cout << "Leaving copy constructor!" << endl;
	}

	BigData(BigData&& B) {//move constructor
		is_Hundred = B.is_Hundred;
		pBigVector = B.pBigVector;
		B.pBigVector = nullptr;
		cout << "Leaving move constructor" << endl;
	}

	BigData& operator=(const BigData& B) { //Lvalue operator=
		is_Hundred = B.is_Hundred;
		*pBigVector = *(B.pBigVector);
		cout << "Leaving L-value operator=" << endl;
		return *this;
	}

	void operator=(BigData&& B) {//Rvalue operator=
		is_Hundred = B.is_Hundred;
		pBigVector = B.pBigVector;
		B.pBigVector = nullptr;
		cout << "Leaving R-value operator=" << endl;

	}

	BigData getThreeTimes();
	void print();
};

BigData BigData::getThreeTimes() {
	BigData temp;
	temp.is_Hundred = is_Hundred;
	*temp.pBigVector = *pBigVector;
	for (int& i : *temp.pBigVector) {
		i *= 3;
	}
	return temp;
	/*
	temp is Lvalue.  However, if you have implemented move constructor
	and perform a return by value, compiler will automtically
	changes it to
	return move(temp); (It assumes that is what you really want.
	A reason for doing that is:
	When move constructor is introduced, it was stated that other than adding function
	to class definition, you don't need to change code at any other place.

	Thus, it will call move constructor, rather than copy constructor.
	*/
}
void BigData::print() { for (int i : *pBigVector) { cout << i << " "; } }


class BigArray {
public:
	int size;
	int* pArray;
	BigArray() { size = 0; pArray = nullptr; }
	BigArray(int i) { size = i; pArray = new int[i]; }
	~BigArray();//destructor
	BigArray(const BigArray& b);//copy constructor
	void operator=(const BigArray& b);//Lvalue operator=
	BigArray(BigArray&& b); //move constructor
	void operator=(BigArray&& b); //Rvalue opeartor=
	BigArray get3times();
	void print();
};
BigArray BigArray::get3times() {
	BigArray temp;
	temp.size = size;
	for (int i = 0; i < size; i++) {
		temp.pArray[i] = 3 * pArray[i];
	}
	return temp;
}
BigArray::~BigArray() { 
	size = 0;
	delete pArray;
	cout << "Leave destructor" << endl;
}//destructor
BigArray::BigArray(const BigArray& b) { //copy constructor
	size = b.size;
	pArray = nullptr;
	pArray = new int[size];
	// *pArray = *b.pArray;
	for (int i = 0; i < size; i++) {
		pArray[i] = b.pArray[i];
	}
	cout << "Leave copy constructor" << endl;
}
void BigArray::operator=(const BigArray& b) {//Lvalue operator=
	size = b.size;
	delete[] pArray;
	pArray = new int[size];
	for (int i = 0; i < size; i++) {
		pArray[i] = b.pArray[i];
	}
	cout << "Leave Lvalue operator=" << endl;
}
BigArray::BigArray(BigArray&& b) {//move constructor
	size = b.size;
	pArray = b.pArray;
	b.pArray = nullptr;
	cout << "Leave move constructor" << endl;
}

void BigArray::operator=(BigArray&& b) { //Rvalue opeartor=
	size = b.size;
	delete[] pArray;
	pArray = b.pArray; //  move constructor and Rvalue always do like this
	b.pArray = nullptr;
	cout << "Leave Rvalue operator=" << endl;
}
void BigArray::print() {
	for (int i = 0; i < size; i++) {
		cout << pArray[i] << " ";
	}
	cout << endl;
}

// summary: LR operator always have delete the content that already existed
// move/R always do pArray = b.pArray, copy/L always do *pArray = *(b.pArray);

int max(int a, int b, bool(*F)(int a, int b)) {
	cout << "Enter Max" << endl;
	if (F(a, b) == true) return a;
	else return b;
}
bool comp1(int a, int b) { return a > b; }

template <class T> class my_ThreeD_comparator {
public:
	bool operator() (const ThreeD<T>& t1, const ThreeD<T>& t2) {
		return t1.getArea() < t2.getArea();
	}
};

template <class X1, class X2> class my_int_comparator {
public:
	bool operator() (const X1 value1, const X2) {
		return X1 > X2;
	}
};
// each object of the my_***_comparator class is a functor

bool my_pred(int i) { return (i % 3 == 2) && (i % 2 == 0); }
class my_pred1_class {
public:
	bool operator()(int i) { return (i % 3 == 2) && (i % 2 == 0); }
}my_pred1;

class my_compare_class {
public:
	bool operator() (ThreeD<int>* p1, ThreeD<int>* p2) const {
		return p1->getVol() < p2->getVol();
	}

};


int main() {
	bool(*p)(int a, int b); // function pointer
	p = comp1;
	cout << max(1, 2, p) << endl;

	// functor
	ThreeD<int> p2(1, 2, 3);
	int k = 0;
	k = p2(4, 5, 6); // because operator () is overloaded, so a functor is created
	// or use functor class

	//**********************
	//maps and multimaps
	//Two ways to sort map elements based on keys
	//first: overload operator< in the class of key
	//second: provide a class of comparator
	ThreeD<int> t1(3, 4, 5), t2(1, 7, 8), t3(2, 3, 9), t4(10, 10, 10), t5(1, 2, 1);
	map<ThreeD<int>, string> M1{ {t4, "Mary"}, {t2, "Steve"}, {t3, "Bob"} };
	M1[t1] = "Nancy";//Add {t1, "Nancy"} to M1.
	M1[t2] = "Dan"; //Overwrite {t2, "Steve"} with {t2, "Dan"}
	for (auto i : M1) { cout << i.first << " " << i.second << " "; }
	cout << endl;
	M1.insert({ t5,"Jennifer" }); //Add {t5, "Jennifer"} to M1
	M1.insert({ t1, "Ben" }); //Will be ignored because the key t1 has existed
	for (auto i : M1) { cout << i.first << " " << i.second << " "; }
	cout << endl;
	map<ThreeD<int>, string, my_ThreeD_comparator<int>> M2{ {t4, "Mary"}, {t2, "Steve"}, { t1,"Nancy" }, {t3, "Bob"} };
	for (auto i : M2) { cout << i.first << " " << i.second << " "; }
	cout << endl;

	//multimaps allow duplicates.
	multimap<ThreeD<int>, string> M3{ {t4, "Mary"}, {t2, "Steve"}, { t1,"Nancy" }, {t3, "Bob"}, {t2,"Jennifer" } };
	//M3[t5] = "Dan"; Error! 
	M3.insert({ t5, "Dan" });
	M3.insert({ t1, "Ben" });
	for (auto i : M3) { cout << i.first << " " << i.second << " "; }
	cout << endl;

	//**********************
	//sets and multisets
	//Sets behave like map, but only single-value elements, rather than pairs
	//Elements will automaticlly sort, just like map
	set<ThreeD<int>> S1{ t1,t2,t3 };
	S1.insert(t4);
	S1.insert(t2);//Will be ignored.
	for (auto i : S1) { cout << i << " "; }
	cout << endl;
	set<ThreeD<int>, my_ThreeD_comparator<int>> S2{ t1,t2,t3,t4 };
	for (auto i : S2) { cout << i << " "; }
	cout << endl;

	//multisets allow duplicates
	multiset<ThreeD<int>> S3{ t1,t2,t3, t3 };
	S3.insert(t1);
	for (auto i : S3) { cout << i << " "; }
	cout << endl;

	//**************************
	//priority_queue
	//heap -- top() returns the max or min, with default being max
	priority_queue<int> pq1;
	pq1.push(11);
	pq1.push(4);
	pq1.push(3);
	pq1.push(8);
	pq1.push(5);
	while (!pq1.empty()) {
		cout << pq1.top() << " ";
		pq1.pop();
	}
	cout << endl;

	priority_queue<int, vector<int>, greater<int>> pq2;
	pq2.push(11);
	pq2.push(4);
	pq2.push(3);
	pq2.push(8);
	pq2.push(5);
	while (!pq2.empty()) {
		cout << pq2.top() << " ";
		pq2.pop();
	}
	cout << endl;

	priority_queue<ThreeD<int>> pq3;
	pq3.push(t1);
	pq3.push(t2);
	pq3.push(t3);
	pq3.push(t4);
	while (!pq3.empty())
	{
		cout << pq3.top();
		pq3.pop();
	}
	cout << endl;

	priority_queue<ThreeD<int>, vector<ThreeD<int>>, my_ThreeD_comparator<int>> pq4;
	//If using user-defined comparator class, you need to specify either vector or deque
	//deque is a "vector" that allows push and pop at both front and back.

	pq4.push(t1);
	pq4.push(t2);
	pq4.push(t3);
	pq4.push(t4);
	while (!pq4.empty())
	{
		cout << pq4.top();
		pq4.pop();
	}

	// 3 ways of using find_if
	// 1. use function; 2. use lambda expression. 3. use functor;
	list<int> L1{ 7, 4, 3, 8, 5 };
	auto it = find_if(L1.begin(), L1.end(), my_pred);
	if (it != L1.end()) cout << *it << endl;  //Will print 8
	it = find_if(L1.begin(), L1.end(), [](int i) {return (i % 3 == 2) && (i % 2 == 0); });
	if (it != L1.end()) cout << *it << endl;  //Will print 8
	it = find_if(L1.begin(), L1.end(), my_pred1);//functor
	if (it != L1.end()) cout << *it << endl;  //Will print 8
	vector<int> V1{ 7, 4, 3, 8, 5 };
	auto it1 = find_if(V1.begin(), V1.end(), my_pred);
	if (it1 != V1.end()) cout << *it1 << endl;  //Will print 8
	
	// use functor to sort map
	ThreeD<int>* p1{ new ThreeD<int>{2,3,4} }, * p2{ new ThreeD<int>{1,2,3} };
	map<ThreeD*, int, my_compare_class> M{ {p1, 4},{p2,2} };
	for (auto i : M) { cout << *i.first << " " << i.second << " "; }

	// *********************************lambda expression************************
	/*
	A lambda (or lambda expression) consists of three parts:
	[capture clause](argument list){function body}
	Capture list allows you to specify which objects (variables) in
	the scope of calling function can be accessed in the lambda.
	Two types of access: Access (or Capture) by value or
	Access (capture) by reference.  See examples below.
	Argument list is the same as argument list of regular function.

	Lambda is primarily used for in-place function definition and/or
	invocation.  Although it can have a "name" and be re-used, it is
	primarily used as an un-named function definition.
	*/
	list<int> L1{ 7,4,3,9,5 };
	L1.sort([](int a, int b) {return a % 3 < b % 3; });
	//The lambda here does not capture any local objects.

	for (int i : L1) { cout << i << " "; };
	cout << endl;
	int j{ 10 }, s{ 100 };
	list<int> L2{ 1,2,3,4 };
	for_each(L2.begin(), L2.end(), [j, &s](int i) {s += i + j; });
	/*
	The lambda here captures two local objects j and s.
	j is captured by value and is thus read-only.  Any attempt
	to modify the value of j will lead to compilation error.
	s is capture by reference.  It permits both read and write.
	Similar to call by reference in a function, there will be a single
	object s.  Thus, any modification on s in lambda will actually
	modify the s in the scope of calling function.

	More on capture clause:
	[&] : access all variables with both read and write
	[=] : access all variables with read only
	[&, i]: i read only and all others both read and write
	[=, &i, &j] :  i and j both read and write, all others read only
	[=, i] : error
	*/
	int int_value = 1;
	for (int i = 0; i < 5; i++) {
		cout << [int_value]() {return int_value; }() << " ";
		//int_value is read-only.  Any attemp to modify it inside the lambda will cause error.
		int_value++;
	}
	//The above loop will print 1 2 3 4 5

	cout << endl;
	int_value = 1;
	auto my_lambda = [int_value]() {return int_value; };
	for (int i = 0; i < 5; i++) {
		cout << my_lambda() << " ";
		int_value++;
	}
	//The above loop will print 1 1 1 1 1

	cout << endl;
	int_value = 1;
	//auto my_lambda_ = [int_value]() mutable {int_value++;  return int_value; };
	for (int i = 0; i < 5; i++) {
		cout << [int_value]() mutable {int_value++;  return int_value; }() << " ";
		//int_value++;
		// mutable: change only one time
	}
	//The above loop will print 2 2 2 2 2

	cout << endl;
	int_value = 1;
	auto my_lambda_ = [int_value]() mutable {int_value++;  return int_value; };
	for (int i = 0; i < 5; i++) {
		cout << my_lambda_() << " ";
	}
	//The above loop will print 2 3 4 5 6

	cout << endl;
	int_value = 1;
	for (int i = 0; i < 5; i++) {
		cout << [&int_value]() {int_value++;  return int_value; }() << " ";
		int_value++;
	}
	//The above loop will print 2 4 6 8 10


	cout << endl;
	int_value = 1;
	auto my_lambda_1 = [&int_value]() {int_value++;  return int_value; };
	for (int i = 0; i < 5; i++) {
		cout << my_lambda_1() << " ";
	}
	//The above loop will print 2 3 4 5 6


	// *********************************smart pointers************************
	//Raw pointers refer to the original pointers
	//Three types of smart pointers: unique_ptr, shared_ptr, weak_ptr
	unique_ptr<int> up1 = make_unique<int>(10);
	up1.reset();// up1 becomes empty; object 10's ref count = 0 and will be deleted automatically.
	up1 = make_unique<int>(15);
	cout << *up1 << endl;
	//unique_prt<int> up2 = up1; error! because the unique object can only be pointed by
	//one unique pointer

	shared_ptr<int> sp1 = make_shared<int>(20); //object 20's reference count is 1
	shared_ptr<int> sp2 = sp1; //reference count is 2
	shared_ptr<int> sp3 = make_shared<int>(30);
	sp2 = sp3; //ref count for object 20 is 1
	sp1 = sp3; //ref count for object 20 is 0 and the object 20 will be automatically deleted.
	weak_ptr<int> wp1;
	cout << sp1.use_count() << endl;//use_count returns reference count of the object pointed by sp1
	shared_ptr<int> sp4;
	wp1 = sp3; //ref count for object 30 remains 3; weak_ptr does not contribute to ref count
			   //sp4 = wp1; error! can't assign weak_ptr to shared_ptr
	sp4 = wp1.lock();//lock() type casting weak_ptr to shared_prt
	cout << *sp1 << endl;
	//cout << *wp1 << endl; Error! weak_ptr does not support * , ->
	cout << *(wp1.lock()) << endl;
	shared_ptr<ThreeD> sp5 = make_shared<ThreeD>(3, 4, 5);
	weak_ptr<ThreeD> wp2 = sp5;
	cout << sp5->ht << endl;
	cout << wp2.lock()->ht << endl;
	sp5.reset(); //the object (3,4,5) will be deleted
	if (wp2.expired()) { cout << "Object has been deleted" << endl; }
	//Reset funcitons are available to all three types of smart pointers
	sp1.reset(new int(40));
	sp1 = make_shared<int>(40);//this is faster than the above
							   //sp1.reset(make_shared<int>(40)); will not compile

							   //weak_ptr<int> wp3 = make_weak<int>(10); make_weak does not exist
	weak_ptr<int> wp3 = make_shared<int>(99);//object 99 is created and immediately deleted because ref count is 0

	linked_list L1 = { 11,2,3,4,5 };
	cout << L1.head->value << endl;

	shared_ptr<linked_list> sp11 = make_shared<linked_list>(initializer_list<int>{ 66, 7, 8, 9, 10 });//notice the
	//new syntax for initializer_list here

	cout << sp11->head->value << endl;
	return 0;
}