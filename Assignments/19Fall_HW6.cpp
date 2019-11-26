//CSE674 HW6  Due: 11:59PM, Nov. 26 (Tuesday)
#include <iostream>
using namespace std;

class node {
public:
	node* p_parent;
	node* p_Lchild;
	node* p_Rchild;
	int value;
	bool color; //true: red, false: black
	node() { p_parent = p_Lchild = p_Rchild = nullptr; }
	node(int i) { value = i; p_parent = p_Lchild = p_Rchild = nullptr; }
};

class tree {
public:
	node* root;
	tree() { root = nullptr; }

	//For insert, the new node should be the last of nodes with the same value in the order of 
	//inorder traversal.  (The same as HW5.)
	void insert_node(int i);
	void insert_R_rotate(node* p);//For insert_node, R-rotate at node pointed by p
	void insert_L_rotate(node* p);//for insert_node, L-rotate at node pointed by p
	//All other siutions of insert_node should be directly implemented inside add_node


	//For delete, the deleted node shoud be the first of nodes with the same value in the order of
	//inorder traversal. (The same as HW5).
	//For replacement, always recursively replace it with predecessor, unless there is no predecessor. (In this
	//case, replace it with sucessor.)


	void delete_node(int i);
	void delete_1(node* p); //case 1 of delete_node; p points to the parent of double black node
	void delete_1_R_rotate(node* p);//R_totate used in case 1 of delete_node; p points to the parent of double black node
	void delete_1_L_rotate(node* p);//L_totate used in case 1 of delete_node; p points to the parent of double black node
	void delete_2A(node* p); //case 2A of delete_node; p points to the parent of double black node
	void delete_2B(node* p);//case 2B of delete_node; p points to the parent of double black node
	void delete_3(node* p);//case 3 of delete_node; p points to the parent of double black node
	//All other cases of delete_node should be directly implemented inside the delete_node.

	//For the following, during traveral, print (value, color) of each node.
	void InorderPrint(node* p);
	void PostorderPrint(node* p);
	void PreorderPrint(node* p);
};

void tree::InorderPrint(node* p) {
	if (!p) { return; }
	InorderPrint(p->p_Lchild);
	cout << p->value << "-";
	if (p->color) { cout << "red "; }
	else { cout << "black "; }
	InorderPrint(p->p_Rchild);
}

void tree::PostorderPrint(node* p) {
	if (!p) { return; }
	InorderPrint(p->p_Lchild);
	InorderPrint(p->p_Rchild);
	cout << p->value << "-";
	if (p->color) { cout << "red "; }
	else { cout << "black "; }
}

void tree::PreorderPrint(node* p) {
	if (!p) { return; }
	cout << p->value << "-";
	if (p->color) { cout << "red "; }
	else { cout << "black "; }
	InorderPrint(p->p_Lchild);
	InorderPrint(p->p_Rchild);
}

void tree::insert_L_rotate(node* p) {
	if (!p) { return; }
	if (p == root) {
		node* p_right = p->p_Rchild;
		p->p_Rchild = p_right->p_Lchild;
		p_right->p_Lchild = p;

		p->p_parent = p_right;
		root = p_right;
		p_right->p_parent = nullptr;
	}
	else {
		node* p_right = p->p_Rchild;
		node* p_parent = p->p_parent;
		bool is_left = false;
		if (p_parent->p_Lchild == p) { is_left = true; }
		p->p_Rchild = p_right->p_Lchild;
		p_right->p_Lchild = p;

		p->p_parent = p_right;
		p_right->p_parent = p_parent;
		if (is_left) { p_parent->p_Lchild = p_right; }
		else { p_parent->p_Rchild = p_right; }
	}
}

void tree::insert_R_rotate(node* p) {
	if (!p) { return; }
	if (p == root) {
		node* p_left = p->p_Lchild;
		p->p_Lchild = p_left->p_Rchild;
		p_left->p_Rchild = p;

		p->p_parent = p_left;
		root = p_left;
		p_left->p_parent = nullptr;
	}
	else {
		node* p_left = p->p_Lchild;
		node* p_parent = p->p_parent;
		bool is_left = false;
		if (p_parent->p_Lchild == p) { is_left = true; }
		p->p_Lchild = p_left->p_Rchild;
		p_left->p_Rchild = p;

		p->p_parent = p_left;
		p_left->p_parent = nullptr;
		if (is_left) { p_parent->p_Lchild = p_left; }
		else { p_parent->p_Rchild = p_left; }
	}
}

