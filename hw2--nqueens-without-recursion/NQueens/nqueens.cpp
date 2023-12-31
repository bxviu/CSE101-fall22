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
			for (int i = 0; i < (int)qVec.size(); i++) {
				if (abs(q.column-qVec[i].column) == abs(q.row-qVec[i].row)) {
					return false;
				}
			}
			return true;
		}

		bool addQueen(Queen q) {
			availableCol.erase(*availableCol.find(q.column));
			availableRow.erase(*availableRow.find(q.row));
			qVec.push_back(q);
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
			for (int i = 0; i < (int)qVec.size(); i++) {
				for (int j = 0; j < (int)qVec.size(); j++) {
					if (i != j && (qVec[i].column == qVec[j].column || qVec[i].row == qVec[j].row || abs(qVec[j].column-qVec[i].column) == abs(qVec[j].row-qVec[i].row))) {
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
		while ((size_t)(cutOff = input.find(" ")) != string::npos || input.length() >= 1) {
			if (dimension == -1) {
				dimension = stoi(input.substr(0,cutOff));
				qBoard = QueenBoard(dimension);
				isCol = true;
			}
			else if (isCol) {
				if (input.length() == 1 || input.length() == 2) {
					cutOff = (int)string::npos;
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
			if (isCol && column != -1 && row != -1) {
				Queen newQ(column, row);
				if (qBoard.queenAllowed(newQ) && (int)qBoard.qVec.size() <= dimension) {
					qBoard.addQueen(newQ);
					column = row = -1;
				}
				else {
					valid = false;
					break;
				}
			}
		}
		if (!valid) {
			outfile << "No solution" << endl;
			continue;
		}
		if (qStack.empty() && (int)qBoard.qVec.size() != dimension) {
			for (set<int>::reverse_iterator j = qBoard.availableRow.rbegin(); j != qBoard.availableRow.rend(); ++j) {
				Queen nextQ(*qBoard.availableCol.begin(),*j);
				QueenBoard qBo = qBoard;
				if (qBo.queenAllowed(nextQ)) {
					Pair p = Pair(qBo, nextQ);
					qStack.push(p);
				}
			}
		}
		Pair top = qStack.empty() ? Pair(qBoard,Queen()) : qStack.top();
		while (!qStack.empty()){
			top = qStack.top();
			qStack.pop();

			if (top.qBoard.queenAllowed(top.q)) {
				top.qBoard.addQueen(top.q);
				if (top.qBoard.availableCol.size() == 0 && top.qBoard.availableRow.size() == 0 ){
					break;
				}
				for (set<int>::reverse_iterator j = top.qBoard.availableRow.rbegin(); j != top.qBoard.availableRow.rend(); ++j) {
					Queen nextQ(*top.qBoard.availableCol.begin(),*j);
					if (top.qBoard.queenAllowed(nextQ)) {
						Pair p = Pair(top.qBoard, nextQ);
						qStack.push(p);
					}
				}
			}
			
		}
		if ((int)top.qBoard.qVec.size() == top.qBoard.dim && top.qBoard.validBoard()) {
			top.qBoard.sort();
			for (int i = 0; i < (int)top.qBoard.qVec.size(); i++) {
				outfile << top.qBoard.qVec[i].column << " " << top.qBoard.qVec[i].row << " ";
			}
			outfile << endl;	
		}
		else {
			outfile << "No solution" << endl;
		}
		while (!qStack.empty()) {qStack.pop();}
	}
	
	infile.close();
	outfile.close();
}