#include <iostream>
#include <queue>
#include <vector>
#include <forward_list>
#include <algorithm>
#include <set>

using std::forward_list;
using std :: cout;
using std :: priority_queue;
using std :: cin;
using std :: pair;
using std :: vector;
using std :: sort;
using std :: set;

class ClistGraph
{
public:
    vector<forward_list<pair <int, int > > > AdjList;
    int vertices_count;
    int VerticesCount() const;
    ClistGraph(int count);
    void AddEdge(int from, int in, int weight) ;
    void GetNextVertices(int vertex, std::vector<int>& vertices) const;
    void GetPrevVertices(int vertex, std::vector<int>& vertices) const;
};

struct Vertex
{
    int d; // оценка кратчайшего пути
    int pred; //предок
    int number;// номер вершины
    Vertex(int i)
    {
        d = -1;
        pred = -1;
        number = i;
    }
};



int Relax(int u, int v,  int weight, vector <Vertex>& arr)
{
    if (arr[v].d > arr[u].d + weight || arr[v].d == -1)
    {
        arr[v].d = arr[u].d + weight;
        arr[v].pred = u;
        return 1;
    }
    return 0;
}



    bool Compare (Vertex* a, Vertex* b)
    {
        if ((a->d != -1) && (b->d != -1))
           return (a->d > b->d);
        return a->d < b->d;
    }

class Comp
{
public:
    bool operator()(pair<int, int> & a, pair<int, int> & b)
    {
        if (a.second > b.second)
            return true;
        if (a.second == b.second)
            return (a.first > b.first);
        return false;
    }
};

class Comp1
{
public:
    bool operator()(const int& a, const int& b)
    {
        return a > b;
    }
};


int Dijkstra (ClistGraph g, int N, int a, int b)
{
    vector <Vertex> arr;
    for (int i(0); i< N; i++)
    {
        Vertex p(i);
        arr.push_back(p);
    }
    arr[a].d = 0;
    priority_queue< pair<int, int>, vector< pair<int, int> >, Comp > q;
    pair<int, int> m(a, 0);
    q.push(m);
    while (!q.empty())
    {
        pair<int, int> p = q.top();
        q.pop();
        if (p.first == b)
            return  arr[p.first].d;
        if (p.second > arr[p.first].d && arr[p.first].d != -1)
            continue;
        if (arr[p.first].d == -1)
            return -1;
        for (pair <int, int> i : g.AdjList[p.first])
        {
            if (Relax(p.first, i.first, i.second, arr) == 1) {
                pair<int, int> s(i.first, arr[i.first].d);
                q.push(s);
            }
        }
    }
    return -1;
}


int main() {
    int N;
    int M;
    cin >> N >> M;
    ClistGraph g(N);
    for (int i(0); i < M; i++)
    {
        int from, in, weight;
        cin >>from >>in >> weight;
        g.AddEdge(from, in, weight);
        g.AddEdge(in, from, weight);
    }
    int a, b;
    cin >> a >> b;
    cout << Dijkstra(g, N, a, b);
    return 0;
}


ClistGraph ::ClistGraph(int count)
{
    forward_list<pair <int, int > > List;
    for (int i(0); i<count;i++ )
    {
        AdjList.push_back(List);
    }
    vertices_count = count;
}

void ClistGraph ::AddEdge(int from, int in, int weight)
{
    pair <int, int> p(in, weight);
    AdjList[from].push_front(p);
}

int ClistGraph ::VerticesCount() const
{
    return vertices_count;
}

void ClistGraph ::GetNextVertices(int vertex, std::vector<int> &vertices) const {
    for ( auto i : AdjList[vertex]){
        vertices.push_back(i.first);
    }
}


void ClistGraph::GetPrevVertices(int vertex, std::vector<int> &vertices) const
{
    for (int i(0); i < vertices_count; i++){
        for (auto j : AdjList[i])
            if (j.first == vertex) {
                vertices.push_back(i);
                break;
            }
    }
}