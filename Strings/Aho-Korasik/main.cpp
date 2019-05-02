#include <iostream>
#include <vector>

using std::cout;
using std::cin;
using std::vector;
using std::string;
using std::ios_base;


typedef std::vector<struct TrieVertex> TVertexs;
typedef std::vector<std::string> TPatterns;

/*
 * вершина бора
 */
struct TrieVertex {
    vector<int>  alphabet;
    bool leaf;
    int parent;
    char symbol;//символ по которому можно перейти от parent в текущую вершину
    vector<int> pattern_number;

    vector<int> turn;
    int suffix_link;
    int fast_suffix_link;//хорошая суффиксная ссылка
    TrieVertex() {
        alphabet.assign(26, -1);
        turn.assign(26, -1);
        leaf = false;
        suffix_link = -1;
        parent = 0;
        symbol = -1;
        fast_suffix_link = -1;
    }

};


/*
 * процедура добавления строки в бор
 */
void AddPattern(const string & s,TVertexs& Trie, TPatterns& patterns) {
    int index = 0;//root of the Trie

    for (int i = 0; i < s.length(); i++) {
        char symbol = s[i] - 'a';//English alphabet from 0 to 25

        if (Trie[index].alphabet[symbol] == -1) {//doesn't exist edge with this symbolol

            Trie.emplace_back();
            Trie[Trie.size() - 1].parent = index;
            Trie[index].alphabet[symbol] = Trie.size() - 1;
            index = Trie.size() - 1;

            Trie[Trie.size() - 1].symbol = symbol;

        } else {
            index = Trie[index].alphabet[symbol];
        }
    }

    Trie[index].leaf = true;
    patterns.push_back(s);
    Trie[index].pattern_number.push_back(patterns.size() - 1);
}


int GetTurn(TVertexs& Trie, int vertex, char symbol);

/*
 * получение суффиксной ссылки
 */
int GetLink(TVertexs& Trie, int vertex) {
    if (Trie[vertex].suffix_link == -1) {
        if (vertex == 0 || Trie[vertex].parent == 0) {
            Trie[vertex].suffix_link = 0;
        } else {
            Trie[vertex].suffix_link = GetTurn(Trie, GetLink(Trie, Trie[vertex].parent), Trie[vertex].symbol);
        }
    }
    return Trie[vertex].suffix_link;
}

/*
 * вычисление функции перехода
 */
int GetTurn(TVertexs& Trie, int vertex, char symbol) {
    if (Trie[vertex].turn[symbol] == - 1) {
        if (Trie[vertex].alphabet[symbol] != -1) {
            Trie[vertex].turn[symbol] = Trie[vertex].alphabet[symbol];
        }else {
            if (vertex == 0)
                Trie[vertex].turn[symbol] = 0;
            else
                Trie[vertex].turn[symbol] = GetTurn(Trie, GetLink(Trie, vertex), symbol);
        }

    }
    return Trie[vertex].turn[symbol];
}

/*
 * получение хорошей суффиксной ссылки
 */
int GetFLink(TVertexs& Trie, int vertex) {
    if (Trie[vertex].fast_suffix_link == -1) {
        int real_link = GetLink(Trie, vertex);//его настоящая суффиксная ссылка

        if (real_link == 0)  //либо это корень, либо сын корня
            Trie[vertex].fast_suffix_link = 0;
        else {
            if (Trie[real_link].leaf == true) {
                Trie[vertex].fast_suffix_link = real_link;
            } else {
                Trie[vertex].fast_suffix_link = GetFLink(Trie, real_link);
            }
        }
    }
    return  Trie[vertex].fast_suffix_link;
}


/*
 * находит все вхождения шаблонов данному префиксу строки
 */
void ProcessPref(TPatterns& patterns, TVertexs& Trie, vector<int>& total, const vector<int>& pat_pos, int vertex, const int index){

    for (int u = vertex; u !=0 ;u = GetFLink(Trie, u)) {
        if (Trie[u].leaf == true) {
            //cout << index - patterns[Trie[vertex].pattern_number].length() + 1 << " " << patterns[Trie[vertex].pattern_number] << endl;

            for (auto i : Trie[u].pattern_number) {
                int var = index - patterns[i].length() + 1;//номер индекса в тексте с которого начинается обнаруженная подстрока шаблона
                if (var - pat_pos[i] >= 0 ) {
                    total[ var - pat_pos[i]]++;//инкрементируем значение элемента total
                }
            }


        }
    }
}


/*
 *  создает бор из подстрок без масок шаблона pattern_mask и формирует массив pat_pos
 */
void BuildTrie(TPatterns& patterns, const string& pattern_mask, TVertexs& Trie, vector<int>& pat_pos) {
    bool mask_in = false;
    int left_border = 0;

    Trie.emplace_back();

    for (int i = 0; i  < pattern_mask.length(); i++) {
        if (pattern_mask[i] == '?') {
            if (mask_in == false) {
                mask_in = true;
                if (i > left_border){
                    AddPattern(pattern_mask.substr(left_border, i -  left_border), Trie, patterns);
                    pat_pos.push_back(left_border);
                }
            }
        } else {
            if (mask_in == true) {
                mask_in = false;
                left_border = i;
            }
        }
    }
    if (mask_in == false) {
        AddPattern(pattern_mask.substr(left_border, pattern_mask.length()  -  left_border), Trie, patterns) ;
        pat_pos.push_back(left_border);
    }
}



/*
 * формирует массив total,
 */
void ProcessText (TPatterns& patterns, string& pattern_mask, TVertexs& Trie, vector<int>& total, vector<int>& pat_pos, const string& text) {

    BuildTrie(patterns, pattern_mask, Trie, pat_pos);
    total.assign(text.length(), 0);
    int vertex = 0;
    for (int i = 0; i < text.length(); i++) {
        char c = text[i] - 'a';
        vertex = GetTurn(Trie, vertex, c);
        ProcessPref(patterns, Trie, total, pat_pos, vertex, i);
    }
}





/*
 * решает задачу поиск паттерна подстроки в строке
 */
int main(int argc, char ** argv) {

    ios_base::sync_with_stdio( 0);
    cin.tie(NULL);

    string pattern_mask;
    string text;
    TVertexs Trie;
    vector<string> patterns;
    vector<int> total;//массив, где на i-ом месте указано сколько безмасковых подстрок из шаблона в начинаются с i-ой позиции в тексте

    vector<int> pat_pos;//массив для указания позиции в шаблоне каждой безмасковой подстроки

    cin >> pattern_mask;
    cin >> text;

    if (text.length() < pattern_mask.length())
        return 0;

    ProcessText(patterns, pattern_mask, Trie, total, pat_pos, text);

    int var = (int)total.size() - (int)pattern_mask.length() + 1;
    for (int i = 0 ; i < var; ++i)
        if (total[i] == patterns.size())
            cout << i << " ";


    return 0;
}
