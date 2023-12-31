#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <unordered_map>
#include <set>
#include <vector>
using namespace std;

class Movie {
	public:
		int id = 0;
		string title = "";
		set<string> actors;
	
		Movie(string name) {
			title = name;
		}

		void addActorM(string actor) {
			actors.emplace(actor);
		}

		void setId(int newId) {
			id = newId;
		}
		
		int getId() {
			return id;
		}

		string getTitle() {
			return title;
		}
};

class GraphVertex {
	public:
		bool isMovie = false;
		int goBack = 0;
		Movie* movie;
		string actor = "";

		GraphVertex(Movie* m) {
			movie = m;
			isMovie = true;
		}

		GraphVertex(string a) {
			actor = a;
			isMovie = false;
		}

		GraphVertex(int i) {
			goBack = i;
		}

		// //from https://www.techiedelight.com/use-object-key-stdset-cpp/
		bool operator<(const GraphVertex &gv) const{
			return (gv.isMovie) ? (movie->title < gv.movie->title || (movie->title == gv.movie->title && movie->getId() < gv.movie->getId())) : actor < gv.actor;
		}
};

class GraphVertexGroup {
	public:
		vector<GraphVertex> gvg;

		GraphVertexGroup(GraphVertex gv) {
			gvg.push_back(gv);
		}
};

class ActorGraph {
	public:
		unordered_map<string, vector<Movie>> g;
		ActorGraph();
		void createActor(string actor);
		void addMovie(string actor, Movie* m);
		bool actorExists(string actor);
};

class MovieGraph {
	public:
		unordered_map<string, vector<Movie>> g;
		MovieGraph();
		Movie* createMovie(string movie);
		void addActor(Movie* m, string actor);
};

string findLink(string startActor, string endActor, MovieGraph, ActorGraph);

#endif