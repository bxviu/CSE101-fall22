#ifndef BARD_H
#define BARD_H

#include <string>

using namespace std;

struct WordNode {
	string data;
	int frequency;
	WordNode *next;
};

class LinkedList {
	private:
		WordNode *head;
	public:
		LinkedList();
		void insert(string);
    void insert(WordNode*);
		WordNode* find(string);
		WordNode* find(string, WordNode*);
		WordNode* deleteWordNode(string);
		WordNode* deleteWordNode(string, WordNode*, WordNode*);
		WordNode* getHead();
		void deleteAndFreeNode(string);
		void deleteList();
    void sort();
    void sort(LinkedList*, WordNode*);
		string print();
		int length();
		int length(WordNode*);
};

#endif