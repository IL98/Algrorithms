#include <iostream>
#include <string>
#include <vector>


using namespace std;


int Ham_str(string s, string p, int begin){
    int  n = p.length();
    int count = 0;
    for (int i(0); i < n; i++){
        if (s[begin + i] != p[i]){
            count++;
        }
    }
    return count;
}

int Hamming(string s, string p){
    int k = s.length() - p.length() + 1;
    int count = 0;
    for (int i = 0; i < k; i++){
        count += Ham_str(s, p, i);
    }
    return count;
}

void comp_q(string s, string p, vector<vector<int > >& cap, int &size, int & size_, vector<int> & vp, vector<int> & vs){
    int len1 = s.length();
    int len2 = p.length();
    int delta = len1 - len2;
    for (int i(0); i < len1; i++){
        if (s[i] == '?'){
            vs.push_back(i);
        }
    }
    for (int j(0); j < len2; j++){
        if (p[j] == '?'){
            vp.push_back(j);
        }
    }
    size = vp.size();
    size_ = vs.size();
    cap.assign(size + size_ + 2, vector<int>(size + size_ + 2, 0));
    for (int i = 0; i < size; i++){
        int x = vp[i] + delta + 1;
        for (int j = vp[i]; j < x; j++){
            if (s[j] == '0'){
                cap[0][2 + size_ + i]++;
            }
            if (s[j] == '1'){
                cap[2 + size_ + i][1]++;
            }
        }
    }
    for (int i = 0; i < size_; i++){
        int x1 = min(vs[i], len2 -1);
        int x = max(0, vs[i] - delta) - 1;
        for (int j = x1; j > x; j--){
            if (p[j] == '0'){
                cap[0][i + 2]++;
            }
            if(p[j] == '1'){
                cap[i + 2][1]++;
            }
        }
    }
    for (int i(0); i < size; i++){
        for (int j(0); j < size_; j++){
            if (vs[j] >= vp[i] && vs[j] <= vp[i]  + delta){
                cap[j + 2][i + 2 + size_] = 1;

                cap[i + 2 + size_][j + 2] = 1;
            }
            if (vs[j] > vp[i] + delta){
                break;
            }
        }
    }
}

bool BFS(vector <vector <int > > & f, vector <vector <int > > cap, vector<int > & d, int n){
    int qh(0), qt(0);
    d.assign(n, -1);
    d[0] = 0;
    vector<int> q(20020);
    q[qt] = 0;
    qt++;
    while (qh < qt){
        int u = q[qh++];
        for (int i = 0; i < n; i++){
            if (f[u][i] < cap[u][i] && d[i] == -1){
                d[i] = d[u]  + 1;
                q[qt++] = i;
            }
        }
    }
    return (d[1] != -1);
}

int DFS(int  u, int min_cap, vector <vector <int > > & f, vector <vector <int > >& cap, vector<int > & d, int n, vector<int > & p){
    if (!min_cap){
        return 0;
    }
    if (u == 1){
        return min_cap;
    }
    for (int & to = p[u]; to < n; to++){
        if (d[to] != d[u] + 1)
            continue;
        int delta = DFS(to, min(min_cap, cap[u][to] - f[u][to]), f, cap, d, n, p);
        if (delta){
            f[u][to] += delta;
            f[to][u] -= delta;
            return delta;
        }
    }
    return 0;
}


int dinic(string & s, string & pus){
    int flow = 0;
    vector<vector<int> > cap;
    int size(0), size_(0);
    vector <int > vs, vp;
    comp_q(s, pus,cap, size, size_, vp, vs);
    vector <vector <int > > f;
    f.assign(size + size_ + 2, vector<int >(size + size_ + 2, 0));
    vector<int > d;
    vector<int > p(size + size_ + 2, -1);
    for (;;){
        if (!BFS(f, cap, d, size + size_ + 2))
            break;
        p.assign(size + size_ + 2, -1);
        while (int pushed = DFS(0, 2000000001, f, cap, d, size + size_ + 2, p)){
            flow += pushed;
        }
    }
    for (int i(2); i < size + size_ + 2; i++){
        if (d[i] != -1){
            if (i < size_ + 2){
                s[vs[i - 2]] = '0';
            }else{
                pus[vp[i - size_ - 2]] = '0';
            };
        }else{
            if (i < size_ + 2){
                s[vs[i - 2]] = '1';
            }else{
                pus[vp[i - size_ - 2]] = '1';
            };

        };

    }
    return Hamming(s, pus);
}




int main() {
    string s, p;
    cin >> s >>p;
    cout <<dinic(s, p) << endl;
    cout << s<< endl;
    cout << p << endl;
    return 0;
}