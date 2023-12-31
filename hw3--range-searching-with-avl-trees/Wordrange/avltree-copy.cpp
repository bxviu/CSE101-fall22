#include "avltree.h" 
#include <iostream>
#include <string>
using namespace std;

AVLT :: AVLT() {
	root = NULL;
}

void AVLT :: insert(string str) {
	if (!root) {
		root = new Node(str);
		// cout << root->data << " " << root->height << " " << root->numChild << endl;
	}
	else {
		insert(root, str);
	}
}

void AVLT :: insert(Node* subtree, string str) {
	if (str == subtree->data) {return;}
	if (str < subtree->data) {
		if (!subtree->left) {
			subtree->left = new Node(str);
			subtree->left->parent = subtree;
			// subtree->numChild++;
			update(subtree);
			
			// Node* update = subtree;
			// while (update) {
			// 	// cout << update->data << " " << update->height << " " << update->numChild << " | ";
			// 	update->numChild++;
			// 	update->height = height(update);
			// 	// cout << update->data << " " << update->height << " " << update->numChild << endl;
			// 	update = update->parent;
			// }
			// cout << "---" << endl;
			// cout << "parent of left child: " << subtree->left->data << " is " << subtree->left->parent->data << endl;
		}
		else {
			insert(subtree->left, str);
		}
	} 
	else {
		if (!subtree->right) {
			subtree->right = new Node(str);
			subtree->right->parent = subtree;
			// subtree->numChild++;
			update(subtree);
			// Node* update = subtree;
			// while (update) {
			// 	// cout << update->data << " " << update->height << " " << update->numChild << " | ";
			// 	update->numChild++;
			// 	update->height = height(update);
			// 	// cout << update->data << " " << update->height << " " << update->numChild << endl;
			// 	update = update->parent;
			// }
			// cout << "---" << endl;
			// cout << "parent of right child: " << subtree->right->data << " is " << subtree->right->parent->data << endl;
		}
		else {
			insert(subtree->right, str);
		}
	}
}

int AVLT :: height(Node* subtree) {
	int lH = 0;
	int rH = 0;
	if (subtree->left) lH = subtree->left->height;
	if (subtree->right) rH = subtree->right->height;
	return 1 + ((lH >= rH) ? lH : rH);
	// if (!subtree) return 0;
	// int lH = height(subtree->left);
	// int rH = height(subtree->right);
	// if (printDebug) cout << "data " << subtree->data << " leftH " << lH << " rightH " << rH << endl;
	// return 1 + ((lH >= rH) ? lH : rH);
}

Node* AVLT :: find(string str) {
	return find(root, str);//, abs(str.compare(root->data)));
}

