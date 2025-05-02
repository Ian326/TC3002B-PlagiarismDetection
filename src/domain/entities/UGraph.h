#ifndef UGRAPH_H
#define UGRAPH_H

#include <iterator>
#include <iostream>
#include <sstream>
#include <set>
#include <map>
#include<vector>


/**
 * @class UGraph
 * @brief This class represents a CFG.
 */
template<class Vertex>
class UGraph {
    private:
        bool direction;
        std::set<std::pair<int, Vertex>> vertexes;
        std::map<std::pair<int, Vertex>, std::set<std::pair<int, Vertex>>> edges;
    
    public:
        UGraph(bool direction = true);
        ~UGraph();
        void addEdge(std::pair<int, Vertex> from, std::pair<int, Vertex> to);
        std::vector<std::pair<int, Vertex>> getVertexes() const;
	    std::vector<std::pair<int, Vertex>> getConnectionsFrom(std::pair<int, Vertex>) const;
        std::vector<std::pair<int, Vertex>> getConnectionsFrom(std::string) const;
        std::string getTagFrom(int) const;
        std::pair<int, Vertex> getLastNode();
        std::string toString() const;
};


/**
 * @brief Constructor for the UGraph class (defaults to a directed graph).
 */
template<class Vertex>
UGraph<Vertex>::UGraph(bool direction) {
    this->direction = direction;
}


/**
 * @brief Destructor for the UGraph class.
 */
template<class Vertex>
UGraph<Vertex>::~UGraph(){}


/**
 * @brief Add connection between vertexes.
 * @param to Where the connection will be stored
 * @param from Vertex stored.
 *             If the graph is undirected, it will also store the vertex where the connection originates
 */
template<class Vertex>
void UGraph<Vertex>::addEdge(std::pair<int, Vertex> from, std::pair<int, Vertex> to){
    typename std::set<std::pair<int, Vertex>>::iterator it;

    it = vertexes.find(from);
    if (it == vertexes.end()) {
        vertexes.insert(from);
        edges.insert(std::make_pair(from, std::set<std::pair<int, Vertex>>()));
    }

    it = vertexes.find(to);
    if (it == vertexes.end()) {
        vertexes.insert(to);
        edges.insert(std::make_pair(to, std::set<std::pair<int, Vertex>>()));
    }

    edges[from].insert(to);

    if (!direction){
        edges[to].insert(from);
    }
}


/**
 * @brief This method gets all the vertexes in the graph.
 * @return Set of vertexes
 */
template<class Vertex>
std::vector<std::pair<int, Vertex>> UGraph<Vertex>::getVertexes() const{
    std::vector<std::pair<int, Vertex>> result(vertexes.begin(), vertexes.end());
	return result;
}


/**
 * @brief This method get all the connections from one vertex.
 * @return Set of vertexes
 */
template<class Vertex>
std::vector<std::pair<int, Vertex>> UGraph<Vertex>::getConnectionsFrom(std::pair<int, Vertex> v) const {
    std::vector<Vertex> result(edges.at(v).begin(), edges.at(v).end());
	return result;
}


/**
 * @brief Get connections for a given tag
 * @return Vector with count for a given vertex
 */
template<class Vertex>
std::vector<std::pair<int, Vertex>> UGraph<Vertex>::getConnectionsFrom(std::string tag) const {
    std::vector<std::pair<int, Vertex>> ret;
    std::map<Vertex,int> connections;
    typename std::map<Vertex,int>::iterator it;

    for (const auto& pair : edges) {
        if (pair.first.second == tag){
            for (const auto& nodeConnections : pair.second) {
                connections[nodeConnections.second]++;
            }
        }
    }

    for (const auto& pair : connections) {
        ret.push_back(std::make_pair(pair.second, pair.first));
    }

    return ret;
}


/**
 * @brief Find tag for specified node
 * @return Tag associated to the number or empty if not found
 */
template<class Vertex>
std::string UGraph<Vertex>::getTagFrom(int node) const {
    for (const auto& pair : vertexes) {
        if (pair.first == node){
            return pair.second;
        }
    }

    return "";
}


/**
 * @brief Checks node's numbers to identify last one
 * @return Graph's last node
 */
template<class Vertex>
std::pair<int, Vertex> UGraph<Vertex>::getLastNode() {
    std::pair<int, Vertex> last;

    for (const auto& pair : vertexes) {
        if (pair.first > last.first){
            last = pair;
        }
    }
    return last;
}


/**
 * @brief This method returns the graph in a readable string.
 * @return String representing the constructed graph
 */
template<class Vertex>
std::string UGraph<Vertex>::toString() const {
    std::stringstream ss;
    typename std::set<std::pair<int, Vertex>>::iterator vertexItr, edgeItr;
    
    for(vertexItr = vertexes.begin(); vertexItr != vertexes.end(); vertexItr++) {
        ss << "Vertex " << vertexItr->first << ": " << vertexItr->second << "\nConnections:\n";

        for(edgeItr = edges.at(std::make_pair(vertexItr->first,vertexItr->second)).begin(); edgeItr != edges.at(std::make_pair(vertexItr->first,vertexItr->second)).end(); edgeItr++) {
            ss << "(" << edgeItr->first << "," << edgeItr->second << ")" << "\n";
        }
        ss << "\n\n";
    }
    ss << "\n";
    
    return ss.str();
}

#endif // UGRAPH_H