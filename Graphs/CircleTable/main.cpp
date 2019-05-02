#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>


using std :: vector;
using std :: cin;
using std :: sqrt;
using std :: sort;

double Distance(vector<std::pair<int , int > > arr, int i, int j)
{
    int n = arr.size();
    double x1, x2;
    double y1, y2;
    x1 = double(arr[i].first);
    x2 = double(arr[j].first);
    y1 = double(arr[i].second);
    y2 = double(arr[j].second);
    if (i == 0 || i == n-1)
        return sqrt((x1 - x2) * (x1 - x2));
    if (j == 0 || j == n-1)
        return sqrt((x1 - x2) * (x1 - x2));
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}


struct Edge
{
   int prev, next;//номера вершин
   double distance;
   Edge(int i, int j, vector<std::pair<int, int> > arr)
   {
        prev = i;
        next = j;
        distance = Distance(arr, i, j);
   }
};



class DSU //класс системы независимых множеств, для поддержки компонент связности при добавлении ребер
{

public:
    DSU(int count)
    {
        parent.resize(count, -1);
    }
    vector <int > parent;
    void make_set(int x)
    {
        parent[x] = x;
    }
    void union_sets(int x, int y)
    {
        x = find_set(x);
        y = find_set(y);
        if (x != y)
         parent[y] = x;
    }
    int find_set(int x)
    {
        if (parent[x] == x)
            return x;

        return parent[x] = find_set(parent[x]);
    }
};

bool Compar(Edge a, Edge b)
{
  return (a.distance < b.distance);
}

double Action(vector<std::pair<int , int> > arr, int r)
{
    int n = arr.size();
    vector <Edge> edge;
    for (int i(0); i < n; i++)
        for (int j(i+1); j < n; j++)
        {
            Edge p(i, j, arr);
            edge.push_back(p);
        }
    sort(edge.begin(), edge.end(), Compar);
    DSU f(n);

    for (auto i : edge)
    {
       if (f.parent[i.prev] == -1)
           f.make_set(i.prev);
        if (f.parent[i.next] == -1)
           f.make_set(i.next);
       f.union_sets(i.prev, i.next);
       if (f.parent[0] != -1 && f.parent[n-1] != -1)
         if (f.find_set(0) == f.find_set(n-1))
            return i.distance - 2*r;

    }
    return 0;
}



int main() {
    int a, m;
    cin >> a >> m;
    int r, n;
    cin >> r >> n;
    std :: pair <int , int> p1(a-r, 0);
    std :: pair <int , int> p2(m+r, 0);

    vector<std::pair<int , int> > arr;//храню вектор пар координат

    arr.push_back(p1);//забиваю в вектор левую стенку

    for (int i(0); i < n; i++) {
        int a, b;
        cin >> a >> b;
        if (a > arr[0].first && a < p2.first) {//записываю только те
            std::pair<int , int > p(a, b);
            arr.push_back(p);
        }

    }

    arr.push_back(p2);//забиваю в вектор правую стенку

    printf("%.3lf", Action(arr, r));
    return 0;
}