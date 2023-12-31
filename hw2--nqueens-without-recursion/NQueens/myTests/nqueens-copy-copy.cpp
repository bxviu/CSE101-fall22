#include <iostream>
#include <stack>
#include <stdexcept>
#include <fstream>
#include <string>
#include <vector>
#include <set>
using namespace std;

class Queen {
	public:
		int column, row;
		Queen() {
			column = 0;
			row = 0;
		}
		Queen(int y, int x) {
			column = y;
			row = x;
		}
};

class QueenBoard {
	public:
		int dim;
		vector<Queen> qVec;
		set<int> availableCol, availableRow;
		QueenBoard() {
			dim = 0;
		} 
		QueenBoard(int dimension) {
			dim = dimension;
			for (int i = 1; i <= dimension; i++) {
				availableCol.insert(i);
				availableRow.insert(i);
			}
		} 

		bool queenAllowed(Queen q) {
			// cout << "checking: " << q.column << ", " << q.row; //<<endl;
			// cout << ", board: ";
			// for (int i = 0; i < (int)qVec.size(); i++) {
			// 	// cout << top.qBoard.qVec[i].column << ", " << top.qBoard.qVec[i].row << " | ";
			// 	cout << qVec[i].column << " " << qVec[i].row << ", ";
			// }
			// cout << endl;
			for (int i = 0; i < (int)qVec.size(); i++) {
				// cout << qVec[i].column << ", " << qVec[i].row << " at " << i << endl;
				if (qVec[i].column == q.column || qVec[i].row == q.row || abs(q.column-qVec[i].column) == abs(q.row-qVec[i].row)) {
					// cout << "on row or column " << qVec[i].column <<"," << qVec[i].row << "|" << q.column << "," << q.row<<endl;
					return false;
				}
				// if (abs(q.column-qVec[i].column) == abs(q.row-qVec[i].row)) {
				// 	// cout << "on diagonal " << qVec[i].column <<"," << qVec[i].row << "|" << q.column << "," << q.row<<endl;
				// 	return false;
				// }
			}
			// cout << "queen allowed: " << q.column << ", " << q.row <<endl;
			return true;
		}

		bool addQueen(Queen q) {
			// if (!queenAllowed(q)) return false;
			// cout << q.column << ", " << q.row << " added" << endl;
			// cout << arrayEnd << endl;
			// for (set<int>::iterator i = availableCol.begin(); i != availableCol.end(); ++i) {
			// 	cout << *i << " ";
			// }
			// for (set<int>::iterator j = availableRow.begin(); j != availableRow.end(); ++j) {
			// 	cout << *j << ", ";
			// }
			availableCol.erase(*availableCol.find(q.column));
			availableRow.erase(*availableRow.find(q.row));
			qVec.push_back(q);
			// cout << "adding " << q.column << " " << q.row << ", board: ";
			// for (int i = 0; i < (int)qVec.size(); i++) {
			// 	cout << qVec[i].column << " " << qVec[i].row << ", ";
			// }
			// cout << "col: ";
			// 			for (set<int>::iterator i = availableCol.begin(); i != availableCol.end(); ++i) {
			// 	cout << *i << " ";
			// }
			// cout << " row: ";
			// for (set<int>::iterator j = availableRow.begin(); j != availableRow.end(); ++j) {
			// 	cout << *j << " ";
			// }
			// cout << endl;
			// cout << qArray[arrayEnd-1].column << ", " << qArray[arrayEnd-1].row << " in array" << endl;
			// cout << qArray[0].column << ", " << qArray[0].row << endl;
			// cout << arrayEnd << endl;
			// if (qArray) cout << typeid(qArray).name() << endl;
			return true;
		}

		void sort() {
			Queen temp = qVec[0];
			for (int i = 0; i < (int)qVec.size(); i++) {
				for (int j = i; j < (int)qVec.size(); j++) {
					if (qVec[j].column < qVec[i].column) {
						temp = qVec[j];
						qVec[j] = qVec[i];
						qVec[i] = temp;
					}
				}
			}
		}

		bool validBoard() {
			// cout << "board: " << endl;
			// for (int i = 0; i < (int)qVec.size(); i++) {
			// 	// cout << top.qBoard.qVec[i].column << ", " << top.qBoard.qVec[i].row << " | ";
			// 	cout << qVec[i].column << " " << qVec[i].row << " ";
			// }
			// cout << endl;
			for (int i = 0; i < (int)qVec.size(); i++) {
				for (int j = 0; j < (int)qVec.size(); j++) {
					if (i != j && (qVec[i].column == qVec[j].column || qVec[i].row == qVec[j].row || abs(qVec[j].column-qVec[i].column) == abs(qVec[j].row-qVec[i].row))) {
						cout << "NO\n" <<endl; 
						return false;
					}
				}
			}
			return true;
		}
};

class Pair {
	public:
		QueenBoard qBoard;
		Queen q;