void tree::insert_node(int val) {
	// case 1: 
	if (!root) {
		root = new node(val);
		root->color = false; // root color is always black
	}
	else { // search from the root to find the right place
		node* current = root;
		node* temp = nullptr;
		node* new_node = new node(val);
		new_node->color = true; // red

		while (current) {
			temp = current;
			if (current->value >= val) {
				current = current->p_Lchild;
			}
			else {
				current = current->p_Rchild;
			}
		}

		if (temp->value < val) {
			temp->p_Rchild = new_node;
			new_node->p_parent = temp;
		}
		else {
			temp->p_Lchild = new_node;
			new_node->p_parent = temp;
		}

		while (new_node && temp) {
			if (temp->color) { // parent node is red then rotate
				node* g_parent = temp->p_parent;
				node* parent = temp;
				node* uncle = nullptr;
				bool is_left = false;
				bool uncle_isNULL = false;
				if (!g_parent) { return; }
				if (g_parent->p_Lchild == temp) { is_left = true; }
				uncle = is_left ? g_parent->p_Rchild : g_parent->p_Lchild;

				if (!uncle) {
					uncle = new node(-1);
					uncle->p_parent = nullptr;
					uncle->color = false;
				}
				if (!uncle->color) { // if parent is red and uncle color is black
					// 4 cases
					// RR
					if (g_parent->p_Rchild == parent && parent->p_Rchild == new_node) {
						// cout << "RR pattern" << endl;
						insert_L_rotate(g_parent);
						g_parent->color = g_parent->color ? false : true;
						parent->color = parent->color ? false : true;
						root->color = false;
						break;
					} // RL
					else if (g_parent->p_Rchild == parent && parent->p_Lchild == new_node) {
						// cout << "RL pattern" << endl;
						insert_R_rotate(parent);
						insert_L_rotate(g_parent);
						g_parent->color = g_parent->color ? false : true;
						new_node->color = new_node->color ? false : true;
						root->color = false;
						break;
					} // LR
					else if (g_parent->p_Lchild == parent && parent->p_Rchild == new_node) {
						// cout << "LR pattern" << endl;
						insert_L_rotate(parent);
						insert_R_rotate(g_parent);
						g_parent->color = g_parent->color ? false : true;
						parent->color = parent->color ? false : true;
						root->color = false;
						break;
					} // LL
					else if (g_parent->p_Lchild == parent && parent->p_Lchild == new_node) {
						// cout << "LL pattern" << endl;
						insert_R_rotate(g_parent);
						g_parent->color = g_parent->color ? false : true;
						parent->color = parent->color ? false : true;
						root->color = false;
						break;
					}
				}
				else { // change g_parent, parent and uncle's color
					// cout << "g_parent is " << g_parent->value << " parent is " << parent->value << " uncle is " << uncle->value << endl;
					g_parent->color = g_parent->color ? false : true;
					parent->color = parent->color ? false : true;
					uncle->color = uncle->color ? false : true;
					if (g_parent == root) { g_parent->color = false; }
					else {
						// TODO: multiple violation
						// insert_node(g_parent->value);
						new_node = g_parent;
						temp = new_node->p_parent;
					}
				}
			}
			else {
				break;
			}
		}
	}
}

void tree::delete_1_L_rotate(node* p) {
	if (!p) { return; }
	if (p == root) {
		bool color = p->color;
		node* p_right = p->p_Rchild;
		p->p_Rchild = p_right->p_Lchild;
		p_right->p_Lchild = p;

		p->p_parent = p_right;
		root = p_right;
		p_right->color = false;
		p_right->p_parent = nullptr;
		if (p_right->p_Rchild) {
			p_right->p_Rchild->color = false;
		}
	}
	else {
		bool color = p->color;
		node* p_right = p->p_Rchild;
		node* p_parent = p->p_parent;
		bool is_left = false;
		if (p_parent->p_Lchild == p) { is_left = true; }
		p->p_Rchild = p_right->p_Lchild;
		p_right->p_Lchild = p;
		p_right->color = color;
		p->color = p->color ? false : true;
		p->p_parent = p_right;
		p_right->p_parent = p_parent;
		if (is_left) { p_parent->p_Lchild = p_right; }
		else { p_parent->p_Rchild = p_right; }
		if (p_right->p_Rchild) {
			p_right->p_Rchild->color = false;
		}
	}
}

void tree::delete_1_R_rotate(node* p) {
	if (!p) { return; }
	if (p == root) {
		bool color = p->color;
		node* p_left = p->p_Lchild;
		p->p_Lchild = p_left->p_Rchild;
		p_left->p_Rchild = p;
		p_left->color = color;

		p->p_parent = p_left;
		root = p_left;
		p_left->p_parent = nullptr;
		if (p_left->p_Lchild) {
			p_left->p_Lchild->color = false;
		}
	}
	else {
		bool color = p->color;
		node* p_left = p->p_Lchild;
		node* p_parent = p->p_parent;
		bool is_left = false;
		if (p_parent->p_Lchild == p) { is_left = true; }
		p->p_Lchild = p_left->p_Rchild;
		p_left->p_Rchild = p;
		p->color = p->color ? false : true;
		p->p_parent = p_left;
		p_left->p_parent = nullptr;
		if (is_left) { p_parent->p_Lchild = p_left; }
		else { p_parent->p_Rchild = p_left; }
		p_left->color = color;
		if (p_left->p_Lchild) {
			p_left->p_Lchild->color = false;
		}
	}
}

