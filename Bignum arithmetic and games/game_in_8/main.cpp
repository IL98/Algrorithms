#include <string>
#include <queue>
#include <fstream>


using namespace std;

class Hash{
    struct Node{
        string str;
        bool deleted;
        string path;
        Node(){
            str="";
            path = "";
            deleted=false;
        }
    };

    int n;
    int Size;
    int H1(string s){
        int h(0);
        for (unsigned int i(0); i<s.length();i++){
            h=(h*7+s[i]) % Size;
        }
        return h;
    }
    int H2(string s){
        int h(0);
        for (int i = s.length()-1; i>-1; i--){
            h=(2*(h+s[i])+1)  % Size ;
        }
        return h;
    }


    double K(){
        return double(n)/double(Size);
    }


public:
    Node* mas;
    Hash(){
        mas=new Node[180000];
        Size=180000;
        n=0;
    }

    ~Hash(){
        delete [] mas;
    }
    int Find (string s){
        int x=H1(s);
        int y=H2(s);
        for (int i(0); i < Size; i++){
            if (mas[(x+i*y) % Size].str=="")
                return -1;
            if (mas[(x+i*y) % Size].str==s && mas[(x+i*y) % Size].deleted)
                return -1;
            if (mas[(x+i*y) % Size].str==s && !mas[(x+i*y) % Size].deleted)
                return (x+i*y) % Size;
        }
        return -1;
    }

    bool Add(string s, string p){
        if (Find(s) != -1) return false;
        //  if ( K()>= 0.75) ReHash();
        int x=H1(s);
        int y=H2(s);
        for (int i(0); i<Size; i++){
            if (mas[(x+i*y) % Size].str=="" || (mas[(x+i*y) % Size].deleted)){
                mas[(x+i*y) % Size].str=s;
                mas[(x+i*y) % Size].deleted = false;
                mas[(x+i*y) % Size].path = p;
                n++;
                return true;
            }
        }
        return true;
    }

    void ReHash(){
        Size*=2;
        Node* mas1=new Node[Size];
        n=0;
        Node* mas2=new Node[Size/2];
        for (int i(0); i<Size/2; i++){
            if (mas[i].str!=""){
                mas2[i].str=mas[i].str;
                mas2[i].deleted=mas[i].deleted;
                mas2[i].path = mas[i].path;
            }
        }
        delete [] mas;
        mas=mas1;

        for (int i(0); i< Size/2; i++){
            if (mas2[i].str!="" && (!mas2[i].deleted))
                Add(mas2[i].str, mas2[i].path);
        }
        delete [] mas2;
    }


    bool Remove (string s){
        if (!Find(s))  return false;
        int x=H1(s);
        int y=H2(s);
        for (int i(0);i<Size; i++){
            if (mas[(x+i*y) % Size].str==s)
                if (mas[(x+i*y) % Size].deleted==false){
                    mas[(x+i*y) % Size].deleted=true;
                    n--;
                    return true;
                }
        }
        return true;
    }

};

void up(string s, string &s1)
{
    s1 = s;
    int n = s1.find("0");
    int def = n / 3;
    int mod = n % 3;
    int i = (def - 1)  * 3 + mod;
    s1[n] = s[i];
    s1[i] = '0';
}

void down(string s, string &s1)
{
    s1 = s;
    int n =s1.find("0");
    int def = n / 3;
    int mod = n % 3;
    int i = (def + 1) * 3 + mod;
    s1[n] = s[i];
    s1[i] = '0';
}

void left(string s, string &s1)
{
    s1 = s;
    int n =s1.find("0");
    s1[n] = s1[n - 1];
    s1[n -1] = '0';
}

void right(string s, string &s1)
{
    s1 = s;
    int n =s1.find("0");
    s1[n] = s1[n + 1];
    s1[n + 1] = '0';
}

int proverka(string s)
{
    int n = 0;
    for (int i = 1; i < 9; i++)
    {
        if (s[i] != '0')
            for (int j = 0; j < i; j++)
                if (s[j] > s[i])
                    n++;
    }
    return n;
}

int find_right_pos(string s, string &p1)
{
    Hash T;
    queue <int> Q;
    string p = "";
    T.Add(s, p);
    Q.push(T.Find(s));
    while (!Q.empty())
    {
        int k1 = Q.front();
        Q.pop();
        string s1 = T.mas[k1].str;
        int n = s1.find("0");
        int def = n / 3;
        int mod = n % 3;
        if (def != 0)
        {
            string s2;
            up(s1, s2);
            if (s2 == "123456780")
            {
                p1 = T.mas[k1].path;
                p1 += "U";
                return 1;
            }
            int k = T.Find(s2);
            if (k == -1)
            {

                string p0 = T.mas[k1].path + "U";
                T.Add(s2, p0);
                Q.push(T.Find(s2));

            }
        }
        if (def != 2)
        {
            string s3;
            down(s1, s3);
            if (s3 == "123456780")
            {
                p1 = T.mas[k1].path;
                p1 += "D";
                return 1;
            }
            int k = T.Find(s3);
            if (k == -1)
            {
                string p00 = T.mas[k1].path + "D";
                T.Add(s3, p00);
                Q.push(T.Find(s3));
            }
        }
        if (mod != 0)
        {
            string s4;
            left(s1, s4);
            if (s4 == "123456780")
            {
                p1 = T.mas[k1].path;
                p1 += "L";
                return 1;
            }
            int k = T.Find(s4);
            if (k == -1)
            {
                string p000 = T.mas[k1].path + "L";
                T.Add(s4, p000);
                Q.push(T.Find(s4));
            }
        }
        if (mod != 2)
        {
            string s5;
            right(s1, s5);
            if (s5 == "123456780")
            {
                p1 = T.mas[k1].path;
                p1 += "R";
                return 1;
            }
            int k = T.Find(s5);
            if (k == -1)
            {
                string p0000 = T.mas[k1].path + "R";
                T.Add(s5, p0000);
                Q.push(T.Find(s5));
            }
        }
    }
    return -1;
}


int main()
{
    ifstream fin("puzzle.in");
    ofstream fout("puzzle.out");
    string s;
    int i(0);
    while (s.length() != 9)
    {
        char n;
        fin >> n;
        if (n != ' ')
            s += n;
        i++;
    }
    string p;
    if (s == "123456780")
        fout << 0;
    else
    if (proverka(s) & 1)
        fout << -1;
    else{
        find_right_pos(s, p);
        fout << p.length() << endl;
        fout << p;
    }
    fout.close();
    fin.close();
    return 0;
}

