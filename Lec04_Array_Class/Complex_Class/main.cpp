#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    double a_real, a_imag;
    double b_real, b_imag;

    // 입력
    cin >> a_real >> a_imag;
    cin >> b_real >> b_imag;

    // 1입력값 그대로 출력
    cout << "A = " << a_real << " " << a_imag << endl;
    cout << "B = " << b_real << " " << b_imag << endl;

    // 복소수 형태 출력 (소수점 2자리)
    cout << fixed << setprecision(2);
    cout << "A = " << a_real << " + " << a_imag << "i" << endl;
    cout << "B = " << b_real << " + " << b_imag << "i" << endl;

    // 덧셈 결과 출력
    cout << "A + B = "
        << a_real + b_real << " + "
        << a_imag + b_imag << "i" << endl;

    return 0;
}