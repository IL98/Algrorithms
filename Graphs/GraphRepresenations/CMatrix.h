//
// Created by ilya on 22.02.17.
//

#ifndef GRAPH_CMATRIX_H
#define GRAPH_CMATRIX_H
#include "IGraph.h"

#include <iostream>

using std::vector;

  class CMatrixGraph : public IGraph
  {
  private:
      vector<vector<int> > Matrix;
      int vertices_count;
  public:
      CMatrixGraph(int count);
      void AddEdge(int from, int in)  ;
      void GetNextVertices(int vertex, vector<int>& vertices) const ;
      void GetPrevVertices(int vertex, vector<int>& vertices) const;
  };



#endif //GRAPH_CMATRIX_H
