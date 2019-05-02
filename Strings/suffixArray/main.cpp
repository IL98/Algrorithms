#include <iostream>
#include <vector>

using std :: vector;
using std :: string;
using std :: max;
using std :: move;
using std :: cin;
using std :: cout;
using std :: endl;


class SuffArray {
private:
    int count_classes_;
    vector <int> substr_array_;// массив для подсчета, который в конце концов преобразуется в суффиксный массив
    vector <int> classes_;// классы эквивалентности
    vector <int> lcp_;//массив lcp
    string text_;//строка с прибавленным символом окончания
public:
    SuffArray(string & Str) {
        text_ = Str + "$";
        substr_array_.assign(Str.length() + 1, -1);
        classes_.assign(Str.length() + 1, -1);
        lcp_.assign(Str.length() + 1, -1);
        count_classes_ = 0;
    }

    /*
     * строит суффиксный массив за време O(nlogn)
     * конечный результат в массиве substr_array_
     */
    void buildSufArray() {
        int length = substr_array_.size();
        vector <int> substr_array_helper;//вспомогательный массив в котором хранятся подстроки степени 2^k упорядоченные
                                         // по вторым половинкам длины 2^(k - 1)
        vector <int> classes_helper;//вспомогательный массив для подсчета классов эквивалентности
        vector <int> count_helper;//массив для сортировки подсчетом
        count_helper.reserve(length);

        buildZeroPhase();

        substr_array_helper.assign(length, -1);
        classes_helper.assign(length, -1);

        for (int degree = 0; (1 << degree) < length && count_classes_ < length; degree++) {
            for (int j = 0; j < length; j++) {
                substr_array_helper[j] = (substr_array_[j] - (1<<degree) );// формирую вспомогательный массив//                                                                                     ;
                if (substr_array_helper[j] < 0) {
                    substr_array_helper[j] += length;
                }
            }

            count_helper.assign(count_classes_, 0); //сортирую подсчетом классы эквивалентности
            for (int j = 0 ; j < length; j++) {
                count_helper[classes_[substr_array_helper[j]]]++;
            }

            for (int j = 1 ; j  < length; j++) {
                count_helper[j] += count_helper[j - 1];
            }

            for (int j = length - 1; j > -1; j-- ) { // заполняю новый substr_array_
                int tmp_value = --count_helper[classes_[substr_array_helper[j] ] ];
                substr_array_[tmp_value] = substr_array_helper[j];
            }

            classes_helper[substr_array_[0]] = 0;
            count_classes_ = 1;
            for (int j = 1; j < length; j++) {//формирую новый класс эквивалентности
                if (classes_[substr_array_[j]] != classes_[substr_array_[j - 1]] ||
                        classes_[(substr_array_[j] + (1 << degree)) % length] != classes_[(substr_array_[j - 1] + (1 << degree)) % length]) {

                   count_classes_++;
                }
                classes_helper[substr_array_[j]] = count_classes_ - 1;
            }
            classes_ = classes_helper;
        }
    }


    /*
     * делает нулевую итерацию в построении суффиксного массива, проходит для подстрок длины 1
     * задает изначальные значения массивам substr_array_ и classes_, в основе лежит сортировка подсчетом
     */
    void buildZeroPhase() {
        vector <int > count;//массив для сортировки подсчетом
        count.assign(27, 0);
        for (int i = 0; i < text_.length(); i++) {//сортирую подсчетом
            if (text_[i] == '$') {
                count[0]++;
            } else {
                count[text_[i] - 'a' + 1]++;
            };
        }

        for (int i = 1 ; i  < 27; i++) {
            count[i] += count[i-1];
        }

        for (int i = 0; i  < text_.length(); i++ ) {//формирую массив substr_array_
            int value = (text_[i] == '$') ? 0 : text_[i] - 'a' + 1;
            count[value]--;
            substr_array_[ count[value]] = i;
        }
        classes_[substr_array_[0]] = 0;
        count_classes_ = 1;
        for (int i = 1 ; i < classes_.size(); i++) { //формирую классы эквивалентности
            if (text_[substr_array_[i] ] != text_[substr_array_[i-1]]) {
                count_classes_++;
            }
            classes_[substr_array_[i]] = count_classes_ - 1;
        }

    }


    /*
     * строю lcp для массива, последний элемент не учитывается и всегда -1
     * результат в массиве lcp_
     */
    void buildLCP() {
        int length = text_.length();
        int prev_lcp = 0;// предыдущее значение lcp
        vector <int> suf_array_reverse;// обратный к суффиксному массиву

        suf_array_reverse.assign(length, -1);
        for (int i = 0; i < length; i++) {
            suf_array_reverse[substr_array_[i] ] = i;
        }

        for (int i  = 0; i  < length; i++ ) {

            if (prev_lcp > 0) {
                prev_lcp--;
            }

            if (suf_array_reverse[i] == length - 1) {
                prev_lcp = 0;
            } else {
                int index = substr_array_[suf_array_reverse[i] + 1];//берем следующий суффикс в суффиксном массиве

                while (i + prev_lcp < length && index + prev_lcp < length
                       && text_[i + prev_lcp] == text_[index + prev_lcp]) {
                    prev_lcp++;
                }

                lcp_[suf_array_reverse[i] ] = prev_lcp;
            }
        }


    }

    /*
     * считает и выводит число различных подстрок в строке
     */
    int diff_substr_search() {
        buildSufArray();
        buildLCP();
        int length = text_.length();

        int result = length - 1 - substr_array_[0];


        for (int i =  1; i < length; i++) {
            result += length - 1- substr_array_[i] - lcp_[i - 1];
        }

        return result;
    }


};


int main()
{
    string S;
    cin >> S;

    SuffArray A =  SuffArray(S);
    cout << A.diff_substr_search()<< endl;
    return 0;
}
