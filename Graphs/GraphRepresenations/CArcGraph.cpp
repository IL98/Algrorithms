//
// Created by ilya on 24.02.17.
//

#include "CArcGraph.h"

CArcGraph ::CArcGraph(int count)
{
    vertices_count =count;
}

void CArcGraph ::AddEdge(int from, int in)
{
    std :: pair <int,int> p(from, in);
    arr.insert(p);

}


void CArcGraph ::GetNextVertices(int vertex, std::vector<int> &vertices) const
{
    std :: pair< multimap <int, int > :: const_iterator, multimap <int, int > :: const_iterator > r1;
    r1=arr.equal_range(vertex);
    auto r2=r1.first;
    for (r2; r2 != r1.second; r2++){
        vertices.push_back(r2->second);
    }
}

void CArcGraph ::GetPrevVertices(int vertex, std::vector<int> &vertices) const
{
    for (auto i : arr){
        if (i.second ==vertex)
            vertices.push_back(i.first);
    }
}