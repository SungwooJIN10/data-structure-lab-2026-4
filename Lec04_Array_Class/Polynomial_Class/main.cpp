#include <iostream>
#include <iomanip>
using namespace std;

#define MAX_DEGREE 80

class Polynomial {
private:
    int degree;
    float coef[MAX_DEGREE];

public:
    Polynomial() {
        degree = 0;
        for (int i = 0; i < MAX_DEGREE; i++) {
            coef[i] = 0;
        }
    }

    bool isZero() {
        return degree == 0 && coef[0] == 0;
    }

    void read() {
        cout << "다항식의 최고 차수를 입력하시오: ";
        cin >> degree;

        cout << "각 항의 계수를 입력하시오 (총 " << degree + 1 << "개): ";
        for (int i = 0; i <= degree; i++) {
            cin >> coef[i];
        }
    }

    void add(Polynomial a, Polynomial b) {
        for (int i = 0; i < MAX_DEGREE; i++) coef[i] = 0;

        if (a.degree > b.degree) {
            *this = a;
            for (int i = 0; i <= b.degree; i++) {
                coef[i + (degree - b.degree)] += b.coef[i];
            }
        }
        else {
            *this = b;
            for (int i = 0; i <= a.degree; i++) {
                coef[i + (degree - a.degree)] += a.coef[i];
            }
        }
    }

    void display(const char* str) {
        cout << str;
        for (int i = 0; i < degree; i++) {
            cout << fixed << setprecision(1) << coef[i] << "x^" << degree - i << " + ";
        }
        cout << fixed << setprecision(1) << coef[degree] << endl;
    }
};

int main() {
    Polynomial a, b, c;

    a.read();
    b.read();
    c.add(a, b);

    a.display("A = ");
    b.display("B = ");
    c.display("A+B = ");

    return 0;
}