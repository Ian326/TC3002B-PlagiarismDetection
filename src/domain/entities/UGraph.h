#ifndef UGRAPH_H
#define UGRAPH_H

#include <iterator>
#include <iostream>
#include <sstream>
#include <set>
#include <map>


/**
 * @class UGraph
 * @brief This class represents a CFG.
 */
template<class Vertex>
class UGraph {
    private:
        bool direction;
        std::set<Vertex> vertexes;
        std::map<Vertex, std::set<Vertex>> edges;
    
    public:
        UGraph(bool direction = true);
        ~UGraph();
        void addEdge(Vertex from, Vertex to);
        std::set<Vertex> getVertexes() const;
	    std::set<Vertex> getConnectionFrom(Vertex v) const;
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
void UGraph<Vertex>::addEdge(Vertex from, Vertex to){
    typename std::set<Vertex>::iterator it;

    it = vertexes.find(from);
    if (it == vertexes.end()) {
        vertexes.insert(from);
        edges.insert(std::make_pair(from, std::set<Vertex>()));
    }

    it = vertexes.find(to);
    if (it == vertexes.end()) {
        vertexes.insert(to);
        edges.insert(std::make_pair(to, std::set<Vertex>()));
    }

    edges[from].insert(to);

    if (!direction){
        edges[to].insert(from);
    }
}


/**
 * @brief This mehtod get all the vertexes in the graph.
 * @return Set of vertexes
 */
template<class Vertex>
std::set<Vertex> UGraph<Vertex>::getVertexes() const{
    return this->vertexes;
}


/**
 * @brief This method get all the connections from one vertex.
 * @return Set of vertexes
 */
template<class Vertex>
std::set<Vertex> UGraph<Vertex>::getConnectionFrom(Vertex v) const {
    return this->edges[v];
}


/**
 * @brief This method returns the graph in a readable string.
 * @return String representing the constructed graph
 */
template<class Vertex>
std::string UGraph<Vertex>::toString() const {
    std::stringstream ss;
    typename std::set<Vertex>::iterator vertexItr, edgeItr;
    
    for(vertexItr = vertexes.begin(); vertexItr != vertexes.end(); vertexItr++) {
        ss << "Vertex: " << (*vertexItr) << "\nConnections: ";

        for(edgeItr = edges.at((*vertexItr)).begin(); edgeItr != edges.at((*vertexItr)).end(); edgeItr++) {
            ss << (*edgeItr) << "\t";
        }
        ss << "\n\n";
    }
    ss << "\n";
    
    return ss.str();
}

#endif // UGRAPH_H