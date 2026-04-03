#include <iostream>
#include <cstdio>
#include "Rectangle.h"
#include "pet.h"
#include "Music.h"
using namespace std;

int main() {
    Rectangle rect1(3.4, 2.5);

    cout << "Rectangle1" << endl;
    cout << "Area: " << rect1.getArea() << endl;
    cout << "Perimeter: " << rect1.getPerimeter() << endl;
    cout << "Is Square? " << boolalpha << rect1.isSquare() << endl;

    printf("==========\n");

    //Pet 클래스 테스트
    Pet myPet("Kong", 5, "Cat");
    cout << "My pet's name is " << myPet.getName() << endl;

    //Puppy 클래스 테스트
    Puppy myPuppy("Lucky", 10, "Dog", "Poodle");
    cout << "My puppy's breed is " << myPuppy.getBreed() << endl;

    printf("==========\n");

    //Streaming Service 테스트
    MusicStreamingService myService("Spotify");

    //음악 Service에 추가하기
    myService.addMusic("SWIN", "BTS", "ARIRANG", 2026);
    myService.addMusic("RUDE", "Hearts2Hearts", "RUDE", 2026);
    myService.addMusic("BANGBANG", "IVE", "REVIVE", 2026);
    myService.addMusic("JUMP", "BlackPink", "BornPink", 2022);

    //TITLE로 search
    string music_title;
    cout << "Enter the Music Title: ";
    cin >> music_title;

    //scanf_s("%s", &music_title); 위에랑 같음
    Music* result = myService.searchByTitle(music_title);

    if (result != NULL) {
        cout << "Found: " << result->getTitle() << " by " << result->getArtist() << endl;
    }
    else {
        cout << "Not Found" << endl;
    }
}