void tree::delete_1(node* p) {
	if (!p) { return; }
	// cout << "case 1" << endl;
	bool is_left = false;
	if (!p->p_Lchild) { is_left = true; }

	node* sibling = is_left ? p->p_Rchild : p->p_Lchild;
	if (is_left) { // R pattern
		if (sibling->p_Rchild) {
			if (sibling->p_Rchild->color) { // RR pattern
				// cout << "RR pattern" << endl;
				delete_1_L_rotate(p);
			}
			else {
				// cout << "RL pattern" << endl;
				delete_1_R_rotate(sibling);
				delete_1_L_rotate(p);
			}
		}
		else {
			if (sibling->p_Lchild && sibling->p_Lchild->color) {
				// cout << "RL pattern" << endl;
				delete_1_R_rotate(sibling);
				delete_1_L_rotate(p);
			}
		}
	}
	else {
		if (sibling->p_Lchild) {
			if (sibling->p_Lchild->color) {
				// cout << "LL pattern" << endl;
				delete_1_R_rotate(p);
			}
			else {
				// cout << "LR pattern" << endl;
				delete_1_L_rotate(sibling);
				delete_1_R_rotate(p);
			}
		}
		else {
			if (sibling->p_Rchild && sibling->p_Rchild->color) {
				// cout << "LR pattern" << endl;
				delete_1_L_rotate(sibling);
				delete_1_R_rotate(p);
			}
		}
	}
}

void tree::delete_2A(node* p) {
	if (!p) { return; }
	// cout << "case 2A" << endl;
	node* parent = p->p_parent;
	bool is_left = false;
	if (!p->p_Lchild) { is_left = true; }

	if (is_left) {
		if (p->p_Rchild) {
			p->p_Rchild->color = true;
		}
	}
	else {
		if (p->p_Lchild) {
			p->p_Lchild->color = true;
		}
	}
	// then repeat the process
	node* nil_node = p;
	node* new_parent = nil_node->p_parent;
	is_left = false;
	if (!new_parent) { return; }
	if (new_parent->p_Lchild == nil_node) { is_left = true; }
	node* sibling = nullptr;
	sibling = is_left ? new_parent->p_Rchild : new_parent->p_Lchild;

	if (!sibling->color) { // sibiling is black -> case 1, 2a, 2b
		int num_of_red = 0;
		if (sibling->p_Lchild && sibling->p_Lchild->color) { num_of_red++; }
		if (sibling->p_Rchild && sibling->p_Rchild->color) { num_of_red++; }
		if (num_of_red >= 1) { // case 1
			delete_1(new_parent);
		}
		else { // case 2a, 2b
			if (!parent->color) { // case 2a
				delete_2A(new_parent);
			}
			else {// case 2b
				//cout << new_parent->value << endl;
				delete_2B(new_parent);
			}
		}
	} // sibling is red, case 3
	else { // case 3
		delete_3(new_parent);
	}
}

void tree::delete_2B(node* p) {
	if (!p) { return; }
	// cout << "case 2B" << endl;
	bool is_left = false;
	if (!p->p_Lchild) { is_left = true; }
	p->color = false;
	if (is_left) { 
		if (p->p_Rchild) {
			p->p_Rchild->color = true;
		}
	}
	else { 
		if (p->p_Lchild) {
			p->p_Lchild->color = true;
		}
	}
}

