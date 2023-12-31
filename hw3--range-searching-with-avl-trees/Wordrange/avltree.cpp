#include "avltree.h" 
#include <iostream>
#include <string>
using namespace std;

AVLT :: AVLT() {
	root = NULL;
}

void AVLT :: insert(string& str) {
	if (!root) {
		root = new Node(str);
	}
	else {
		insert(root, str);
	}
}

void AVLT :: insert(Node* subtree, string& str) {
	if (str == subtree->data) {return;}
	if (str < subtree->data) {
		if (!subtree->left) {
			subtree->left = new Node(str);
			subtree->left->parent = subtree;
			update(subtree);
		}
		else {
			insert(subtree->left, str);
		}
	} 
	else {
		if (!subtree->right) {
			subtree->right = new Node(str);
			subtree->right->parent = subtree;
			update(subtree);
		}
		else {
			insert(subtree->right, str);
		}
	}
}

int AVLT :: height(Node* subtree) {
	int lH = (subtree->left) ? subtree->left->height : 0;
	int rH = (subtree->right) ? subtree->right->height : 0;;
	return 1 + ((lH >= rH) ? lH : rH);
}

Node* AVLT :: find(string& str) {
	return find(root, str);
}

Node* AVLT :: find(Node* subtree, string& str) {
	if ((!subtree->left && !subtree->right) || subtree->data == str) {
		return subtree;
	}
	if (subtree->data > str && subtree->left) {
		return find(subtree->left, str);
	}
	else if (subtree->data > str && !subtree->left){
		return subtree;
	}
	else if (subtree->right) {
		return find(subtree->right, str);
	}
	return subtree;
}

int AVLT :: range(string str1, string str2) {
	if (!root){return 0;}
	Node* f1 = find(str1);
	Node* f2 = find(str2);
	Node* mid = f1;
	while (mid) {
		if (find(mid,f2->data) == f2) {
			break;
		}
		mid = mid->parent;
	}
	return range(str1, str2, mid);
}

int AVLT :: range(string str1, string str2, Node* mid) {
	if (!mid) {
		return 0;
	}
	int total = 0;
	Node* subtree = mid;
	while (subtree && subtree->data >= str1 && subtree->data <= mid->data) {
		total += (subtree->data <= str2);
		if (subtree->right) total += (subtree->data < mid->data)*(1 + subtree->right->numChild);
		subtree = subtree->left;
		while (subtree && subtree->data < str1) {
			subtree = subtree->right;
		} 
	}
	subtree = mid;
	while (subtree && subtree->data <= str2 && subtree->data >= mid->data) {
		total += (subtree->data >= str1 && subtree != mid);
		if (subtree->left) total += (subtree->data > mid->data)*(1 + subtree->left->numChild);
		subtree = subtree->right;
		while (subtree && subtree->data > str2) {
			subtree = subtree->left;
		} 
	}
	return total;
}

string AVLT :: printPreOrder() {
	return printPreOrder(root);
}

string AVLT :: printPreOrder(Node* subtree) {
	if(subtree == NULL) // base case
			return ""; // return empty string
	string leftpart = printPreOrder(subtree->left);
	string rightpart = printPreOrder(subtree->right);
	string output = subtree->data;
	if(leftpart.length() != 0) // left part is empty
			output = output + " " + leftpart; // append left part
	if(rightpart.length() != 0) // right part in empty
			output = output + " " + rightpart; // append right part
	return output;
}

void AVLT :: rrotate(Node* subtree) {
	Node* temp = subtree->parent;
	subtree->parent = subtree->left;
	subtree->left = subtree->parent->right;
	if (subtree->left) subtree->left->parent = subtree;
	subtree->parent->right = subtree;
	subtree->parent->parent = temp;
	if (subtree != root) {
		if (subtree->parent->parent->left == subtree) subtree->parent->parent->left = subtree->parent;
		else subtree->parent->parent->right = subtree->parent;
	}
	else {
		root = subtree->parent;
	}
	subtree->numChild = 0;
	if (subtree->left) subtree->numChild += 1 + subtree->left->numChild;
	if (subtree->right) subtree->numChild += 1 + subtree->right->numChild;
	subtree->parent->numChild = 0;
	if (subtree->parent->left) subtree->parent->numChild += 0 + subtree->parent->left->numChild;
	if (subtree->parent->right) subtree->parent->numChild += 0 + subtree->parent->right->numChild;
	update(subtree);
}

void AVLT :: lrotate(Node* subtree) {
	Node* temp = subtree->parent;
	subtree->parent = subtree->right;
	subtree->right = subtree->parent->left;
	if (subtree->right) subtree->right->parent = subtree;
	subtree->parent->left = subtree;
	subtree->parent->parent = temp;
	if (subtree != root) {
		if (subtree->parent->parent->left == subtree) subtree->parent->parent->left = subtree->parent;
		else subtree->parent->parent->right = subtree->parent;
	}
	else {
		root = subtree->parent;
	}
	subtree->numChild = 0;
	if (subtree->left) subtree->numChild += 1 + subtree->left->numChild;
	if (subtree->right) subtree->numChild += 1 + subtree->right->numChild;
	subtree->parent->numChild = 0;
	if (subtree->parent->left) subtree->parent->numChild += 0 + subtree->parent->left->numChild;
	if (subtree->parent->right) subtree->parent->numChild += 0 + subtree->parent->right->numChild;
	update(subtree);
}

void AVLT :: update(Node* subtree) { 
	doUpdate = true;
	while (subtree) {
		subtree->numChild = 0;
		if (subtree->left) subtree->numChild += 1 + subtree->left->numChild;
		if (subtree->right) subtree->numChild += 1 + subtree->right->numChild;
		subtree->height = height(subtree);
		int balanceFactor = 0; 
		if (subtree->right && subtree->left) balanceFactor = subtree->right->height - subtree->left->height;
		else if (subtree->right) balanceFactor = subtree->right->height;
		else if (subtree->left) balanceFactor = -subtree->left->height;
		if (balanceFactor > 1) {
			if ((subtree->right->right && subtree->right->left && subtree->right->right->height > subtree->right->left->height) || (subtree->right->right && !subtree->right->left)) {
				lrotate(subtree);
			}
			else if ((subtree->right->right && subtree->right->left && subtree->right->right->height < subtree->right->left->height) || (!subtree->right->right && subtree->right->left)) {
				rrotate(subtree->right);
			}
			else {
				lrotate(subtree->parent);
			}
		}
		else if (balanceFactor < -1) {
			if ((subtree->left->left && subtree->left->right && subtree->left->left->height > subtree->left->right->height) || (subtree->left->left && !subtree->left->right)) {
				rrotate(subtree);
			}
			else if ((subtree->left->left && subtree->left->right && subtree->left->left->height < subtree->left->right->height) || (!subtree->left->left && subtree->left->right)) {
				lrotate(subtree->left);
			}
			else {
				rrotate(subtree->parent);
			}
		}
		
		if (doUpdate) {
			subtree = subtree->parent; 
		}
		else {break;}
	}
	doUpdate = false;
}