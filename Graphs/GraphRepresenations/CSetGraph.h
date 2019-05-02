//
// Created by ilya on 24.02.17.
//

#ifndef GRAPH_CSETGRAPH_H
#define GRAPH_CSETGRAPH_H

#include "IGraph.h"
#include <unordered_set>
using std :: unordered_set;


class CSetGraph : public  IGraph
{
    unordered_set <int> *arr;
    int vertices_count;
public:
    CSetGraph(int count);
    ~CSetGraph();
    void AddEdge(int from, int in) ;
    void GetNextVertices(int vertex, std::vector<int>& vertices) const ;
    void GetPrevVertices(int vertex, std::vector<int>& vertices) const ;
};


#endif //GRAPH_CSETGRAPH_H
