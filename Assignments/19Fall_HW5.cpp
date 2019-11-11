//HW5  AVL Tree
//Due: Sunday (Nov. 10) at 11:59PM
//55 points
//This homework requires more efforts. You should get started as soon as possible.

#include <iostream> //to use cout
#include <algorithm> //to use max function such as  i = max(a, b);

using namespace std;

//You need to use the following node class for each node of the AVL tree
class node {
public:
	int value;
	int height;//this is tree height. Leaf node is 1; empty node (i.e., NIL) is 0
	node* parent;
	node* l_child;
	node* r_child;
	node() {}
	node(int i) { value = i; height = 1; parent = l_child = r_child = nullptr; }

};

class avl_tree {
public:
	node* root;
	avl_tree() {
		root = nullptr;
	}

	//************************************************************************************
	//Implement the following member functions
	void add_node(int i);
	//if case of a tie, add i to the last of existing nodes with value i in the in-order sequence

	void delete_node(int i);
	//Delete the node with value i.  in case of multiple nodes with value i, 
	// delete the first node with value i in the in-order traveral sequence


	void in_order_traversal(node* p); //such as 2 5 9 11 11 14 15 15 ...

	pair<node*, int> height_update(node* p);
	/*
	This function will be invoked by add_node and delete_node.
	p points to the first node that we need to check for possible height update.  We then need to check possible height update toward root.
	All nodes whose heights need to be updated will be performed in this function.
	The function returns a pair.  If no imbalance is detected, the first of the pair will be nullptr; 
	otherwise it will be the address of the action node.
	The second of the pair will be 0 if no imbalance is detected; 
	otherwise its value is 1,2,3,4 for RR RL, LL, and LR pattern, respectively.
	*/

	void L_Rotate(node* p);
	//p points to the node at which the rotation will be performed.

	void R_Rotate(node* p);
	//p points to the node at which the rotation will be performed.
};

void avl_tree::add_node(int i) {
	if (!root) {
		root = new node(i);
		root->height = 1;
		return;
	}

	node* current = root;
	node* temp = nullptr;
	node* new_node = new node(i);

	while (current) {
		temp = current;
		if (current->value >= i) {
			current = current->l_child;
		}
		else {
			current = current->r_child;
		}
	}

	if (temp->value < i) { 
		temp->r_child = new_node; 
		new_node->parent = temp;
	}
	else {
		temp->l_child = new_node;
		new_node->parent = temp;
	}

	pair<node*, int> height = height_update(new_node);
	if (height.first == nullptr) {
		return; 
	}
	else if (height.second == 1) {
		L_Rotate(height.first);
	}
	else if (height.second == 2) {
		R_Rotate(height.first->r_child);
		L_Rotate(height.first);
	}
	else if (height.second == 3) {
		R_Rotate(height.first);
	}
	else if (height.second == 4) {
		L_Rotate(height.first->l_child);
		R_Rotate(height.first);
	}
}

