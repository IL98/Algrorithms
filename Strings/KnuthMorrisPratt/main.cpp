#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using std :: vector;
using std :: string;
using std :: for_each;
using std :: max;


void PrefFunction(const string& sample, vector <int > & pref)
{
    int length = sample.length();

    pref.assign(length, 0);

    pref[0] = 0;

    for (int i = 1 ; i < length; i++)
    {
        if (sample[i] == sample[pref[i - 1]])
            pref[i] = pref[i - 1] + 1;
        else {
            int j = pref[i - 1];
            while (j >0)
            {
                j = pref[j - 1];
                if (sample[i] == sample[j])
                {
                    pref[i] = j + 1;
                    break;
                }

            }
        }
    }

}


int main(int argc, char ** argv)
{
    int n;
    string s;
    std::cin >> s;
    vector <int> p;

    PrefFunction(s, p);

    for (auto i : p)
    {
        std::cout << i <<" ";
    }


    return 0;
}