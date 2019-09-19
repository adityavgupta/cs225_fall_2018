/**
 * @file NetworkFlow.cpp
 * CS 225: Data Structures
 */

#include <vector>
#include <algorithm>
#include <set>

#include "graph.h"
#include "edge.h"

#include "NetworkFlow.h"

int min(int a, int b) {
  if (a<b)
    return a;
  else return b;
}

NetworkFlow::NetworkFlow(Graph & startingGraph, Vertex source, Vertex sink) :
  g_(startingGraph), residual_(Graph(true,true)), flow_(Graph(true,true)), source_(source), sink_(sink) {

  // YOUR CODE HERE
	  
	  //set the vertices according to the orignal graph
	  std::vector<Vertex> vertices_of_og = startingGraph.getVertices();
	  for(unsigned i = 0; i < vertices_of_og.size(); i++) {
		  residual_.insertVertex(vertices_of_og[i]);
		  flow_.insertVertex(vertices_of_og[i]);
	  }

	  //set the edges according to the original graph 
	  std::vector<Edge> edges_of_og = startingGraph.getEdges();
	  for(unsigned i = 0; i < edges_of_og.size(); i++) {

		  flow_.insertEdge(edges_of_og[i].source, edges_of_og[i].dest);
		  residual_.insertEdge(edges_of_og[i].source, edges_of_og[i].dest);
		  residual_.insertEdge(edges_of_og[i].dest, edges_of_og[i].source);

		  //set the weights
		  flow_.setEdgeWeight(edges_of_og[i].source, edges_of_og[i].dest, 0); // for flow graph set all the weights to 0

		  residual_.setEdgeWeight(edges_of_og[i].source, edges_of_og[i].dest, edges_of_og[i].getWeight());
		  // for residual graph set weights in the direction of og graph the same as og graph
		  
		  residual_.setEdgeWeight(edges_of_og[i].dest, edges_of_og[i].source, 0); // for reverse edges set them to 0
	  }
}	  

  /**
   * findAugmentingPath - use DFS to find a path in the residual graph with leftover capacity.
   *  This version is the helper function.
   *
   * @@params: source -- The starting (current) vertex
   * @@params: sink   -- The destination vertex
   * @@params: path   -- The vertices in the path
   * @@params: visited -- A set of vertices we have visited
   */

bool NetworkFlow::findAugmentingPath(Vertex source, Vertex sink, 
  std::vector<Vertex> &path, std::set<Vertex> &visited) {

  if (visited.count(source) != 0)
    return false;
  visited.insert(source);

  if (source == sink) {
    return true;
  }

  vector<Vertex> adjs = residual_.getAdjacent(source);
  for(auto it = adjs.begin(); it != adjs.end(); it++) {
    if (visited.count(*it) == 0 && residual_.getEdgeWeight(source,*it) > 0) {
      path.push_back(*it);
      if (findAugmentingPath(*it,sink,path,visited))
        return true;
      else {
        path.pop_back();
      }
    }
  }

  return false;
}

  /**
   * findAugmentingPath - use DFS to find a path in the residual graph with leftover capacity.
   *  This version is the main function.  It initializes a set to keep track of visited vertices.
   *
   * @@params: source -- The starting (current) vertex
   * @@params: sink   -- The destination vertex
   * @@params: path   -- The vertices in the path
   */

bool NetworkFlow::findAugmentingPath(Vertex source, Vertex sink, std::vector<Vertex> &path) {
   std::set<Vertex> visited;
   path.clear();
   path.push_back(source);
   return findAugmentingPath(source,sink,path,visited);
}

  /**
   * pathCapacity - Determine the capacity of a path in the residual graph.
   *
   * @@params: path   -- The vertices in the path
   */

int NetworkFlow::pathCapacity(const std::vector<Vertex> & path) const {
  // YOUR CODE HERE
  int min_weight = 0;
  for(unsigned i = 0; i < path.size(); i++) {
	  if(i+1 < path.size() && i+2 < path.size()) {
		  int cur = residual_.getEdgeWeight(path[i], path[i+1]);
		  int c_next = residual_.getEdgeWeight(path[i+1], path[i+2]);
		  min_weight = min(cur, c_next);
	  }
  }
  return min_weight;
}

  /**
   * calculuateFlow - Determine the capacity of a path in the residual graph.
   * Sets the member function `maxFlow_` to be the flow, and updates the
   * residual graph and flow graph according to the algorithm.
   *
   * @@outputs: The network flow graph.
   */

const Graph & NetworkFlow::calculateFlow() {
  // YOUR CODE HERE
  maxFlow_ = 0;
  std::vector<Vertex> paths = residual_.getVertices();
  int path_cap = 0;

  while(findAugmentingPath(source_,	sink_, paths)) {
		path_cap = pathCapacity(paths);
		
  }
	
  return flow_;
}

int NetworkFlow::getMaxFlow() const {
  return maxFlow_;
}

const Graph & NetworkFlow::getGraph() const {
  return g_;
}

const Graph & NetworkFlow::getFlowGraph() const {
  return flow_;
}

const Graph & NetworkFlow::getResidualGraph() const {
  return residual_;
}