void avl_tree::delete_node(int i) {
	if (!root) { return; }
	node* current = root;
	node* current_parent = nullptr;
	// first find the node that needs to be deleted
	while (current) {
		// temp = current;
		current_parent = current->parent;
		if (current->value > i) {
			current = current->l_child;
		}
		else if (current->value < i){
			current = current->r_child;
		}
		else {
			break;
		}
	}
	// element not found
	if (!current) { 
		cout << "the node with value " << i << " cannot be found" << endl;
		return; 
	}

	// case 1: i is a leaf node
	if (current->height == 1) {
		if (current == root) {
			delete root;
			root = nullptr;
			return;
		}
		else {
			if (current_parent->l_child == current) {
				current_parent->l_child = nullptr;
			}
			else {
				current_parent->r_child = nullptr;
			}
			bool no_violation = false;
			// then check for other violation
			while (!no_violation) {
				pair<node*, int> height = height_update(current);
				// current->parent = nullptr;
				if (height.first == nullptr) {
					no_violation = true;
				}
				else if (height.second == 1) {
					L_Rotate(height.first);
				}
				else if (height.second == 2) {
					R_Rotate(height.first->r_child);
					L_Rotate(height.first);
				}
				else if (height.second == 3) {
					R_Rotate(height.first);
				}
				else if (height.second == 4) {
					L_Rotate(height.first->l_child);
					R_Rotate(height.first);
				}
				current = current->parent;
				cout << endl;
			}
		}
		
		
	} // case 2: delete a parent of leaf node(s)
	else if (current->height == 2) {
		node* lchild = current->l_child;
		node* rchild = current->r_child;
		pair<node*, int> height;
		node* examine = nullptr;
		bool no_violation = false;
		if (lchild) {
			current->value = lchild->value;
			current->l_child = nullptr;
			examine = lchild;
			// lchild->parent = nullptr;
			// delete lchild;
		}
		else if (rchild) {
			current->value = rchild->value;
			current->r_child = nullptr;
			examine = rchild;
			//rchild->parent = nullptr;
			// delete rchild;
		}
		// then check for other violation
		while (!no_violation) {
			height = height_update(examine);
			if (height.first == nullptr) {
				no_violation = true;
			}
			else if (height.second == 1) {
				L_Rotate(height.first);
			}
			else if (height.second == 2) {
				R_Rotate(height.first->r_child);
				L_Rotate(height.first);
			}
			else if (height.second == 3) {
				R_Rotate(height.first);
			}
			else if (height.second == 4) {
				L_Rotate(height.first->l_child);
				R_Rotate(height.first);
			}
		}
	} // case 3: other, which requires predecessor and successor
	else {
		node* lchild = current->l_child;
		node* rchild = current->r_child;
		node* examine = nullptr;
		bool no_violation = false;
		pair<node*, int> height;
		int diff = lchild->height - rchild->height;

		// find the predecessor
		node* pred = nullptr;
		node* pred_parent = nullptr;
		while (lchild) {
			pred = lchild;
			pred_parent = pred->parent;
			lchild = lchild->r_child;
		}
		node* succ = nullptr;
		node* succ_parent = nullptr;
		while (rchild) {
			succ = rchild;
			succ_parent = succ->parent;
			rchild = rchild->l_child;
		}

		
		if (diff >= 0 && pred) { // replace current with predecessor
			//cout << "Replacing " << current->value << " with " << pred->value << " as predecessor" << endl;
			current->value = pred->value;
			if (pred_parent) { pred_parent->r_child = nullptr; }
			examine = current;
			// height = height_update(current);
			pred->parent = nullptr;
			//delete pred;
		}
		else if (diff < 0 && succ) { // replace current with successor
			//cout << "Replacing " << current->value << " with " << succ->value << " as successor" << endl;
			current->value = succ->value;
			if (succ_parent) { succ_parent->l_child = nullptr; }
			examine = current;
			// height = height_update(current);
			succ->parent = nullptr;
			//delete succ;
		}

		while (!no_violation) {
			height = height_update(examine);
			// then update height
			if (height.first == nullptr) {
				no_violation = true;
			}
			else if (height.second == 1) {
				L_Rotate(height.first);
			}
			else if (height.second == 2) {
				R_Rotate(height.first->r_child);
				L_Rotate(height.first);
			}
			else if (height.second == 3) {
				R_Rotate(height.first);
			}
			else if (height.second == 4) {
				L_Rotate(height.first->l_child);
				R_Rotate(height.first);
			}
		}
	}
}

