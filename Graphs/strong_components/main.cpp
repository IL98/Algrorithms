#include <iostream>
#include <vector>
#include <list>


using std::list;
using std:: vector;
using std::cin;


struct vertices
{
    int color;
    int pred;
    int d, f; //время начало и время конца обработки
    vertices()
    {
        color = 0;
        pred = -1;
    }
};

class ClistGraph
{
private:

    int vertices_count;
public:
    std ::  vector<list<int > > AdjList;
    ClistGraph(int count);
    void AddEdge(int from, int in) ;
    void GetNextVertices(int vertex, std::vector<int>& vertices) const;
    void GetPrevVertices(int vertex, std::vector<int>& vertices) const;
};

void DFS_Visit(ClistGraph g, vector <vertices>& V, int u, int& time, vector <int >& Finished)
{
    time++;
    V[u].d = time;
    V[u].color = 1;
    for (auto i : g.AdjList[u]){
        if (V[i].color == 0)
        {
            V[i].pred = u;
            DFS_Visit(g, V, i, time, Finished);
        }

    }
    V[u].color = 2;
    time++;
    V[u].f = time;
    Finished.push_back(u);

}


void DFS(ClistGraph g, int n, vector<int >& Finished)
{
    vector <vertices> V(n);
    int time = 0 ;
    for(int i(0); i < n;i++)
    {
        if (V[i].color == 0)
            DFS_Visit(g, V, i, time, Finished);
    }


}




void DFS_Visit_r(ClistGraph g1, int u ,vector<int >& Components, int Comp, vector <vertices>& V)//реверсивный dfs с выбором
{
    Components[u] = Comp;
    V[u].color = 1;
    for (auto i : g1.AdjList[u])
    {
        if (V[i].color == 0)
        {
            V[i].pred = u;
            DFS_Visit_r(g1, i, Components, Comp, V);
        }
    }
    V[u].color = 2;
}


ClistGraph Reverse(ClistGraph g, int n) //обратный граф
{
    ClistGraph g1(n);
    for (int i(0); i < n; i++)
    {
        vector <int > vec;
        g.GetPrevVertices(i, vec);
        for (int j : vec)
        {
            g1.AddEdge(i,j);
        }

    }
    return g1;

}

int SCC(vector<int > arr1, vector<int > arr2, int n)
{
    ClistGraph g(n);
    int m =arr1.size();
    for (int i(0); i < m; i++)
    {
        g.AddEdge(arr1[i], arr2[i]);
    }
    vector<int > Finished;//вектор в который я записываю в порядке времени окончания работы над ней
    DFS(g, n, Finished);
    ClistGraph g_r = Reverse(g, n); //обратный граф
    vector <int > Components(n);
    vector <vertices> V(n);
    int Comp = 0;

    for (vector<int> :: reverse_iterator i = Finished.rbegin();i != Finished.rend(); i++ )
    {
        if (V[*i].color == 0)
        {

            DFS_Visit_r(g_r, *i, Components, Comp, V);
            Comp++;
        }
    }

    if (Comp != 1) {
        vector<std::pair<bool, bool> > St_Sc(Comp);//массив пар, одна координата говорит является ли компонента стоком, а другая, является ли истоком

        int Count_Stock = Comp;
        int Count_Scource = Comp;
        for (int i(0); i < n; i++) {
            if (!St_Sc[Components[i]].first) {//если пока компонента еще является стоком
                vector<int> x;
                g.GetNextVertices(i, x);
                for (int j : x) {
                    if (Components[i] != Components[j]) {
                        St_Sc[Components[i]].first = true;
                        Count_Stock--;
                        break;
                    }
                }
            }
            if (!St_Sc[Components[i]].second) {//если пока компонента еще является истоком
                vector<int> x;
                g.GetPrevVertices(i, x);
                for (int j : x) {
                    if (Components[j] != Components[i]) {
                        St_Sc[Components[i]].second = true;
                        Count_Scource--;
                        break;
                    }
                }
            }

        }


        return std::max(Count_Scource, Count_Stock);
    }
    else return 0;
}


int main() {
    int n, m;
    cin >> n >>m;
    vector <int > arr1(m), arr2(m);
    for (int i(0); i < m; i++)
    {
        int a, b;
        cin >> a>>b;
        arr1[i] = a-1;
        arr2[i] = b-1;
    }

    std :: cout << SCC(arr1, arr2, n)<< " ";
    return 0;
}


ClistGraph ::ClistGraph(int count)
{
    list<int> List;
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
