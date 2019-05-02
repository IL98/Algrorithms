#include <iostream>
#include <vector>
#include <cmath>

using std::vector;
using std::cin;
using std::cout;
using std::endl;
using std::min;
using std::max;
using std::pair;
using std::abs;
using std::move;

typedef pair<double, double> PointVec;

/*
 * сумма векторов
 */
PointVec SumVec(const  PointVec&  Sum1, const PointVec&  Sum2) {
    PointVec sum;
    sum.first = Sum1.first + Sum2.first;
    sum.second = Sum1.second + Sum2.second;
    return sum;
}


bool compare(PointVec vec1, PointVec vec2) {
    if (vec1.second < vec2.second) {
        return true;
    }
    if (vec1.second == vec2.second &&
            vec1.first < vec2.first) {
        return true;
    }

    return false;
}

/*
 * выводит номер самой левой нижней точки во множетсве вершин выпуклового многоугольника
 */
int getMin(const vector <PointVec>& sum) {
    int min = 0;
    for (int i = 1; i <  sum.size(); i++) {
        if (compare(sum[i], sum[min])) {
            min = i;
        }
    }
    return min;
}


/*
 *  возвращает векторное произведение (point1_1, point1_2) и (point2_1, point2_2)
 */
double VecProduct(const PointVec& point1_1, const PointVec& point1_2,
                  const PointVec& point2_1, const PointVec& point2_2) {

    return (point1_2.first - point1_1.first) * (point2_2.second - point2_1.second) -
            (point1_2.second - point1_1.second) * (point2_2.first - point2_1.first);
}


/*
 * считает сумму минковского многоугольников Sum1 и Sum2
 * искомую сумму отправит в Result
 */
vector <PointVec> SumMinkowskiyWithDiff(const vector <PointVec>& Sum1, const vector <PointVec>& Sum2) {
    vector <PointVec> sum_minkowski;

    int min_by_sum1 = getMin(Sum1);//номер самой крайней точки из Sum1
    int min_by_sum2 = getMin(Sum2);//номер самой крайней точки из Sum2

    int i = min_by_sum1;
    int j = min_by_sum2;
    int a1 = min_by_sum1 - Sum1.size();//нижняя граница, на которую может быть проитерирован i
    int a2 = min_by_sum2 - Sum2.size();//нижняя граница, на которую может быть проитерирован j

    sum_minkowski.push_back(SumVec(Sum1[(i + Sum1.size()) % Sum1.size()], Sum2[(j + Sum2.size()) % Sum2.size()]));//
                                                                                //добавляем сумму крайних точек
    while (i  > a1 && j > a2) {
        //здесь считаем векторное произведение векторов (i, i-1) и (j, j - 1)  для sum1 и sum2 соответственно
        //берем соответствующие модули от номеров i, i-1, j, j - 1, чтобы итерироваться по точкам многоугольников Sum1 и Sum2
        double VecProduct_ = VecProduct(Sum1[(i + Sum1.size()) % Sum1.size()], Sum1[(i - 1 + Sum1.size()) % Sum1.size()],
                                Sum2[(j + Sum2.size()) % Sum2.size()], Sum2[(j - 1 + Sum2.size()) % Sum2.size()]);
        if (VecProduct_ < 0) {
            j--;
        }else {
            i--;
        }
        sum_minkowski.push_back(SumVec(Sum1[(i + Sum1.size()) % Sum1.size()], Sum2[(j + Sum2.size()) % Sum2.size()]));
    }
    /*
     * здесь добавляются оставшиеся точки, когда обхода одного из многоугольника уже завершился
     */
    while (i > a1) {
        i--;
        sum_minkowski.push_back(SumVec(Sum1[(i + Sum1.size()) % Sum1.size()], Sum2[(j + Sum2.size()) % Sum2.size()]));
    }
    while (j > a2) {
        j--;
        sum_minkowski.push_back(SumVec(Sum1[(i + Sum1.size()) % Sum1.size()], Sum2[(j + Sum2.size()) % Sum2.size()]));
    }
    return move(sum_minkowski);


}


/*
 * все вершины многоугольника умножает на -1
 */
void ReverseConvex(vector <PointVec>& convex) {
    for (int i = 0; i < convex.size(); i++) {
        convex[i].first *= -1;
        convex[i].second *= -1;
    }

}

//выводит основной ответ
bool Action(const vector <PointVec>& convex1, vector <PointVec>& convex2) {
    ReverseConvex(convex2);    //умножили все его вершины на -1
    vector <PointVec> result = SumMinkowskiyWithDiff(convex1, convex2);  //в result заносим сумму минковского - вектор точек в порядке обхода
                                                                        // против часовой стрелки
    PointVec origin(0., 0.);
    bool exist = true;        //true, если начало координат может находится внутри многоугольника по мере обхода

    //result[i] и result[i+1] идут против часовой стрелки
    //

    int size = result.size();
    for (int i = 0; i <= result.size() - 1; i++) {
        double rotate = VecProduct(result[i % size], result[(i + 1) % size],
                                   result[(i + 1) % size], origin);
        if (rotate < 0) {
            exist = false;
            break;
        }
    }
    return exist;
}


int main()
{
    vector <PointVec> convex1;
    vector <PointVec> convex2;
    int n, m;
    cin >> n;
    for (int i = 0; i < n; i++) {
        PointVec point;
        cin >> point.first >> point.second;
        convex1.push_back(point);
    }
    cin >> m;
    for (int i = 0; i < m; i++) {
        PointVec point;
        cin >> point.first >> point.second;
        convex2.push_back(point);
    }

    if (Action(convex1, convex2)) {
        cout << "YES";
    }else {
        cout << "NO";
    };
    return 0;
}