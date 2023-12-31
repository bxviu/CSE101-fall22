#include "graph.h"
#include <iostream>
#include <stdexcept>
#include <fstream>
#include <string>
#include <unordered_map>
#include <queue>
using namespace std;

int main(int argc, char** argv) {
	if (argc < 3) {
		throw std::invalid_argument("Usage: ./sixdegrees <INPUT FILE> <OUTPUT FILE");
	}

	ifstream infile;
	ofstream outfile;
	string input, actor1, actor2, found;
	size_t cutOff = 0;
	bool isMovie = true;
	ActorGraph actors;
	MovieGraph movies;
	Movie* m;

	infile.open("cleaned_movielist.txt");
	while (getline(infile, input)) {
		isMovie = true;
		while ((cutOff = input.find(" ")) != string::npos) {
			found = input.substr(0,cutOff);
			if (isMovie) {
				m = movies.createMovie(found);
				isMovie = false;
			}
			else {
				if (!actors.actorExists(found)) {
					actors.createActor(found);
				}
				actors.addMovie(found, m);
				movies.addActor(m, found);
			}
			input.erase(0, cutOff+1);
		}
	}
	infile.close();

	infile.open(argv[1]);
	outfile.open(argv[2]);

	while (getline(infile, input)) {
		actor1 = actor2 = "";
		cutOff = input.find(" ");
		actor1 = input.substr(0,cutOff);
		input.erase(0,cutOff+1);
		cutOff = input.find("\n");
		actor2 = input.substr(0,cutOff);
		input.erase(0,cutOff+1);
		outfile << findLink(actor1, actor2, movies, actors) << endl;
	}
		
	infile.close();
	outfile.close();
}