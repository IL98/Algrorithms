#include <fstream>
#include <forward_list>
#include <vector>
#include <set>

using namespace std;

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


int Prim(ClistGraph g){
    int n = g.VerticesCount();
    int s = 0;
    vector<int> key(n, 2000000);
    vector<int> used(n, 0);
    key[0] = 0;
    set < pair <int, int > > q;
    q.insert(make_pair(0,0));
    used[0] = 1;
    for (int j = 0; j < n; j++){
        s += q.begin()->first;
        int vertex = q.begin()->second;
        q.erase(q.begin());
        used[vertex] = 1;
        for (auto i : g.AdjList[vertex]){
            int t = i.first;
            int w = i.second;
            if (w < key[t] && !used[t]){
                q.erase(make_pair(key[t], t));
                key[t] = w;
                q.insert(make_pair(key[t], t));
                used[t];
            }
        }
    }
    return s;
}



int main(){
    int n, m ;
    ifstream fin("kruskal.in");
    ofstream fout("kruskal.out");
    fin >> n >> m;
    ClistGraph g(n);
    for (int i(0); i < m; i++){
        int a, b, weight;
        fin >> a >> b >> weight;
        g.AddEdge(a - 1, b - 1, weight);
    }
    fout << Prim(g);
    fout.close();
    fin.close();
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
    pair<int , int> p1(from, weight);
    AdjList[in].push_front(p1);
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