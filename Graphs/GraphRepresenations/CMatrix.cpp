//
// Created by ilya on 23.02.17.
//
#include "CMatrix.h"


CMatrixGraph ::CMatrixGraph(int count)
{
    vertices_count=count;
    Matrix.assign(count, vector <int> (count, 0));
}

void CMatrixGraph ::AddEdge(int from, int in)
{
    Matrix[from][in]=1;
}
void CMatrixGraph ::GetNextVertices(int vertex, vector<int> &vertices) const
{
    for (int i(0); i <vertices_count; i++){
        if (Matrix[vertex][i])
            vertices.push_back(i);
    }
}
void CMatrixGraph ::GetPrevVertices(int vertex, vector<int> &vertices) const
{
    for (int i(0); i <vertices_count; i++){
        if (Matrix[i][vertex])
            vertices.push_back(i);
    }
}

