//
// Created by ilya on 23.02.17.
//

#include "CLIstGraph.h"

ClistGraph ::ClistGraph(int count)
{
    forward_list<int > List;
    for (int i(0); i<count;i++ )
    {
        AdjList.push_back(List);
    }
    vertices_count=count;
}


void ClistGraph ::AddEdge(int from, int in)
{
    AdjList[from].push_front(in);
}


void ClistGraph ::GetNextVertices(int vertex, std::vector<int> &vertices) const {
   for ( auto i : AdjList[vertex]){
       vertices.push_back(i);
   }
}


void ClistGraph::GetPrevVertices(int vertex, std::vector<int> &vertices) const
{
  for (int i(0); i < vertices_count; i++){
      for (auto j : AdjList[i])
          if (j==vertex) {
              vertices.push_back(i);
              break;
          }
  }
}