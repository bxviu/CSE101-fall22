#include <iostream>
#include <stack>
#include <stdexcept>
#include <fstream>
#include <string>
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
	private:
		// int arrayEnd = 0;
		// Queen* qArray;
	public:
		int arrayEnd = 0;
		Queen* qArray[1];
		int dim;
		QueenBoard() {
			dim = 0;
		} 
		QueenBoard(int dimension) {
			Queen newQArray[dimension];
			dim = dimension;
			*qArray = newQArray;
			// cout << "new size: " << dim << endl;
		} 

		bool queenAllowed(Queen q) {
			cout << "checking: " << q.column << ", " << q.row <<endl;
			for (int i = 0; i < arrayEnd; i++) {
				cout << qArray[i]->column << ", " << qArray[i]->row << " at " << i << endl;
				if (qArray[i]->column == q.column || qArray[i]->row == q.row) {
					cout << "on row or column " << qArray[i]->column <<"," << qArray[i]->row << "|" << q.column << "," << q.row<<endl;
					return false;
				}
				if (abs(q.column-qArray[i]->column) == abs(q.row-qArray[i]->row)) {
					cout << "on diagonal " << qArray[i]->column <<"," << qArray[i]->row << "|" << q.column << "," << q.row<<endl;
					return false;
				}
			}
			cout << "accepting: " << q.column << ", " << q.row <<endl;
			return true;
		}

		bool addQueen(Queen q) {
			if (!queenAllowed(q)) return false;
			// cout << q.column << ", " << q.row << " added" << endl;
			// cout << arrayEnd << endl;
			qArray[arrayEnd] = &q;
			arrayEnd++;
			cout << qArray[arrayEnd-1]->column << ", " << qArray[arrayEnd-1]->row << " in array" << endl;
			cout << qArray[0]->column << ", " << qArray[0]->row << endl;
			// cout << arrayEnd << endl;
			// if (qArray) cout << typeid(qArray).name() << endl;
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
	bool isCol, isRow;
	QueenBoard qBoard;
	while (getline(infile, input)) {
		dimension = column = row = cutOff = -1;
		isCol = isRow = false;
		while ((size_t)(cutOff = input.find(" ")) != string::npos || input.length() == 1) {
			if (dimension == -1) {
				dimension = stoi(input.substr(0,cutOff));
				qBoard = QueenBoard(dimension);
				isCol = true;
			}
			else if (isCol) {
				column = stoi(input.substr(0,cutOff));
				isRow = true;
				isCol = !isRow;
			}
			else if (isRow) {
				row = stoi(input.substr(0,cutOff));
				if (input.length() == 1) cutOff = 0;
				isCol = true;
				isRow = !isCol;
			}
			input.erase(0, cutOff+1);
			if (isCol && column != -1 && row != -1) {
				Queen newQ(column, row);
				// Pair p = Pair(qBoard, newQ);
				// qStack.push(p);
				// cout << "got input: " << column << ", " << row<<endl;
				cout << "got input: " << newQ.column << ", " << newQ.row<<endl;
				qBoard.addQueen(newQ);
				// cout << "got input: " << newQ.column << ", " << newQ.row<<endl;
				if (qBoard.arrayEnd > 1) {
					QueenBoard bruh = qBoard;
					cout << "inputting: " << bruh.qArray[1]->column << ", " << bruh.qArray[1]->row << endl;
				}
			}
		}
		// for (int i = 1; i <= dimension; i++) {
		// 	for (int j = 1; j <= dimension; j++) {
		// 		Queen nextQ(i,j);
		// 		Pair p = Pair(qBoard, nextQ);
		// 		qStack.push(p);
		// 	}
		// }

		// while (!qStack.empty()) {
		// 	Pair top = qStack.top();
		// 	qStack.pop();
		// 	top.qBoard.addQueen(top.q);
			// cout << top.q.column << " " << top.q.row << " dim: " << top.qBoard.dim << endl;
			// for (int i = 0; i < top.qBoard.arrayEnd; i++) {
				// cout << top.qBoard.qArray[i]->row << ", ";
				// cout << top.qBoard.qArray[i]->column << endl; 
			// }
			// cout << endl;
		// }	

		cout << "\nnext line" << endl;
	}

	//need to add possible positions to stack, after seeing the columns and rows that 
	//cant be used, since a queen is already there (diagonals too). Store given queens
	//in an array so the possible queen positions check be checked with them
	
	//nevermind, instead push queenBoard to stack, which has the positions of queens that are
	//currently being tested, and once there are n queens in the board, then it should be solved

	//need to:
	//insert queens into qBoard
	
	infile.close();
	outfile.close();
}
