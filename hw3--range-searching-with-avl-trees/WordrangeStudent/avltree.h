#ifndef AVLTREE_H
#define AVLTREE_H

#include <string>
using namespace std;

class Node {
	public:
		int numChild = 0;
		int height = 1;
		string data;
		Node* left, *right, *parent;

		Node() {
			data = "";
			parent = left = right = NULL;
		}

		Node(string input) {
			data = input;
			parent = left = right = NULL;
		}

		
};

class AVLT {
	private:
		Node* root;
		bool doUpdate = false;
	public:
		AVLT();
		void insert(string&);
		void insert(Node* subtree, string&);
		Node* find(string&);
		Node* find(Node* subtree, string&);
		void rrotate(Node*);
		void lrotate(Node*);
		void rlrotate(Node*);
		void lrrotate(Node*);
		int range(string, string);
		int range(string, string, Node*);
		int height(Node* subtree);
		void update(Node* subtree);
		string printPreOrder();
		string printPreOrder(Node* subtree);
};

#endif