#include "Graph.h"
#include "Edge.h"
#include "Vertex.h"

#include <string>
#include <iostream>

/**
* @return The number of vertices in the Graph
*/
template <class V, class E>
unsigned int Graph<V,E>::size() const {
  // TODO: Part 2
  return vertexMap.size();
}


/**
* @return Returns the degree of a given vertex.
* @param v Given vertex to return degree.
*/
template <class V, class E>
unsigned int Graph<V,E>::degree(const V & v) const {
  // TODO: Part 2
  return adjList.find(v)->size();
}


/**
* Inserts a Vertex into the Graph by adding it to the Vertex map and adjacency list
* @param key The key of the Vertex to insert
* @return The inserted Vertex
*/
template <class V, class E>
V & Graph<V,E>::insertVertex(std::string key) {
  // TODO: Part 2
  V & v = *(new V(key));
	vertexMap.emplace(key, v);
	std::list<edgeListIter> empty_list;
	adjList.emplace(key, empty_list);
  return v;
}


/**
* Removes a given Vertex
* @param v The Vertex to remove
*/
template <class V, class E>
void Graph<V,E>::removeVertex(const std::string & key) {
  // TODO: Part 2
	std::list<std::reference_wrapper<E>> edges = incidentEdges(key);
	for(edgeListIter it = edges.begin(); it != edges.end(); ++it) {
		removeEdge(it);
	}
	vertexMap.erase(key);
}


/**
* Inserts an Edge into the adjacency list
* @param v1 The source Vertex
* @param v2 The destination Vertex
* @return The inserted Edge
*/
template <class V, class E>
E & Graph<V,E>::insertEdge(const V & v1, const V & v2) {
  // TODO: Part 2
  E & e = *(new E(v1, v2));
	edgeList.push_front(e);
	adjList.at(v1.key()).push_back(edgeList.begin());
	adjList.at(v2.key()).push_back(edgeList.begin());
  return e;
}


/**
* Removes an Edge from the Graph
* @param key1 The key of the ource Vertex
* @param key2 The key of the destination Vertex
*/
template <class V, class E>
void Graph<V,E>::removeEdge(const std::string key1, const std::string key2) {
  // TODO: Part 2
	for(auto it = edgeList.begin(); it != edgeList.end(); ++it) {
		auto & lookup = it->get();
		//check if directed
		if(lookup.directed() == true) {
			//if directed then check if key1 corresponds to source and key2 corresponds to dest
			if(lookup.source() == vertexMap.at(key1) && lookup.dest() == vertexMap.at(key2)) {
				edgeList.erase(it);
				adjList.at(key1).remove(it);
				adjList.at(key2).remove(it);
				return;
			}
		} else {
			//if not directed check if both of the keys are the source and dest
			if((lookup.source() == vertexMap.at(key1) && lookup.dest() == vertexMap.at(key2)) ||
					(lookup.source() == vertexMap.at(key2) && lookup.dest() == vertexMap.at(key1))) {
				edgeList.erase(it);
				adjList.at(key1).remove(it);
				adjList.at(key2).remove(it);
				return;
			}
		}
	}
}


/**
* Removes an Edge from the adjacency list at the location of the given iterator
* @param it An iterator at the location of the Edge that
* you would like to remove
*/
template <class V, class E>
void Graph<V,E>::removeEdge(const edgeListIter & it) {
  // TODO: Part 2
	V src = (it->get()).source();
	V dest = (it->get()).dest();
	removeEdge(src.key(), dest.key());
}


/**
* @param key The key of an arbitrary Vertex "v"
* @return The list edges (by reference) that are adjacent to "v"
*/
template <class V, class E>
const std::list<std::reference_wrapper<E>> Graph<V,E>::incidentEdges(const std::string key) const {
  // TODO: Part 2
  std::list<std::reference_wrapper<E>> edges;
  for (auto it : adjList.at(key)) {
 	  edges.push_back(*it);
   }
  return edges;
}


/**
* Return whether the two vertices are adjacent to one another
* @param key1 The key of the source Vertex
* @param key2 The key of the destination Vertex
* @return True if v1 is adjacent to v2, False otherwise
*/
template <class V, class E>
bool Graph<V,E>::isAdjacent(const std::string key1, const std::string key2) const {
  // TODO: Part 2
  if (adjList.at(key1).size() < adjList.at(key2).size()) {
		for (auto edge : adjList.at(key1)) {
			if ((*edge).get().source() == vertexMap.at(key2)) {
				return true;
			}
		}
	}
	else {
		for (auto edge : adjList.at(key2)) {
			if ((*edge).get().source() == vertexMap.at(key1)) {
				return true;
			}
		}
	}
  return false;
}
