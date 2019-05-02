#include <iostream>
#include <vector>


using std::vector;
using std::cin;


class CMatrixGraph
{
private:
    int vertices_count;

public:
    vector<vector<int>> Matrix;
    CMatrixGraph(int count);
    void AddEdge(int from, int in)  ;
    void GetNextVertices(int vertex, vector<int>& vertices) const ;
    void GetPrevVertices(int vertex, vector<int>& vertices) const;
};



bool Search_Stock(vector< vector <int>> array, int n)
{
    CMatrixGraph g(n);
    for (int i(0); i < n; i++)
        for (int j(0); j < n; j++)
            if (array[i][j] == 1)
                g.AddEdge(i, j);
    int i = 0;
    int j = 0;
    while (i < n && j < n)
    {
         if ( g.Matrix[i][j] == 1 || (i == j))
             i++;
         else if (g.Matrix[i][j] == 0)
             j++;
    }
    if (i < j)
        return false;
    else {
        for (int i(0); i < n; i++)
            if (g.Matrix[j][i] == 1)
                return false;
    }
    return true;
}




int main()
{
    int n;
    cin >> n;
    vector <vector <int > > array (n, vector <int>(n));
    for (int i(0); i < n; i++)
        for (int j(0); j < n; j++)
            cin >> array[i][j];
    if (Search_Stock(array, n))
        std :: cout << "YES";
    else
        std :: cout << "NO";

    return 0;
}





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