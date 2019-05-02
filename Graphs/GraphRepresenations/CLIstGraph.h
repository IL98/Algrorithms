//
// Created by ilya on 23.02.17.
//

#ifndef GRAPH_CLISTGRAPH_H
#define GRAPH_CLISTGRAPH_H

#include "IGraph.h"
#include <forward_list>
using std::forward_list;
class ClistGraph : public IGraph
{
private:
  std ::  vector<forward_list<int>> AdjList;
   int vertices_count;
public:
    ClistGraph(int count);
    void AddEdge(int from, int in) ;
    void GetNextVertices(int vertex, std::vector<int>& vertices) const;
    void GetPrevVertices(int vertex, std::vector<int>& vertices) const;
};

#endif //GRAPH_CLISTGRAPH_H
