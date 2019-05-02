#include <iostream>
#include <list>
#include <vector>
#include <queue>
using std :: cin;

using std::list;
using std::vector;
using std::queue;

struct vertices
{
    int color;
    int d;
    int pred;
    vertices()
    {
        color = 0;
        d = -1;
        pred = -1;
    }
};


class ClistGraph
{

public:
    vector<list<int > > AdjList;
    ClistGraph(int c){
        list<int> List;
        for (int i(0); i<c;i++ )
        {
            AdjList.push_back(List);
        }
    };

    void AddEdge(const int from,const int in)
    {
        AdjList[from].push_front(in);
        AdjList[in].push_front(from);
    }
};



void BFS(ClistGraph &g, int s, vector<vertices> V, int& Min)
{
    V[s].color = 1;
    V[s].d = 0;
    queue<int > Queue;
    Queue.push(s);
    while (!Queue.empty())
    {
        int u = Queue.front();
        Queue.pop();
        for (list <int> :: iterator i = g.AdjList[u].begin(); i != g.AdjList[u].end(); i++)
        {
            if ((V[*i].color == 1) && (*i != V[u].pred))
            {
                int x =V[*i].d + V[u].d + 1;
                if (Min == -1)
                    Min = x;
                else
                    Min = std :: min (Min,x);
                if (Min == 3)
                    return;

            }
            if (V[*i].color == 0)
            {
                V[*i].color = 1;
                V[*i].d = V[u].d + 1;
                V[*i].pred = u;
                Queue.push(*i);
            }


        }
        V[u].color = 2;
    }
}

int B_F_S(vector<int > arr1, vector<int > arr2, int n)
{
    int m = arr1.size();
    ClistGraph g(n);
    int Min = -1;
    vector <vertices> V(n);
    for (int i(0); i<m; i++)
    {
        g.AddEdge(arr1[i], arr2[i]);
    }
    for (int i(0); i < n; i++)
    {
            BFS(g, i, V, Min);
        if (Min == 3)
            return 3;
    }
    return Min;
}

int main()
{
    int n,m;
    cin >> n >> m;
    vector <int> arr1(m);
    vector <int> arr2(m);
    for (int i(0); i < m ; i++)
    {
        cin >> arr1[i] >> arr2 [i];
    }

    std :: cout << B_F_S(arr1, arr2, n);

    return 0;
}