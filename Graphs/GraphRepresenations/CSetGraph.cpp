//
// Created by ilya on 24.02.17.
//


#include "CSetGraph.h"

CSetGraph ::CSetGraph(int count)
{
   arr=new unordered_set <int> [count];
    vertices_count=count;
}

CSetGraph ::~CSetGraph()
{
    delete [] arr;
}

void CSetGraph ::AddEdge(int from, int in)
{
    arr[from].insert(in);
}

void CSetGraph ::GetNextVertices(int vertex, std::vector<int> &vertices) const
{
    vertices .insert(vertices.begin(), arr[vertex].begin(),arr[vertex].end() );
}

void CSetGraph ::GetPrevVertices(int vertex, std::vector<int> &vertices) const
{
    for (int i(0); i<vertices_count; i++ ){
        unordered_set <int > :: iterator a = arr[i].find(vertex);
        if (a != arr[i].end()) {
            vertices.push_back(i);
        }
    }
}