#include <fstream>
#include <vector>

using std :: vector;
using std :: ifstream;
using std :: ofstream;

class CMatrixGraph
{
public:
    vector<vector<int> > Matrix;
    int vertices_count;
    int VerticesCount() const;
    CMatrixGraph(int count);
    void AddEdge(int from, int in, int weight) ;
    void GetNextVertices(int vertex, vector<int>& vertices) const ;
    void GetPrevVertices(int vertex, vector<int>& vertices) const;
};

void Floyd_Warshall(vector <vector <int > >& D, int N)
{
    for (int k(0); k < N; k++)
        for (int i(0); i< N; i++)
            for (int j(0); j < N; j++)
                if (i != j)
                   D[i][j] = std :: min (D[i][j], D[i][k] + D[k][j]);

}

int main() {
    int N;
    ifstream fin("floyd.in");
    ofstream fout("floyd.out");
    fin >> N;
    vector <vector <int > > D;
    D.assign(N, vector <int> (N, 0));
    for (int i(0); i < N; i++)
        for (int j(0); j <N; j++)
        {
            int weight;
            fin >> weight;
            D[i][j] = weight;
        }
    Floyd_Warshall(D, N);
    for (int i(0); i < N; i++) {
        for (int j(0); j < N; j++) {
            fout << D[i][j];
            if (j != N-1)
                fout << " ";
        }
        if (i != N -1)
          fout << "\n";
    }
    fout.close();
    fin.close();
    return 0;
}

CMatrixGraph ::CMatrixGraph(int count)
{
    vertices_count=count;
    Matrix.assign(count, vector <int> (count, 0));
}

void CMatrixGraph ::AddEdge(int from, int in, int weight)
{
    Matrix[from][in] = weight;
}
void CMatrixGraph ::GetNextVertices(int vertex, vector<int> &vertices) const
{
    for (int i(0); i <vertices_count; i++){
        if (Matrix[vertex][i])
            vertices.push_back(i);
    }
}

int CMatrixGraph ::VerticesCount() const
{
    return vertices_count;
}

void CMatrixGraph ::GetPrevVertices(int vertex, vector<int> &vertices) const
{
    for (int i(0); i <vertices_count; i++){
        if (Matrix[i][vertex])
            vertices.push_back(i);
    }
}
