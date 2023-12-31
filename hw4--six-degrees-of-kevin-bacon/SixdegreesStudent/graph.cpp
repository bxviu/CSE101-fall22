#include "graph.h" 
#include <unordered_map>
#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <queue>
using namespace std;

MovieGraph :: MovieGraph() {
	// (set<Movie>)g = new set<Movie>;
}

Movie* MovieGraph :: createMovie(string movie) {
	Movie newMovie(movie);
	unordered_map<string,vector<Movie>>::iterator i = g.find(movie);
	if (i != g.end()) {
		newMovie.setId((i->second.size()));
		i->second.push_back(newMovie);
		return &(i->second.back());
	}
	vector<Movie> newMVector = {newMovie};
	g.emplace(movie, newMVector);
	return &((g.find(movie)->second).back());
}

void MovieGraph :: addActor(Movie* m, string actor) {
	m->addActorM(actor);
}

ActorGraph :: ActorGraph() {
	// (unordered_map<string, set<Movie>>)g = new unordered_map<string, set<Movie>>;
}

void ActorGraph :: createActor(string actor) {
	vector<Movie> movies;
	g[actor] = movies;
}

void ActorGraph :: addMovie(string actor, Movie* m) {
	vector<Movie> temp = g[actor];
	temp.push_back(*m);
	g[actor] = temp;
}

bool ActorGraph :: actorExists(string actor) {
	return (g.find(actor) != g.end());
}

string findLink(string startActor, string endActor, MovieGraph mG, ActorGraph aG) {
	if (!aG.actorExists(startActor) || !aG.actorExists(endActor)) {return "Not present";}
	if (startActor == endActor) {return startActor;}
	queue<GraphVertexGroup> qGV;
	unordered_map<string, vector<Movie>> seenMovies;
	set<GraphVertex> seenActors;
	qGV.push(GraphVertexGroup(GraphVertex(startActor)));
	while (!qGV.empty()) {
		GraphVertexGroup saved = qGV.front();
		GraphVertexGroup grp = qGV.front();
		GraphVertex gv = grp.gvg.back();
		qGV.pop();
		if (gv.isMovie) {
			for (auto i = gv.movie->actors.begin(); i != gv.movie->actors.end(); ++i) {
				if (seenActors.find(GraphVertex(*i)) != seenActors.end()) {continue;}
				seenActors.emplace(GraphVertex(*i));
				grp.gvg.push_back(GraphVertex(*i));
				qGV.push(grp);
				grp = saved;
			}
		}
		else {
			if (gv.actor == endActor) {
				string result = "";
				for (size_t i = 0; i < grp.gvg.size(); i++) {
					result += grp.gvg[i].isMovie ? ("-(" + grp.gvg[i].movie->title + ")- ") : (grp.gvg[i].actor + " "); 
				}
				return result;
			}
			vector<Movie> vM = aG.g[gv.actor];
			for (size_t i = 0; i < vM.size(); i++) {
				bool skip = false;
				GraphVertex movieToCheck(&((mG.g[vM[i].getTitle()])[vM[i].getId()])); 
				if (seenMovies.find(movieToCheck.movie->getTitle()) != seenMovies.end()) {
					vector<Movie> sM = (seenMovies.find(movieToCheck.movie->getTitle())->second);
					for (auto it = sM.begin(); it != sM.end(); ++it) {
						if (it->getId() == movieToCheck.movie->getId()) {
							skip = true;
							break;
						}
					}
					
				}
				if (!skip) {
					vector<Movie> temp = seenMovies[movieToCheck.movie->getTitle()];
					temp.push_back(*movieToCheck.movie);
					seenMovies[movieToCheck.movie->getTitle()] = temp;
					grp.gvg.push_back(movieToCheck);
					qGV.push(grp);
					grp = saved;	
				}
			}
		}
	}
	return "Not present";
}