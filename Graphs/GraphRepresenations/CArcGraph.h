//
// Created by ilya on 24.02.17.
//

#ifndef GRAPH_CARCGRAPH_H
#define GRAPH_CARCGRAPH_H

#include "IGraph.h"
#include <map>
using std :: multimap;

class CArcGraph : public IGraph
{
private:
    int vertices_count;
    multimap <int, int> arr;
public:
    CArcGraph(int count);
    void AddEdge(int from, int in) ;
    void GetNextVertices(int vertex, std::vector<int>& vertices) const ;
    void GetPrevVertices(int vertex, std::vector<int>& vertices) const ;
};

#endif //GRAPH_CARCGRAPH_H
