#include <iostream>
#include <vector>

using std::vector;
using std::string;
using std::cout;
using std::min;
using std::cin;

/*
 * построение z-функции для строки sample
 * результат заношу в вектор z_func
 */
void ZFunction(const string& sample, vector<int>& z_func)
{
    int length = sample.length();

    z_func.assign(length, 0);

    z_func[0] = length;

    int left_border = 0;

    int right_border = 0;

    for (int index = 1; index < length; index++)
    {
        if (index <= right_border)
        {
            z_func[index] = min (z_func[index - left_border], right_border - index + 1);
        }

        while ( sample[z_func[index]] == sample[index + z_func[index]]
                                        && (z_func[index] + index < length))
        {
            z_func[index]++;
        }

        if (z_func[index] + index > right_border + 1)
        {
            right_border = z_func[index] + index - 1;
            left_border = index;
        }

    }

}

/*
 * поиск шаблона pattern  в тексте text
 * рузальтат заношу в массив result
 */
void Substr(const string& pattern, const string& text, vector<int>& result)
{
    int pat_length = pattern.length();
    int text_length = text.length();

    vector<int> z_func;
    ZFunction(pattern, z_func); //z функция для шаблона


    int left_border = -1;

    int right_border = -1;

    for (int index = 0; index  < text_length; index++)
    {
        int counter = 0; //для нахождения значения z функции в позиции index в тексте


        if (index <= right_border)
        {
            counter = min(right_border - index + 1, z_func[index - left_border]);
        }

        while (pattern[counter] == text[counter + index] && counter < pat_length && counter + index < text_length)
        {
            counter++;
        }


        if (counter == pat_length)
        {
            result.push_back(index);
        }


        if (right_border < index + counter - 1)
        {
            right_border = index + counter - 1;
            left_border = index;
        }

    }



}

int main(int argc, char ** argv)
{
    string pattern;
    string text;
    cin >> pattern;
    cin >> text;

    vector<int> result;
    Substr(pattern, text, result);

    for (auto i : result)
    {
        cout << i << " ";
    }
    return 0;
}