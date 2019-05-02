#include <iostream>
#include <vector>
#include <sstream>

using std :: vector;
using std :: string;
using std ::cout;
using std :: cin;
using std :: min;
using std :: stringstream;


/*
 * вычисление z функции
 */
void ZFunction(const string& sample, vector <int > & z_func)
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

        while ( sample[z_func[index]] == sample[index + z_func[index]] && (z_func[index] + index < length))
            z_func[index]++;

        if (z_func[index] + index > right_border + 1)
        {
            right_border = z_func[index] + index - 1;
            left_border = index;
        }

    }

}

/*
 * вычисление префикс функции
 */
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


/*
 * по z функции строит префикс функцию
 */
void ZToPref(const vector<int >& z, vector <int >& pref)
{
    int length = z.size();

    pref.assign(length, 0);

    for (int i = 1; i < length; i++)
    {
        if (z[i])                                 //если ненулевое значение то просто добавляем элементы pref[i+j] с конца от (i+ z[i] - 1) до i
            for (int j = z[i] - 1; j >= 0 ; j--)
            {
                if (pref[i + j] != 0)           //если значение префикс функции уже ненулевое, значит инициализировано уже было до этого момента, и очевидно большим числом
                    break;
                pref[i + j] = j + 1;
            }
    }
}


/*
 * по префикс функции строит z функцию
 */
void PrefToZ(vector<int >& z, const vector <int >& pref)
{
    int length = pref.size();

    z.assign(length, 0);

    for (int i = 1; i < length; i++) // проходим по prefix функции и формируем прототип z-функции
    {
        if (pref[i])
            z[i + 1 - pref[i]] = pref[i];
    }

    z[0] = length;
    int i = 1;
    while (i < length)//проходим по z и доформировываем z-функцию до окончательного состояния
    {
        int temp_var = i;//временная переменная для увеличения i
        if (z[i] != 0)
        {
            for (int j = 1; j < z[j]; j++)// здесь мы рассматриваем случаи как еще мы можем увеличить значение z[i+j]
            {
                if (z[j] < z[i + j])
                    break;
                z[j  + i] = min(z[i] - j, z[j]);
                temp_var++;
            }
        }
        i = temp_var + 1;
    }


}


/*
 * по префикс функции строит строку
 */
void PrefToStr(const vector <int > & pref, string& sample)
{
    int length = pref.size();

    vector<int> alphabet(26, -1);//массив, в котором в i-ом элементе хранится номер элемента в строке, который не может быть равным символу i + 'a'
    alphabet[0] = 0;//"a" никогда не берем в случае pref[i] = 0, так как это начальная буква

    sample.insert(sample.end(), 'a');


    for (int i = 1; i < length; i++)
    {
        if (!pref[i])//если значение префикс функции нулевое, то мы не можем взять те буквы, которые при подстановке давали какие лиюбо общие суффиксы
        {
            int j = pref[i - 1];

            while (j)//в цикле мы рассматриваем все возможные общие суффиксы и определяем буквы, которые мы не можем поставить
            {
                alphabet[sample[j] - 97] = i;
                j = pref[j - 1];
            }


            for (j = 1; alphabet[j] == i && j < 26; j++);//ищем миниммальную букву которой не встречалось

            sample.insert(sample.end(), j + 97);
        } else {
            sample.insert(sample.end(), sample[pref[i] - 1]);
        }
    }

}



/*
 * по z функции строит строку
 */
void ZToStr(const vector <int > & z, string& sample)
{
    int length = z.size();

    int prefix_counter = 0 ;//количество символов, которое надо напечатать из -за значения z[i], которое встречалось ранее

    vector <int > vector_counter ;//здесь будут лежать номера элементов, соответвующие символы в строке которых не могут быть под определенным номером

    int pref_index = 0;//номер символа из префикса, который мы собираемся напечатать

    vector<int> alphabet(26, -1);//массив, в котором в i-ом элементе хранится номер элемента в строке, который не может быть равным символу i + 'a'

    alphabet[0] = 0;//"a" никогда не берем в случае pref[i] = 0, так как это начальная буква

    sample.insert(sample.end(), 'a');

    for (int i = 1; i < length; i++)
    {

        if (z[i] == 0 && prefix_counter == 0)// в этом случае смотрим на массив номеров элементов строки, которые мы не можем взять и выделяем минимальный из возможных
        {
            int index;                              //(pref_index + prefix_counter) - это есть z[j], засчет которого мы начисляли буквы, но сейчас он закончился
                                                        // чтобы мы не взяли следующий элемент

            for (int k : vector_counter)
            {
                alphabet[sample[k] - 97] = i;
            }

            vector_counter.clear();
            for( index = 1; index < 26 && alphabet[index] == i; index++);
            sample.insert(sample.end(), index + 97);

        }



        if (z[i] == prefix_counter && z[i + prefix_counter] == 0 && i + prefix_counter < length)//если у элемента значение равно оставшейся длине и после оставшейся длины будет
        {                                                                                 // значение функции равно 0, то мы не можем напечатать на том места элемент с номером z[i]
            vector_counter.push_back(z[i]);
        }



        if (z[i] > prefix_counter)//если мы нашли значение префикс функции на некотоором символе больше, чем оставшаяся длинна, то теперь печатаем ее
        {
            pref_index = 0;
            prefix_counter = z[i];

            if (z[i + z[i]] == 0 && (i + z[i] < length))//если спустя оставшуюся длинну будет элемент, значение которого равно 0, то элемент, стоящий на месте z[i] мы взять не можем
            {
                vector_counter.push_back(z[i]);//заносим его в массив
            }
        }



        if (prefix_counter > 0)//печатаем символ если длинна не нулевая
        {
            prefix_counter--;
            sample.insert( sample.end(), sample[pref_index++] );
        }

    }


}


int main(int argc, char ** argv)
{
    vector <int> pref;
    int var;          //вспомогательная переменная, чтобы считать ввод
    string helper;

    getline(cin, helper);

    stringstream ss(helper);

    while (ss >> var)
    {

        pref.push_back(var);
    }


    string sample;

    PrefToStr(pref, sample);

    cout << sample;

    return 0;
}