Node* AVLT :: find(Node* subtree, string str) {
	if ((!subtree->left && !subtree->right) || subtree->data == str) {
		if (printDebug2) cout << "looking for " << str << " found " << subtree->data << endl;
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
	Node* f1 = find(str1);
	Node* f2 = find(str2);
	if (printDebug2) {printNode(f1);
	printNode(f2);}
	int diff = abs(f1->data.compare(f2->data));
	int d;
	Node* mid = f1;
	// while (mid) {
	// 	if (printDebug2) printNode(mid);
	// 	string s = find(mid, f2->data)->data;
	// 	d = abs(s.compare(f2->data));
	// 	if (printDebug2) cout << "f1 " << f1->data << " found " << s << " diff " << diff << " d " << d << endl;
	// 	if (d == 0) break;
	// 	if (d <= diff) {
	// 		diff = d;
	// 	}
	// 	else break;
	// 	if (mid->parent) mid = mid->parent;
	// 	else break;	
	// }
	while (mid) {
		if (printDebug2) printNode(mid);
		if (find(mid,f2->data) == f2) {
			break;
		}
		mid = mid->parent;
	}
	if (printDebug2) cout << "left " << f1->data << " right " << f2->data << endl;
	if (printDebug2) {printNode(mid);cout << "found " << mid->data << endl;}
	// if (printDebug2) return range(root, str1, str2, mid, f1, f2);	//return range(root, str1, str2);
	/*else*/ return range(mid, str1, str2, mid, f1, f2);	
	// if (mid->parent) {
	// 	return range(mid->parent, str1, str2, mid, f1, f2);	
	// }
	// return range(root, str1, str2, mid, f1, f2);	
}

int AVLT :: range(Node* subtree, string str1, string str2) {
	if (!subtree) {
		return 0;
	}
	printNode(subtree);
	if (printDebug2) cout << "range " << subtree->data << " " << str1 << " " << str2 << endl;
	if (str1 <= subtree->data && str2 >= subtree->data) {
		if (printDebug2) cout << "3 " << ((subtree->data >= str1 && subtree->data <= str2) ? "added" : "no") << endl;
		return ((subtree->data >= str1 && subtree->data <= str2) ? 1 : 0) + range(subtree->right, str1, str2) + range(subtree->left, str1, str2);
	}
	if (str1 >= subtree->data) {
		if (printDebug2) cout << "1 " << ((subtree->data >= str1 && subtree->data <= str2) ? "added" : "no") << endl;
		return ((subtree->data >= str1) ? 1 : 0) + range(subtree->right, str1, str2);
	}
	// if (str2 <= subtree->data) {
		if (printDebug2) cout << "2 " << ((subtree->data >= str1 && subtree->data <= str2) ? "added" : "no") << endl;
		return ((subtree->data <= str2) ? 1 : 0) + range(subtree->left, str1, str2);
	// }
}

int AVLT :: range(Node* subtree, string str1, string str2, Node* mid, Node* min, Node* max) {
	if (!subtree) {
		return 0;
	}
	if (printDebug2)  printNode(subtree);
	if (subtree->data < str1) {
		return range(subtree->right, str1, str2, mid, min, max);
	}
	if (subtree->data > str2) {
		return range(subtree->left, str1, str2, mid, min, max);
	}
	int total = 0;
	if (subtree->data <= str2 && subtree->data >= str1) total++;
	if (printDebug2)  cout << "data " << subtree->data << " total: " << total << endl;
	if (subtree->data < mid->data) {
		if (subtree->right) {total += 1 + subtree->right->numChild; if (printDebug2) cout << "lr " << "data " << subtree->data << " total: " << total << endl;}
		//if (subtree->left && mid->data > min->data) {total += 1 + subtree->left->numChild; cout << "llm " << endl;} 
		/*else*/ if (subtree->left) {total += range(subtree->left, str1, str2, mid, min, max);if (printDebug2) cout << "ll " << "data " << subtree->data << " total: " << total << endl;}
		// if (printDebug2)  cout << "data " << subtree->data << " total: " << total << endl;
		return total;
	}
	if (subtree->data > mid->data) {
		if (subtree->left) {total += 1 + subtree->left->numChild;if (printDebug2) cout << "gl " << "data " << subtree->data << " total: " << total << endl;}
		// if (subtree->right && mid->data < max->data) {total += 1 + subtree->right->numChild;cout << "grm " << endl;}
		/*else*/ if (subtree->right) {total += range(subtree->right, str1, str2, mid, min, max);if (printDebug2) cout << "gr " << "data " << subtree->data << " total: " << total << endl;}
		// if (printDebug2)  cout << "data " << subtree->data << " total: " << total << endl;
		return total;
	}
	if (mid->data == subtree->data) {
		if (subtree->data > str1) {total += range(subtree->left, str1, str2, mid, min, max);if (printDebug2) cout << "el " << "data " << subtree->data << " total: " << total << endl;}
		if (subtree->data < str2) {total += range(subtree->right, str1, str2, mid, min, max);if (printDebug2) cout << "er " << "data " << subtree->data << " total: " << total << endl;}
	}
	// if (printDebug2)  cout << "data " << subtree->data << " total: " << total << endl;
	return total;
}

/*
int AVLT :: range(Node* subtree, string str1, string str2, Node* mid) {
	if (!subtree) {
		return 0;
	}
	// printNode(subtree);
	if (subtree->data < str1) {
		return range(subtree->right, str1, str2, mid);
	}
	if (subtree->data > str2) {
		return range(subtree->left, str1, str2, mid);
	}
	int total = 0;
	if (subtree->data >= str1 && mid->data < root->data) {
		if (subtree->data <= str2) total++;
		// if (subtree->parent && subtree->parent->data <= str2 && subtree->parent->data >= str1) {
		// 	if (subtree->right && subtree->data < str2) {total += 1 + subtree->right->numChild; cout << "1 " << endl;}
		// 	if (subtree->left) {total += subtree->left->numChild;cout << "2 " << endl;}
		// }
		//else if (subtree->parent && subtree->parent->data < str1) {
		if (subtree->data < mid->data) {
			if (subtree->right && subtree->data < str2) {total += 1 + subtree->right->numChild;}// cout << "1-2 " << endl;}
			if (subtree->left) {total += range(subtree->left, str1, str2, mid);}//cout << "2-2 " << endl;}
		}
		else {//if (mid->data > str2) {
			if (subtree->right) {total += range(subtree->right, str1, str2, mid);}//cout << "3 " << endl;}
			if (subtree->left) {total += range(subtree->left, str1, str2, mid);}//cout << "4 " << endl;}
		}
		// cout << "data1 " << subtree->data << " total: " << total << endl;
		return total;
	}
	if (subtree->data <= str2 && mid->data > root->data) {
		if (subtree->data >= str1) {total++;}// cout << "data2a " << subtree->data << " total: " << total << endl;}
		
		// if (subtree->parent && subtree->parent->data < str2 && subtree->parent->data > str1) {
		if (subtree->data > mid->data) {
			if (subtree->left && subtree->data > str1) {total += 1 + subtree->left->numChild;}//cout << "5 " << endl;}
			if (subtree->right) {total += range(subtree->right, str1, str2, mid);}//cout << "6 " << endl;}
		}
		else {//if (mid->data < str1) {
			if (subtree->right) {total += range(subtree->right, str1, str2, mid);}//cout << "7 " << endl;}
			if (subtree->left) {total += range(subtree->left, str1, str2, mid);}//cout << "8 " << endl;}
		}
		// cout << "data2 " << subtree->data << " total: " << total << endl;
		return total;
	}
	if (subtree->data >= str1 && subtree->data <= str2 && mid->data == root->data) {
		total += 1 + range(subtree->right, str1, str2, mid) + range(subtree->left, str1, str2, mid);
	}
	// cout << "data3 " << subtree->data << " total: " << total << endl;
	return total;
}*/

/*int AVLT :: range(Node* subtree, string str1, string str2) {
	if (!subtree) {
		return 0;
	}
	int total = 0;
	Node* s = subtree;
	while (s && s->data >= str1) {
		// printNode(s);
		if (s->data >= str1 && s->data <= str2) {
			total += 1;
		} 
		if (s->right && s->parent && s->right->data < str2 && s->parent->data > str2) {
			// cout << "1" << endl;
			// total += 1 + range(s->right, str1, str2);
			Node* tmp = s;
			while (tmp && tmp->data <= str2) {
				total += 1;//range(s->left, str1, str2);
				if (tmp->right && tmp->right->left) total += tmp->right->left->numChild;
				tmp = tmp->right;
			}
		}
		else if (s->right && s->parent && s->right->data < str2 && s->parent->data <= str2) {
			// cout << "2" << endl;
			total += 1 + s->right->numChild;
		}
		// cout << "total: " << total << endl;
		s = s->left;
		// if (s) printNode(s);
	}
	if (s && s->data < str1) {
		// printNode(s);
		if (s->right && s->parent && s->right->data < str2 && s->parent->data <= str2) {
			// cout << "3" << endl;
			Node* tmp = s;
			while (tmp->right && tmp->right->data < str1) {

				tmp = tmp->right;
			}
			if (tmp->right && tmp->right->data >= str1) {
					total += 1 + tmp->right->numChild;
					// break;
			}
		}
		else if (s->right && s->parent && s->right->data < str2 && s->parent->data > str2) {
			// cout << "7" << endl;
			Node* tmp = s;
			while (tmp && tmp->data <= str2) {
				if (tmp->data >= str1) total += 1;
				if (tmp->right && tmp->right->left) total += 1 + tmp->right->left->numChild;
				tmp = tmp->right;
			}
		}
	}
	// cout << "total: " << total << endl;
	s = subtree;
	while (s && s->data <= str2) {
		// printNode(s);
		if (s->data <= str2 && s->data >= str1 && s != root) {
			total += 1;
		} 
		if (s->left && s->parent && s->left->data > str1 && s->parent->data < str1) {
			// cout << "4" << endl;
			Node* tmp = s;
			while (tmp && tmp->data >= str1) {
				total += 1;//range(s->left, str1, str2);
				if (tmp->left && tmp->left->right) total += tmp->left->right->numChild;
				tmp = tmp->left;
			}
		}
		else if (s->left && s->parent && s->left->data > str1 && s->parent->data >= str1) {
			// cout << "5" << endl;
			total += 1 + s->left->numChild;
		}
		// cout << "total: " << total << endl;
		s = s->right;
	}
	if (s && s->data > str2) {
		// printNode(s);
		if (s->left && s->parent && s->left->data > str1 && s->parent->data >= str1) {
			// cout << "6" << endl;
			Node* tmp = s;
			while (tmp->left && tmp->left->data > str2) {

				tmp = tmp->left;
			}
			if (tmp->left && tmp->left->data <= str2) {
					total += 1 + tmp->left->numChild;
					// break;
				}
		}
		else if (s->left && s->parent && s->left->data > str1 && s->parent->data < str1) {
			// cout << "8" << endl;
			Node* tmp = s;
			while (tmp && tmp->data >= str1) {
				if (tmp->data <= str2) total += 1;
				if (tmp->left && tmp->left->left) total += 1 + tmp->left->right->numChild;
				tmp = tmp->left;
			}
		}
	}
	// cout << "total: " << total << endl;
	return total;
}*/

// int AVLT :: range(Node* subtree, string str1, string str2) {
// 	if (!subtree) {
// 		return 0;
// 	}
// 	if (printDebug) cout << "range called " << subtree->data << endl;
// 	int total = 0;
// 	// if (subtree->data < str1) {
// 	// 	// return range(subtree->right, str1, str2);
// 	// 	while (subtree->data < str1 && subtree->right) {
// 	// 		subtree = subtree->right;
// 	// 		if (subtree->data >= str1 && subtree->data < root->data) {
// 	// 			total += 1;
// 	// 			if (subtree->data < str2 && subtree->right) {
// 	// 				total += 1 + subtree->right->numChild;
// 	// 			}
// 	// 			return total + range(subtree->left, str1, str2);
// 	// 		}
// 	// 		if (subtree->data >= str1 && subtree->data <= str2) {
// 	// 			return 1 + range(subtree->right, str1, str2) + range(subtree->left, str1, str2);
// 	// 		}
// 	// 	}
// 	// }
// 	// if (subtree->data > str2) {
// 	// 	while (subtree->data > str2 && subtree->left) {
// 	// 		subtree = subtree->left;
// 	// 		if (subtree->data <= str2 && subtree->data > root->data) {
// 	// 			total += 1;
// 	// 			if (subtree->data > str1 && subtree->left) {
// 	// 					total += 1 + subtree->left->numChild;
// 	// 			}
// 	// 			return total + range(subtree->right, str1, str2);
// 	// 		}
// 	// 		if (subtree->data >= str1 && subtree->data <= str2) {
// 	// 			return 1 + range(subtree->right, str1, str2) + range(subtree->left, str1, str2);
// 	// 		}
// 	// 	}
// 	// 	// return range(subtree->left, str1, str2);
// 	// }
// 	// return total;
// 	// if (subtree->data < str1) {
// 	// 	// cout << "going to right: " << subtree->data << endl;
// 	// 	return range(subtree->right, str1, str2);
// 	// }
// 	// if (subtree->data > str2) {
// 	// 	// cout << "going to left: " << subtree->data << endl;
// 	// 	return range(subtree->left, str1, str2);
// 	// }
// 	// if (subtree->data >= str1 /**&& subtree->data < root->data*/) {
// 	// 	total += 1;
// 	// 	// cout << "l ";
// 	// 	if (subtree->data < str2 /*&& root->data > str2*/ && subtree->right) {
// 	// 		// cout << "3 ";
// 	// 		total += 1 + subtree->right->numChild;
// 	// 	}
// 	// 	else if (subtree->data < str2) {
// 	// 		// cout << "1 ";
// 	// 		total += range(subtree->right, str1, str2);
// 	// 	}
// 	// 	// printNode(subtree);
// 	// 	return total + range(subtree->left, str1, str2);
// 	// }
// 	// if (subtree->data <= str2/* && subtree->data > root->data*/) {
// 	// 	total += 1;
// 	// 	// cout << "r ";
// 	// 	if (subtree->data > str1 /*&& root->data < str1*/ && subtree->left) {
// 	// 		// cout << "4 ";
// 	// 		total += 1 + subtree->left->numChild;
// 	// 	}
// 	// 	else if (subtree->data > str1) {
// 	// 		// cout << "2 ";
// 	// 		total += range(subtree->left, str1, str2);
// 	// 	}
// 	// 	// printNode(subtree);
// 	// 	return total + range(subtree->right, str1, str2);
// 	// }
// 	// if (subtree->data > str1 && subtree->data < str2) {
// 	// 	// cout << "5 ";
// 	// 	// printNode(subtree);
// 	// 	return 1 + range(subtree->right, str1, str2) + range(subtree->left, str1, str2);
// 	// }
// 	// else {
// 	// 	// printNode(subtree);
// 	// }
// 	// return total;

// 	if (printDebug) cout << "range " << subtree->data << " " << str1 << " " << str2 << endl;
// 	if (str1 <= subtree->data && str2 >= subtree->data) {
// 		if (printDebug) cout << "3 " << ((subtree->data >= str1 && subtree->data <= str2) ? "added" : "no") << endl;
// 		return ((subtree->data >= str1 && subtree->data <= str2) ? 1 : 0) + range(subtree->right, str1, str2) + range(subtree->left, str1, str2);
// 	}
// 	if (str1 >= subtree->data) {
// 		if (printDebug) cout << "1 " << ((subtree->data >= str1 && subtree->data <= str2) ? "added" : "no") << endl;
// 		return ((subtree->data >= str1) ? 1 : 0) + range(subtree->right, str1, str2);
// 	}
// 	// if (str2 <= subtree->data) {
// 		if (printDebug) cout << "2 " << ((subtree->data >= str1 && subtree->data <= str2) ? "added" : "no") << endl;
// 		return ((subtree->data <= str2) ? 1 : 0) + range(subtree->left, str1, str2);
// 	// }
// }

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

void AVLT :: printNode(Node* subtree) {
		cout << "data " << subtree->data << " height " << subtree->height << " child# " << 			subtree->numChild;
		if (subtree->parent) {cout <<" parent " << subtree->parent->data << " child# " << subtree->parent->numChild ;} 
		if (subtree->right) {cout <<" right " << subtree->right->data << " child# " << subtree->right->numChild ;}
		if (subtree->left) {cout <<" left " << subtree->left->data << " child# " << subtree->left->numChild ;} cout << endl;
}

void AVLT :: printVerbose() {
	cout << "verbose" <<endl;
	printVerbose(root);
}

void AVLT :: printVerbose(Node* subtree) {
	if(subtree == NULL) // base case
			return; // return empty string
	printVerbose(subtree->left);
	printVerbose(subtree->right);
	cout << "data " << subtree->data << " height " << subtree->height << " child# " << subtree->numChild;
	if (subtree->parent) cout << " parent " << subtree->parent->data << " "; 
	if (subtree->right) cout << " right " << subtree->right->data << " child# " << subtree->right->numChild << " parent " << subtree->right->parent->data << " ";
	if (subtree->left) cout << " left " << subtree->left->data << " child# " << subtree->left->numChild << " parent " << subtree->left->parent->data << " ";
	cout << endl; 
}

void AVLT :: rrotate(Node* subtree) {
	if (printDebug) cout <<"rrot " << subtree->data << endl;
	Node* temp = subtree->parent;
	subtree->parent = subtree->left;
	subtree->left = subtree->parent->right;
	if (subtree->left) subtree->left->parent = subtree;
	subtree->parent->right = subtree;
	subtree->parent->parent = temp;
	if (subtree != root) {
		// subtree->parent->parent = temp;
		if (subtree->parent->parent->left == subtree) subtree->parent->parent->left = subtree->parent;
		else subtree->parent->parent->right = subtree->parent;
	}
	else {
		root = subtree->parent;
		// subtree->parent->parent = temp;
	}
	subtree->numChild = 0;
	if (subtree->left) subtree->numChild += 1 + subtree->left->numChild;
	if (subtree->right) subtree->numChild += 1 + subtree->right->numChild;

	subtree->parent->numChild = 0;
	if (subtree->parent->left) subtree->parent->numChild += 0 + subtree->parent->left->numChild;
	if (subtree->parent->right) subtree->parent->numChild += 0 + subtree->parent->right->numChild;

	if (printDebug) {
		cout << "data " << subtree->data << " child " << subtree->numChild;
		if (subtree->parent) cout << " parent " << subtree->parent->data << " childe " << subtree->parent->numChild; 
		if (subtree->right) cout << " right " << subtree->right->data << " parent " << subtree->right->parent->data << " ";
		if (subtree->left) cout << " left " << subtree->left->data << " parent " << subtree->left->parent->data << " ";
		cout << endl; 
		// cout << "printu " << printPreOrder() << endl;
	}
	update(subtree);
}

void AVLT :: lrotate(Node* subtree) {
	if (printDebug) {
	cout <<"lrot " << subtree->data;
	if (subtree->parent) cout << " " << subtree->parent->data;
	cout << endl;}
	Node* temp = subtree->parent;
	subtree->parent = subtree->right;
	subtree->right = subtree->parent->left;
	if (subtree->right) subtree->right->parent = subtree;
	subtree->parent->left = subtree;
	subtree->parent->parent = temp;
	if (subtree != root) {
		// subtree->parent->parent = temp;
		if (subtree->parent->parent->left == subtree) subtree->parent->parent->left = subtree->parent;
		else subtree->parent->parent->right = subtree->parent;
	}
	else {
		root = subtree->parent;
		// subtree->parent->parent = temp;
	}
	subtree->numChild = 0;
	if (subtree->left) subtree->numChild += 1 + subtree->left->numChild;
	if (subtree->right) subtree->numChild += 1 + subtree->right->numChild;

	subtree->parent->numChild = 0;
	if (subtree->parent->left) subtree->parent->numChild += 0 + subtree->parent->left->numChild;
	if (subtree->parent->right) subtree->parent->numChild += 0 + subtree->parent->right->numChild;

	if (printDebug) {
	cout << "data " << subtree->data << " child " << subtree->numChild;
	if (subtree->parent) cout << " parent " << subtree->parent->data << " childe " << subtree->parent->numChild; 
	if (subtree->right) cout << " right " << subtree->right->data << " parent " << subtree->right->parent->data << " ";
	if (subtree->left) cout << " left " << subtree->left->data << " parent " << subtree->left->parent->data << " ";
	cout << endl;} 
	// cout << "printu " << printPreOrder() << endl;}
	update(subtree);
}

void AVLT :: update(Node* subtree) { 
	// if (!subtree) {cout << "got null, update over" << endl; return;}
	doUpdate = true;
	if (printDebug) {
	cout << "update " << subtree->data << endl;
	cout << "printe " << printPreOrder() << endl;}
	while (subtree) {
		// if (subtree->numChild > 100) break;
		if (printDebug) cout << "before update: data " << subtree->data << " height " << subtree->height << " child# " << subtree->numChild << endl;
		// subtree->numChild++;
		subtree->numChild = 0;
		if (subtree->left) subtree->numChild += 1 + subtree->left->numChild;
		if (subtree->right) subtree->numChild += 1 + subtree->right->numChild;
		subtree->height = height(subtree);
		int balanceFactor = 0; 
		if (subtree->right && subtree->left) balanceFactor = subtree->right->height - subtree->left->height;
		else if (subtree->right) balanceFactor = subtree->right->height;
		else if (subtree->left) balanceFactor = -subtree->left->height;
		// else {
		// 	balanceFactor = 0;
			// cout << "update ended" << endl;
			// cout << "printEnded " << printPreOrder() << endl;
			// break;
		// }
		if (printDebug) {cout << "data " << subtree->data << " height " << subtree->height << " child# " << subtree->numChild << " bf " << balanceFactor;
		if (subtree->parent) {cout <<" parent " << subtree->parent->data << " child# " << subtree->parent->numChild ;} 
		if (subtree->right) {cout <<" right " << subtree->right->data << " child# " << subtree->right->numChild ;}
		if (subtree->left) {cout <<" left " << subtree->left->data << " child# " << subtree->left->numChild ;} cout << endl;}
		// if (balanceFactor == 0) { 
		// 	subtree = subtree->parent; 
		// 	if (printDebug && subtree) cout << " bal 0 subtree now " << subtree->data << endl; 
		// 	// continue;
		// 	return;
		// }
		if (balanceFactor > 1) {
			if ((subtree->right->right && subtree->right->left && subtree->right->right->height > subtree->right->left->height) || (subtree->right->right && !subtree->right->left)) {
				lrotate(subtree);
			}
			else if ((subtree->right->right && subtree->right->left && subtree->right->right->height < subtree->right->left->height) || (!subtree->right->right && subtree->right->left)) {
				rrotate(subtree->right);
				// rlrotate(subtree->right);
				if (printDebug) cout << "printR " << printPreOrder() << endl;
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
				if (printDebug) cout << "printR " << printPreOrder() << endl;
				// rrotate(subtree->parent->parent);
			}
			else {
				rrotate(subtree->parent);
			}
		}
		
		if (printDebug) {cout << "after bf check: \ndata " << subtree->data << " height " << subtree->height << " child# " << subtree->numChild << " bf " << balanceFactor;
		if (subtree->parent) {cout <<" parent " << subtree->parent->data << " child# " << subtree->parent->numChild ;} 
		if (subtree->right) {cout <<" right " << subtree->right->data << " child# " << subtree->right->numChild ;}
		if (subtree->left) {cout <<" left " << subtree->left->data << " child# " << subtree->left->numChild ;} cout << endl;}
		// if (doUpdate) {
			subtree = subtree->parent;
			if (printDebug && subtree) cout << "subtree now " << subtree->data << endl; 
		// }
		// else {if (printDebug) {cout << "the cycle... is broken " << subtree->data << endl;} break;}
		// if (printDebug) {if (subtree->parent) cout << "subtree now " << subtree->parent->data << endl;
		// else cout << "subtree now NULL" << endl;} 
		// update(subtree->parent);
	}
	doUpdate = false;
	if (printDebug) cout << "update over" << endl;
}