pair<node*, int> avl_tree::height_update(node* p) {
	if (!p || !p->parent) { return { nullptr, -1 }; }
	node* p_parent = p->parent;
	// update heights from the node just inserted
	while (p_parent) {
		int left_height = p_parent->l_child ? p_parent->l_child->height : 0;
		int right_height = p_parent->r_child ? p_parent->r_child->height : 0;
		p_parent->height = max(left_height, right_height) + 1;
		p_parent = p_parent->parent;
	}

	// then check violation
	node* current = p->parent;
	while (current) {
		int left_height = current->l_child ? current->l_child->height : 0;
		int right_height = current->r_child ? current->r_child->height : 0;
		int diff = left_height - right_height;

		int left_left_height = 0, left_right_height = 0;
		int right_left_height = 0, right_right_height = 0;

		if (current->l_child) {
			left_left_height = current->l_child->l_child ? current->l_child->l_child->height : 0;
			left_right_height = current->l_child->r_child ? current->l_child->r_child->height : 0;
		}

		if (current->r_child) {
			right_left_height = current->r_child->l_child ? current->r_child->l_child->height : 0;
			right_right_height = current->r_child->r_child ? current->r_child->r_child->height : 0;
		}

		// its value is 1,2,3,4 for RR RL, LL, and LR pattern, respectively.
		// RR pattern
		if (diff < -1 && right_right_height > right_left_height) {
			//cout << "RR pattern" << endl;
			return { current, 1 };
		} // RL pattern
		else if (diff < -1 && right_right_height <= right_left_height) {
			//cout << "RL pattern" << endl;
			return { current, 2 };
		}
		else if (diff > 1 && left_left_height > left_right_height) {
			//cout << "LL pattern" << endl;
			return { current, 3 };
		}
		else if (diff > 1 && left_left_height <= left_right_height) {
			//cout << "LR pattern" << endl;
			return { current, 4 };
		}
		current = current->parent;
	}
	return { nullptr, -1 };
}

void avl_tree::in_order_traversal(node* p) {
	if (!p) { return; }
	in_order_traversal(p->l_child);
	cout << p->value << "-" << p->height << " ";
	in_order_traversal(p->r_child);
}


void avl_tree::L_Rotate(node* p) {
	if (!p) { return; }
	//cout << "L rotating at node " << p->value << endl;
	if (p == root) {
		node* p_right = p->r_child;
		p->r_child = p_right->l_child;
		p_right->l_child = p;

		p->parent = p_right;
		root = p_right;
		p_right->parent = nullptr;
	}
	else {
		node* p_right = p->r_child;
		node* p_parent = p->parent;
		bool is_left = false;
		if (p_parent->l_child == p) { is_left = true; }
		p->r_child = p_right->l_child;
		p_right->l_child = p;

		p->parent = p_right;
		p_right->parent = p_parent;
		if (is_left) { p_parent->l_child = p_right; }
		else { p_parent->r_child = p_right; }

		// update height
		node* current = p;
		while (current) {
			int left_height = current->l_child ? current->l_child->height : 0;
			int right_height = current->r_child ? current->r_child->height : 0;
			current->height = max(left_height, right_height) + 1;
			current = current->parent;
		}
	}
}

void avl_tree::R_Rotate(node* p) {
	if (!p) { return; }
	//cout << "R rotating at node " << p->value << endl;
	if (p == root) {
		node* p_left = p->l_child;
		p->l_child = p_left->r_child;
		p_left->r_child = p;

		p->parent = p_left;
		root = p_left;
		p_left->parent = nullptr;

		node* current = p;
		while (current) {
			int left_height = current->l_child ? current->l_child->height : 0;
			int right_height = current->r_child ? current->r_child->height : 0;
			current->height = max(left_height, right_height) + 1;
			current = current->parent;
		}
	}
	else {
		node* p_left = p->l_child;
		node* p_parent = p->parent;
		bool is_left = false;
		if (p_parent->l_child == p) { is_left = true; }
		p->l_child = p_left->r_child;
		p_left->r_child = p;

		p->parent = p_left;
		p_left->parent = p_parent;
		if (is_left) { p_parent->l_child = p_left; }
		else { p_parent->r_child = p_left; }
	
		node* current = p;
		while (current) {
			int left_height = current->l_child ? current->l_child->height : 0;
			int right_height = current->r_child ? current->r_child->height : 0;
			current->height = max(left_height, right_height) + 1;
			current = current->parent;
		}
	}
}

int main() {
	//Different test cases will be used during grading.
	avl_tree t1;
	t1.add_node(45);
	t1.in_order_traversal(t1.root);
	t1.delete_node(45);
	t1.in_order_traversal(t1.root);
	t1.add_node(50);
	t1.add_node(46);
	t1.add_node(30);
	t1.add_node(34);
	t1.in_order_traversal(t1.root);
	
	return 0;
}