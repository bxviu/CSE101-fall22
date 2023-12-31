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
				// cout << "movie: " + m->getTitle() << endl;
				isMovie = false;
			}
			else {
				if (!actors.actorExists(found)) {
					actors.createActor(found);
				}
				// else {
				// 	cout << found << " exists" << endl;
				// 					for (int i = 0; i < actors.g[found].size(); i++) {
				// 		cout << actors.g[found].at(i).getTitle() << " ";
				// 	}
				// 	cout <<endl;
				// }
				actors.addMovie(found, m);//make sure to make stuff private again
				// cout << found << ", actor in movies: ";
				// for (int i = 0; i < actors.g[found].size(); i++) {
				// 	cout << actors.g[found].at(i).getTitle() << " ";
				// }
				// cout <<endl;
				movies.addActor(m, found);
				// cout << "movie with actors: ";
				// for (std::set<string>::iterator it=m->actors.begin(); it!=m->actors.end(); ++it) // from https://cplusplus.com/reference/set/set/begin/
    		// 	cout << ' ' << *it;
				// cout <<endl;
			}
			input.erase(0, cutOff+1);
		}
		// cout<< endl;

	}
		// cout << "done" << endl;
	/*
	cout << "movie with actors: " << endl;
	vector<Movie> mo = movies.g.find("The_Author")->second;
	for (int i = 0; i<mo.size(); i++) {

				for (std::set<string>::iterator it=mo[i].actors.begin(); it!=mo[i].actors.end(); ++it) 
    			cout << *it << ' ';
				cout <<endl;
	}
	for (int i = 0; i < actors.g["Troy_Bland"].size(); i++) {
					cout << actors.g["Troy_Bland"].at(i).getTitle() << " id: " << actors.g["Troy_Bland"].at(i).getId() << " ";
				}
cout << "\nmovie with actors: " << endl;
				mo = movies.g.find("A_Hero's_Heart")->second;
	for (int i = 0; i<mo.size(); i++) {

				for (std::set<string>::iterator it=mo[i].actors.begin(); it!=mo[i].actors.end(); ++it) 
    			cout << *it << ' ';
				cout <<endl;
	}

	/*
					for (int i = 0; i < actors.g["Christin_Able"].size(); i++) {
					cout << actors.g["Christin_Able"].at(i).getTitle() << " ";
				}
				cout << endl;
									for (int i = 0; i < actors.g["Jennifer_Hale"].size(); i++) {
					cout << actors.g["Jennifer_Hale"].at(i).getTitle() << " ";
				}
					cout << endl;
													for (int i = 0; i < actors.g["Arnold_Schwarzenegger"].size(); i++) {
					cout << actors.g["Arnold_Schwarzenegger"].at(i).getTitle() << " ";
				}*/
				/*cout << "Brad_Pitt" << endl;
				for (int i = 0; i < actors.g["Brad_Pitt"].size(); i++) {
					cout << actors.g["Brad_Pitt"].at(i).getTitle() << " ";
				}
				cout << endl;
				cout << "\nOn_Location:_Fight_Club: " << endl;
				vector<Movie> mo = movies.g.find("On_Location:_Fight_Club")->second;
				for (int i = 0; i<mo.size(); i++) {
					for (std::set<string>::iterator it=mo[i].actors.begin(); it!=mo[i].actors.end(); ++it) 
						cout << *it << ' ';
					cout <<endl;
				}
				cout << "Edward_Norton" << endl;
				for (int i = 0; i < actors.g["Edward_Norton"].size(); i++) {
					cout << actors.g["Edward_Norton"].at(i).getTitle() << " ";
				}
				cout << endl;
				cout << "\nThe_Making_of_'The_Illusionist': " << endl;
				mo = movies.g.find("The_Making_of_'The_Illusionist'")->second;
				for (int i = 0; i<mo.size(); i++) {
					for (std::set<string>::iterator it=mo[i].actors.begin(); it!=mo[i].actors.end(); ++it) 
						cout << *it << ' ';
					cout <<endl;
				}
				cout << "Jessica_Biel" << endl;
				for (int i = 0; i < actors.g["Jessica_Biel"].size(); i++) {
					cout << actors.g["Jessica_Biel"].at(i).getTitle() << " ";
				}
				cout << endl;
				cout << "\nJT:_Reflections: " << endl;
				mo = movies.g.find("JT:_Reflections")->second;
				for (int i = 0; i<mo.size(); i++) {
					for (std::set<string>::iterator it=mo[i].actors.begin(); it!=mo[i].actors.end(); ++it) 
						cout << *it << ' ';
					cout <<endl;
				}
				cout << "Justin_Timberlake" << endl;
				for (int i = 0; i < actors.g["Justin_Timberlake"].size(); i++) {
					cout << actors.g["Justin_Timberlake"].at(i).getTitle() << " ";
				}
				cout << endl;
				cout << "\nJustin_Timberlake:_Justified_-_The_Videos: " << endl;
				mo = movies.g.find("Justin_Timberlake:_Justified_-_The_Videos")->second;
				for (int i = 0; i<mo.size(); i++) {
					for (std::set<string>::iterator it=mo[i].actors.begin(); it!=mo[i].actors.end(); ++it) 
						cout << *it << ' ';
					cout <<endl;
				}
				cout << "Nelly" << endl;
				for (int i = 0; i < actors.g["Nelly"].size(); i++) {
					cout << actors.g["Nelly"].at(i).getTitle() << " ";
				}
				cout << endl;
				cout << "\nNelly_&_St._Lunatics:_Batter_Up: " << endl;
				mo = movies.g.find("Nelly_&_St._Lunatics:_Batter_Up")->second;
				for (int i = 0; i<mo.size(); i++) {
					for (std::set<string>::iterator it=mo[i].actors.begin(); it!=mo[i].actors.end(); ++it) 
						cout << *it << ' ';
					cout <<endl;
				}
				cout << "Ali" << endl;
				for (int i = 0; i < actors.g["Ali"].size(); i++) {
					cout << actors.g["Ali"].at(i).getTitle() << " ";
				}
				cout << endl;
				cout << "\nKhaidi_No._150: " << endl;
				mo = movies.g.find("Khaidi_No._150")->second;
				for (int i = 0; i<mo.size(); i++) {
					for (std::set<string>::iterator it=mo[i].actors.begin(); it!=mo[i].actors.end(); ++it) 
						cout << *it << ' ';
					cout <<endl;
				}
				cout << "Chiranjeevi" << endl;
				for (int i = 0; i < actors.g["Chiranjeevi"].size(); i++) {
					cout << actors.g["Chiranjeevi"].at(i).getTitle() << " ";
				}
				cout << endl;
				cout << "\nSye_Raa_Narasimha_Reddy: " << endl;
				mo = movies.g.find("Sye_Raa_Narasimha_Reddy")->second;
				for (int i = 0; i<mo.size(); i++) {
					for (std::set<string>::iterator it=mo[i].actors.begin(); it!=mo[i].actors.end(); ++it) 
						cout << *it << ' ';
					cout <<endl;
				}
				cout << "Amitabh_Bachchan" << endl;
				for (int i = 0; i < actors.g["Amitabh_Bachchan"].size(); i++) {
					cout << actors.g["Amitabh_Bachchan"].at(i).getTitle() << " ";
				}
				cout << endl;*/

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