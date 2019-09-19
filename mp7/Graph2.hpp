#include <queue>
#include <algorithm>
#include <string>
#include <list>

/**
 * Returns an std::list of vertex keys that creates some shortest path between `start` and `end`.
 *
 * This list MUST include the key of the `start` vertex as the first vertex in the list, the key of
 * the `end` vertex as the last element in the list, and an ordered list of all vertices that must
 * be traveled along the shortest path.
 * 
 * For example, the path a -> c -> e returns a list with three elements: "a", "c", "e".
 * 
 * @param start The key for the starting vertex.
 * @param end   The key for the ending vertex.
 */
template <class V, class E>
std::list<std::string> Graph<V,E>::shortestPath(const std::string start, const std::string end) {
  std::list<std::string> path;

	for(auto vert : vertexMap) {
		vert.second["label"] = "unexplored";
	}

	for(auto edge : edgeList) {
		edge.get()["label"] = "unexplored";
	}

	std::queue<std::string> q;
	q.push(start);
	vertexMap.at(start)["label"] = "explored";

	while (!q.empty()) {
		std::string curr = q.front();
		q.pop();

		for (auto edge : adjList.at(curr)) {
			if (vertexMap.at(edge->get().dest().key())["label"] == "unexplored") {
				q.push(edge->get().dest().key());
				vertexMap.at(edge->get().dest().key())["pred"] = curr;
				vertexMap.at(edge->get().dest().key())["label"] = "explored";
			}

			if (vertexMap.at(edge->get().source().key())["label"] == "unexplored") {
				q.push(edge->get().source().key());
				vertexMap.at(edge->get().source().key())["pred"] = curr;
				vertexMap.at(edge->get().source().key())["label"] = "explored";
			}
		}
	}

	std::string trav = end;
	while (trav != start) {
		path.push_front(trav);
		trav = vertexMap.at(trav)["pred"];
	}

	path.push_front(start);

	for (std::string node : path) {
		std::cout << node << "->";
	}

	std::cout << std::endl;

  return path;
}

