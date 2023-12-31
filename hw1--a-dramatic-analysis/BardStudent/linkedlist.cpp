#include "bard.h"
#include <string>
#include <iostream>
using namespace std;

LinkedList :: LinkedList() {
    head = NULL;
}

void LinkedList :: insert(string str) {
    WordNode* inList = find(str);
    if (!inList) {
        WordNode* newNode = new WordNode{str,1,head};
        head = newNode;
    }
    else {
        inList->frequency++;
    }
}

void LinkedList :: insert(WordNode* Node) {
    Node->next = head;
    head = Node;

}

WordNode* LinkedList :: find(string str) {
    return find(str, head);
}

WordNode* LinkedList :: find(string str, WordNode* curr) {
    if (curr == NULL) {
        return NULL;
    }
    if (!str.compare(curr->data)){
        return curr;
    }
    return find(str, curr->next);
}

WordNode* LinkedList :: deleteWordNode(string str) {
    if (head == NULL) {
        return NULL;
    }
    else if (!str.compare(head->data)) {
        WordNode* temp = head;
        head = head->next;
        return temp;
    }
    return deleteWordNode(str, head->next, head);
}

WordNode* LinkedList :: deleteWordNode(string str, WordNode* curr, WordNode* prev) {
    if (curr == NULL) {
        return NULL;
    }
    if (!str.compare(curr->data)){
        prev->next = curr->next;
        return curr;
    }
    return deleteWordNode(str, curr->next, curr);
}

WordNode* LinkedList :: getHead() {
  return head;
}

void LinkedList :: deleteAndFreeNode(string str) {
    WordNode* node = deleteWordNode(str);
    if (node) {
        node->next = NULL;
        delete(node);
    }
}

void LinkedList :: deleteList() {
    WordNode* curr = head;
    WordNode* toDelete = NULL;
    while (curr) {
        toDelete = curr;
        curr = curr->next;
        delete(toDelete);
    }
    head = NULL;
}

string LinkedList :: print() {
    string str = "";
    if (head != NULL) {   
        WordNode* curr = head;
        while (curr) {
            str += curr->data + " ";
            curr = curr->next;
        }
        if (str.length() != 0) {
            str = str.substr(0,str.length());
        }
    }
    return str + "\n";
}

int LinkedList :: length() {
    return length(head);
}

int LinkedList :: length(WordNode* curr) {
    if (curr == NULL) {
        return 0;
    }
    return 1 + length(curr->next);
}

void LinkedList :: sort() {
  LinkedList sorted;
  WordNode* curr = head;
  while (curr) {
    WordNode* next = curr->next;
    sort(&sorted, curr);
    curr = next;
  }
  head = sorted.head;
}

void LinkedList :: sort(LinkedList* l, WordNode* node) {
  WordNode* curr = l->head;
  if (!curr || curr->frequency < node->frequency || (curr->frequency == node->frequency && curr->data.compare(node->data) > 0)) {
    l->insert(node);
  }
  else {
    while(curr->next && (curr->next->frequency > node->frequency || (curr->next->frequency == node->frequency && curr->next->data.compare(node->data) < 0))) {
      curr = curr->next;
    }
		node->next = curr->next;
		curr->next = node; 
  }
}