void tree::delete_3(node* p) {
	if (!p) { return; }
	// cout << "case 3" << endl;
	bool is_left = false;
	if (!p->p_Lchild) { is_left = true; }

	if (is_left) {
		if (p->p_Rchild && p->p_Rchild->color) { // sibling is red
			// cout << "R pattern" << endl;
			insert_L_rotate(p);
			p->color = p->color ? false : true;
			p->p_parent->color = p->p_parent->color ? false : true;
			
			node* sibling = p->p_Rchild;
			if (sibling && !sibling->color) {
				int num_of_red = 0;
				if (sibling->p_Lchild && sibling->p_Lchild->color) { num_of_red++; }
				if (sibling->p_Rchild && sibling->p_Rchild->color) { num_of_red++; }
				if (num_of_red >= 1) { // case 1
					delete_1(p);
				}
				else { // case 2a, 2b
					if (!p->color) { // 2a
						delete_2A(p);
					}
					else { // 2b
						delete_2B(p);
					}
				}
			}
		}
	}
	else {
		if (p->p_Lchild && p->p_Lchild->color) { // sibling is red
			// cout << "L pattern" << endl;
			insert_R_rotate(p);
			p->color = p->color ? false : true;
			p->p_parent->color = p->p_parent->color ? false : true;

			node* sibling = p->p_Lchild;
			if (sibling && !sibling->color) {
				int num_of_red = 0;
				if (sibling->p_Lchild && sibling->p_Lchild->color) { num_of_red++; }
				if (sibling->p_Rchild && sibling->p_Rchild->color) { num_of_red++; }
				if (num_of_red >= 1) { // case 1
					delete_1(p);
				}
				else { // case 2a, 2b
					if (!p->color) { // 2a
						delete_2A(p);
					}
					else { // 2b
						delete_2B(p);
					}
				}
			}
		}
	}

}
void tree::delete_node(int val) {
	if (!root) { return; }
	node* current = root;
	node* current_parent = nullptr;
	// first find the node that needs to be deleted
	while (current) {
		// temp = current;
		current_parent = current->p_parent;
		if (current->value > val) {
			current = current->p_Lchild;
		}
		else if (current->value < val) {
			current = current->p_Rchild;
		}
		else {
			break;
		}
	}

	if (!current) { // element not found
		cout << "Element " << val << " not found!" << endl;
		return;
	}
	int count = 0;
	bool pred_color = false;
	// if not a leaf node
	while (current->p_Lchild || current->p_Rchild) {
		// find the predecessor
		node* l_child = current->p_Lchild;
		node* pred = nullptr;
		node* pred_parent = nullptr;

		while (l_child) {
			pred = l_child;
			pred_parent = pred->p_parent;
			l_child = l_child->p_Rchild;
		}

		if (current->p_Lchild && !current->p_Lchild->p_Lchild && !current->p_Lchild->p_Rchild) {
			count++;
			if (current->p_Rchild && (current->p_Rchild->p_Lchild || current->p_Rchild->p_Rchild)) {
				count--;
			}
		}
		else if (current->p_Rchild && !current->p_Rchild->p_Lchild && !current->p_Rchild->p_Rchild) {
			count++;
			if (current->p_Lchild && (current->p_Lchild->p_Lchild || current->p_Lchild->p_Rchild)) {
				count--;
			}
		}

		if (pred) {
			// cout << "predesessor of " << current->value << " is " << pred->value << endl;
			current->value = pred->value;
			pred_color = pred->color;
			current = pred;
		}
		
		
	}

	// delete a leaf node
	if (!current->p_Lchild && !current->p_Rchild) {
		node* nil_node = current;
		node* parent = current->p_parent;
		bool is_left = false;
		if (parent->p_Lchild == nil_node) { is_left = true; }
		if (current == root) { // root is leaf node
			root = nullptr;
			return;
		}
		else { // delete a leaf node which is not root
			if (count == 1) { // delete a node with leaf node as child
				// cout << "count is 1" << endl;
				current->color = pred_color;
				nil_node->p_parent = nullptr;
				if (is_left) { parent->p_Lchild = nullptr; }
				else { parent->p_Rchild = nullptr; }
				return;
			}
			nil_node->p_parent = nullptr;
			if (is_left) { parent->p_Lchild = nullptr; }
			else { parent->p_Rchild = nullptr; }
			node* sibling = nullptr;
			sibling = is_left ? parent->p_Rchild : parent->p_Lchild;
			// cout << "sibling of " << nil_node->value << " is " << sibling->value << endl;
			if (!sibling) { return; }
			if (!sibling->color) { // sibiling is black -> case 1, 2a, 2b
				int num_of_red = 0;
				if (sibling->p_Lchild && sibling->p_Lchild->color) { num_of_red++; }
				if (sibling->p_Rchild && sibling->p_Rchild->color) { num_of_red++; }
				if(num_of_red >= 1) { // case 1
					if (is_left) { parent->p_Lchild = nullptr; }
					else { parent->p_Rchild = nullptr; }
					delete_1(parent);
				}
				else { // case 2a, 2b
					if (!parent->color) { // case 2a
						if (is_left) { parent->p_Lchild = nullptr; }
						else { parent->p_Rchild = nullptr; }
						delete_2A(parent);
					}
					else {// case 2b
						if (is_left) { parent->p_Lchild = nullptr; }
						else { parent->p_Rchild = nullptr; }
						delete_2B(parent);
					}
				}
			} // sibling is red, case 3
			else { // case 3
				if (is_left) { parent->p_Lchild = nullptr; }
				else { parent->p_Rchild = nullptr; }
				delete_3(parent);
			}
		}
	}
}