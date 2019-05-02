#include <iostream>
#include <vector>
#include <algorithm>

using std::min;
using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::abs;

struct Point {
    int x; //1ая координата
    int y; //2ая координата
    int z; //3ая координата
    Point(const int& x, const int& y, const int& z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }
    Point() {}
};

class SegmentDistance {
    struct Point point1_1, point1_2, //точки первого отрезка
            point2_1, point2_2; //точки второго отрезка

    double a, b, c, d, e, f; //коэффициенты многочлена
    const double eps = 0.0000000000001;

public:

    SegmentDistance(const vector<struct Point>& points) {
        point1_1 = points[0];
        point1_2 = points[1];
        point2_1 = points[2];
        point2_2 = points[3];
        CoefficientInit();
    }

    /*
     * инициализация коэффициентов многочлена
     */
    void CoefficientInit() {
        struct Point vec1 = GetVec(point1_1, point1_2);
        struct Point vec2 = GetVec(point2_1, point2_2);
        struct Point vec3 = GetVec(point2_1, point1_1);

        a = CartesianProduct(vec1, vec1);
        b = CartesianProduct(vec1, vec2);
        c = CartesianProduct(vec2, vec2);
        d = CartesianProduct(vec1, vec3);
        e = CartesianProduct(vec2, vec3);
        f = CartesianProduct(vec3, vec3);
    }

    /*
    * скалярное произведение векторов
    */
    int CartesianProduct (const struct Point& vec1, const struct Point& vec2) {
        return vec1.x*vec2.x + vec1.y*vec2.y + vec1.z*vec2.z;
    }

    /*
    * по двум точкам выдает вектор - массив целых чисел длины 3
    */
    Point GetVec (const Point& point1, const Point& point2) {
        return Point(point2.x - point1.x, point2.y - point1.y, point2.z - point1.z);
    }


    /*
    * подсчет квадрата расстояния как скалярного произведения
    * разности векторов на себя с параметрами s и t
    */
    double  R (double s, double t) {
        return a*s*s - 2*b*s*t + c*t*t + 2*d*s - 2*e*t + f;
    }

    /*
 * возвращает кратчайшее расстояние между отрезками
 * следующим образом:
 * представляю оба отрезка как уравнения векторов вида А + (B - A)*t и C + (D - C) * s
 * s и t принимают значения от 0 до 1
 * тогда квадрат кратчайшего расстояния это минимум скалярного произведения  разности
 * векторов на себя в зависимости от значений s и t
 * берем производную от первого параметра и от второго и получаем систему линейных уравнений, с которой работаем
 * кроме того принимаются во внимание критические случаи когда кратчайшее расстояние прямых
 * не лежит на отрезке
 */
    double Distance() {

        double det = a * c - b * b;

        double s0 = (d >= 0) ? 0 : ((-d) <= a ? -d/a : 0);
        double s1 = ((b - d) <= 0 )? 0 : ((b - d) <= a  ? (b - d)/a : 0 ) ;
        double t0 = (e <= 0) ? 0 : (e <= c ? e/c : 0) ;
        double t1 = ((b + e) <= 0) ? 0 : ((b + e) <= c ? (b + e) / c : 0);
        double s = 0;
        double t = 0;
        if (det  > 0) {
            s = (b*e - c*d) / det;
            t = (a*e - b*d) / det;
        }
        if (t < 0 || s < 0 || t > 1 || s > 1) {
            s = t = 0;
        }
        //рассматривает вырожденные случаи когда один либо два отрезка вырождены
        //сравнение с нулем, с помощью  eps - маленькой эпсилон
        if (a < eps && c < eps) {
            return R( 0, 0);
        }
        if (a  < eps) {
            return min( {R( 0, t0),  R(0, 0), R(0, 1)} );
        }
        if (c < eps) {
            return min ( {R(s0, 0), R( 1, 0), R(0, 0) } );
        }

        return min({R(s, t), R(s0, 0), R( s1, 1),
                    R( 0, t0), R( 1, t1), R( 0, 0),
                    R(0, 1), R(1, 1), R(1, 0) }
        ) ;
    }

};



int main()
{
    vector<struct Point>  points;
    for (int i = 0; i < 4; i++) {
        int x, y, z;
        cin >> x >> y >> z;
        points.emplace_back(x, y, z);
    }

    SegmentDistance segmentDistance = SegmentDistance(points);

    printf("%.20f", sqrt(segmentDistance.Distance()) );


    return 0;
}