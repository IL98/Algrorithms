//
// Created by ilya on 22.02.17.
//

#ifndef GRAPH_IGRAPH_H
#define GRAPH_IGRAPH_H

#include <vector>


class IGraph
{
public:
    virtual ~IGraph(){};
    virtual void AddEdge(int from, int in) = 0;
    virtual void GetNextVertices(int vertex, std::vector<int>& vertices) const = 0;
    virtual void GetPrevVertices(int vertex, std::vector<int>& vertices) const = 0;

};



#endif //GRAPH_IGRAPH_H