		Pair(QueenBoard qB, Queen qu) {
			qBoard = qB;
			q = qu;
		}
};

int main(int argc, char** argv) {
	if (argc < 3) {
		throw std::invalid_argument("Usage: ./nqueens <INPUT FILE> <OUTPUT FILE>");
	}

	ifstream infile;
	ofstream outfile;

	infile.open(argv[1]);
	outfile.open(argv[2]);
	
	stack<class Pair> qStack;
	string input;
	int dimension, column, row, cutOff;
	bool isCol, isRow, valid;
	QueenBoard qBoard;
	while (getline(infile, input)) {
		dimension = column = row = cutOff = -1;
		isCol = isRow = false;
		valid = true;
		// qBoard = QueenBoard();
		while ((size_t)(cutOff = input.find(" ")) != string::npos || input.length() >= 1) {
			cout << "len " << input.length() << endl;
			if (dimension == -1) {
				dimension = stoi(input.substr(0,cutOff));
				qBoard = QueenBoard(dimension);
				isCol = true;
			}
			else if (isCol) {
				if (input.length() == 1 || input.length() == 2) {
					cutOff = string::npos;
					// if (column == -1 || row == -1) {valid = false;}
					break;
				}
				column = stoi(input.substr(0,cutOff));
				if (column > dimension || column < 1) {
					valid = false;
					break;
				}
				isRow = true;
				isCol = !isRow;
			}
			else if (isRow) {
				row = stoi(input.substr(0,cutOff));
				if (row > dimension || row < 1) {
					valid = false;
					break;
				}
				if (input.length() == 1) cutOff = 0;
				isCol = true;
				isRow = !isCol;
			}
			input.erase(0, cutOff+1);
			cout << input << " : " << column << ", " << row<<endl;
			if (isCol && column != -1 && row != -1) {
				Queen newQ(column, row);
				// qStack.push(p);
				// cout << "got input: " << column << ", " << row<<endl;
				// cout << "got input: " << newQ.column << ", " << newQ.row<<endl;
				if (qBoard.queenAllowed(newQ) && qBoard.qVec.size() <= dimension) {
					qBoard.addQueen(newQ);
					column = row = -1;
					// Pair p = Pair(qBoard, newQ);
					// qStack.push(p);
				}
				else {
					valid = false;
					break;
				}
				// cout << "got input: " << newQ.column << ", " << newQ.row<<endl;
				// if (qBoard.qVec.size() > 1) {
				// 	QueenBoard bruh = qBoard;
				// 	cout << "inputting: " << bruh.qVec[1].column << ", " << bruh.qVec[1].row << endl;
				// }
			}
			// else if (isCol && column == -1 && row == -1) {
				
			// }
		}
		// for (set<int>::iterator i = qBoard.availableCol.begin(); i != qBoard.availableCol.end(); ++i) {
		// 	cout << *i << " ";
		// }
		if (!valid) {
			outfile << "No solution" << endl;
			cout << "No 2Solution" << endl;
			continue;
		}
		if (qStack.empty() && qBoard.qVec.size() != dimension) {
			// cout << "emptiness" << endl;
			// for (int i = *qBoard.availableCol.begin(); i <= qBoard.dim; i++) {
			// 	Queen nextQ(i,1);
			// 	QueenBoard qBo = qBoard;
			// 	qBo.addQueen(nextQ);
			// 	Pair p = Pair(qBo, nextQ);
			// 	qStack.push(p);
			// }
			// 								cout << "col: ";
			// 			for (set<int>::iterator i = top.qBoard.availableCol.begin(); i != top.qBoard.availableCol.end(); ++i) {
			// 	cout << *i << " ";
			// }
			// cout << " row: ";
			// for (set<int>::iterator j = top.qBoard.availableRow.begin(); j != top.qBoard.availableRow.end(); ++j) {
			// 	cout << *j << " ";
			// }
			// cout << endl;
			for (set<int>::iterator j = qBoard.availableRow.begin(); j != qBoard.availableRow.end(); ++j) {
				Queen nextQ(*qBoard.availableCol.begin(),*j);
				QueenBoard qBo = qBoard;
				if (qBo.queenAllowed(nextQ)) {
					// qBo.addQueen(nextQ);
					Pair p = Pair(qBo, nextQ);
					qStack.push(p);
				}
			}
		}
		// cout << "wacc" << endl;
		Pair top = qStack.empty() ? Pair(qBoard,Queen()) : qStack.top();
		// while (!qStack.empty()) {
		// 	top = qStack.top();
		// 	qStack.pop();
		// 	for (int i = 1; i <= top.qBoard.dim; i++) {
		// 		for (int j = 1; j <= top.qBoard.dim; j++) {
		// 			Queen nextQ(i,j);
		// 			if (top.qBoard.queenAllowed(nextQ)) {
		// 				top.qBoard.addQueen(nextQ);
		// 				Pair p = Pair(top.qBoard, nextQ);
		// 				if ((int)top.qBoard.qVec.size() == top.qBoard.dim) {
		// 					break;
		// 				}
		// 				qStack.push(p);
		// 			}
		// 		}
		// 	}
		// }
		while (!qStack.empty() ){//&& (int)top.qBoard.qVec.size() != top.qBoard.dim) {
			top = qStack.top();
			qStack.pop();
			// 					cout << "col: ";
			// 			for (set<int>::iterator i = top.qBoard.availableCol.begin(); i != top.qBoard.availableCol.end(); ++i) {
			// 	cout << *i << " ";
			// }
			// cout << " row: ";
			// for (set<int>::iterator j = top.qBoard.availableRow.begin(); j != top.qBoard.availableRow.end(); ++j) {
			// 	cout << *j << " ";
			// }
			// cout << endl;

			if (top.qBoard.queenAllowed(top.q)) {
				top.qBoard.addQueen(top.q);
				// cout << "added: " << top.q.column << " " << top.q.row <<endl;
				if (top.qBoard.availableCol.size() == 0 && top.qBoard.availableRow.size() == 0 ){//&& top.qBoard.validBoard()){//(int)top.qBoard.qVec.size() == top.qBoard.dim && top.qBoard.validBoard()) {
					// cout << "valid";
					break;
				}
				set<int> tempCol,tempRow;
				tempCol = top.qBoard.availableCol;
				tempRow = top.qBoard.availableRow;
				// for (set<int>::iterator i = tempCol.begin(); i != tempCol.end(); ++i) {
				// 	for (set<int>::iterator j = tempRow.begin(); j != tempRow.end(); ++j) {
				// 		Queen nextQ(*i,*j);
				// 		// if (top.qBoard.queenAllowed(nextQ)) {
				// 			// top.qBoard.addQueen(nextQ);
				// 			Pair p = Pair(top.qBoard, nextQ);
				// 			// cout << "adding " << nextQ.column << " " << nextQ.row << ", board: ";
				// 			// for (int i = 0; i < (int)top.qBoard.qVec.size(); i++) {
				// 			// 	// cout << top.qBoard.qVec[i].column << ", " << top.qBoard.qVec[i].row << " | ";
				// 			// 	cout << top.qBoard.qVec[i].column << " " << top.qBoard.qVec[i].row << ", ";
				// 			// }
				// 			// cout << endl;
				// 			// if ((int)top.qBoard.qVec.size() == top.qBoard.dim) {
				// 			// 	break;
				// 			// }
				// 			cout << "pushing: " << nextQ.column << " " << nextQ.row <<endl;
				// 			qStack.push(p);
				// 	}
				// }
				for (set<int>::iterator j = tempRow.begin(); j != tempRow.end(); ++j) {
					Queen nextQ(*tempCol.begin(),*j);
					if (top.qBoard.queenAllowed(nextQ)) {
						Pair p = Pair(top.qBoard, nextQ);
						qStack.push(p);
					}
				}
			}
			
		}
		if ((int)top.qBoard.qVec.size() == top.qBoard.dim && top.qBoard.validBoard()) {
			top.qBoard.sort();
			cout << "board: " << endl;
			for (int i = 0; i < (int)top.qBoard.qVec.size(); i++) {
				// cout << top.qBoard.qVec[i].column << ", " << top.qBoard.qVec[i].row << " | ";
				cout << top.qBoard.qVec[i].column << " " << top.qBoard.qVec[i].row << " ";
				outfile << top.qBoard.qVec[i].column << " " << top.qBoard.qVec[i].row << " ";
			}
			outfile << endl;
			cout << endl;	
		}
		else {
			outfile << "No solution" << endl;
			cout << "No Solution" << endl;
		}
			// top.qBoard.addQueen(top.q);
			// cout << "board: " << endl;
			// for (int i = 0; i < (int)top.qBoard.qVec.size(); i++) {
			// cout << top.qBoard.qVec[i].column << ", " << top.qBoard.qVec[i].row << " | ";
			// }
			// cout << endl;
	
		while (!qStack.empty()) {qStack.pop();}

		cout << "\nnext line" << endl;
	}
	//need to add possible positions to stack, after seeing the columns and rows that 
	//cant be used, since a queen is already there (diagonals too). Store given queens
	//in an array so the possible queen positions check be checked with them
	
	//nevermind, instead push queenBoard to stack, which has the positions of queens that are
	//currently being tested, and once there are n queens in the board, then it should be solved

	//need to:
	//insert queens into qBoard
	//need to deal with stacks

	//try printing board when checked
	//not checking all spots

	//more queens than dimension check needed
	//find out why the board is fixed if there are multiple boards with no input

	//sometimes the length will be greater than 1 at the end since dimension isnt always length of 1, like 14 (length 2)
	
	infile.close();
	outfile.close();
}
