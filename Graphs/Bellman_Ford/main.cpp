#include <iostream>
#include <forward_list>
#include <vector>


using std :: vector;
using std ::  cout;
using std ::  cin;
using std::forward_list;
using std :: pair;

class ClistGraph
{
public:
    vector<forward_list<pair <int, double > > > AdjList;
    int vertices_count;
    int VerticesCount() const;
    ClistGraph(int count);
    void AddEdge(int from, int in, double weight) ;
    void GetNextVertices(int vertex, std::vector<int>& vertices) const;
    void GetPrevVertices(int vertex, std::vector<int>& vertices) const;
};

struct Vertex
{
    double d;// оценка кратчайшего пути
    int pred; //предок
    int number;// номер вершины
    Vertex(int i)
    {
        d = -1;
        pred = -1;
        number = i;
    }
};


void Relax(int u, int v,  double weight, vector <Vertex>& arr)
{
    if (arr[v].d < arr[u].d * weight)
    {
        arr[v].d = arr[u].d * weight;
        arr[v].pred = u;
    }
}


int Bell_Ford(ClistGraph g, int N)
{
    for (int i(0); i < N; i++)
    {
        vector <Vertex> arr;
        for (int k(0); k< N; k++)
        {
            Vertex p(k);
            arr.push_back(p);
        }
        arr[i].d = 1;
        for (int k(0); k < N - 1; k++)
        {
            for(int m(0); m < N; m++)
            {
                for (pair <int, double > j : g.AdjList[m])
                {
                    Relax(m, j.first, j.second, arr);
                }

            }

        }
        if (arr[i].d > 1)
            return 1;
        arr.clear();
    }
    return 0;
}


int main() {
    int N;
    cin >> N;
    ClistGraph g(N);
    for (int i(0); i < N; i++)
        for (int j(0); j < N; j++)
        {
            if (j != i)
            {
                double weight;
                cin >> weight;
                if (weight != -1)
                   g.AddEdge(i, j, weight);
            } else {
                g.AddEdge(i, j, 1.0);
            }

        }

     int a = Bell_Ford(g, N);
     if (a == 1)
         cout << "YES";
      else cout << "NO";
    return 0;
}


ClistGraph ::ClistGraph(int count)
{
    forward_list<pair <int, double > > List;
    for (int i(0); i<count;i++ )
    {
        AdjList.push_back(List);
    }
    vertices_count = count;
}

void ClistGraph ::AddEdge(int from, int in, double weight)
{
    pair <int, double> p(in, weight);
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