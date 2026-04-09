#include <iostream>
#include <cstring>
using namespace std;

class Car {
protected:
    int speed;
    char name[40];

public:
    int gear;

    // 기본 생성자
    Car() {
        speed = 0;
        gear = 0;
        strcpy_s(name, "None");
    }

    // 매개변수 생성자
    Car(int s, const char* n, int g) : speed(s), gear(g) {
        strcpy_s(name, n);
    }

    // 기어 변경
    void changeGear(int g = 4) {
        gear = g;
    }

    // 속도 5 증가
    void speedUp() {
        speed += 5;
    }

    // 정보 출력
    void display() {
        cout << "[" << name << "] : 기어=" << gear
            << "단 속도=" << speed << "kmph" << endl;
    }
};

class SportsCar : public Car {
public:
    bool bTurbo;

    SportsCar() : Car() {
        bTurbo = false;
    }

    SportsCar(int s, const char* n, int g, bool t) : Car(s, n, g) {
        bTurbo = t;
    }

    void setTurbo(bool bTur) {
        bTurbo = bTur;
    }

    // 터보가 켜져 있으면 20 증가, 아니면 Car의 speedUp 사용
    void speedUp() {
        if (bTurbo)
            speed += 20;
        else
            Car::speedUp();
    }
};

int main() {
    Car c1(50, "Sonata", 3);
    SportsCar s1(100, "Ferrari", 5, true);

    c1.display();
    s1.display();

    cout << "속도 증가..." << endl;

    c1.speedUp();
    s1.speedUp();

    c1.display();
    s1.display();

    return 0;
}