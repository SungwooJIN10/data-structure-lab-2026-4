#include <iostream>
#include "Music.h"
using namespace std;

int main() {

    cout << "====================" << endl;

    // Streaming Service 테스트
    MusicStreamingService myService("Spotify");

    // 음악 Service에 추가하기
    myService.addMusic("SUN", "BTS", "ARIRANG", 2026);
    myService.addMusic("RIDE", "Hearts2Hearts", "RIDE", 2026);
    myService.addMusic("BANGBANG", "IVE", "REIVE", 2026);
    myService.addMusic("JUMP", "BlackPink", "BornPink", 2022);

    // TITLE search
    string music_title;
    cout << "Enter the Music Title: ";
    cin >> music_title;

    Music* result = myService.searchByTitle(music_title);

    if (result != NULL) {
        cout << "Found: " << result->getTitle()
            << " by " << result->getArtist() << endl;
    }
    else {
        cout << "Not Found" << endl;
    }

    // ARTIST search (교수님 슬라이드 부분🔥)
    string artist_name;
    cout << "Enter the Artist Name: ";
    cin >> artist_name;

    vector<Music*> artistResult = myService.searchByArtist(artist_name);

    if (artistResult.size() > 0) {
        cout << "Found " << artistResult.size()
            << " songs by " << artist_name << " :" << endl;

        for (int i = 0; i < artistResult.size(); i++) {
            cout << artistResult[i]->getTitle() << endl;
        }
    }
    else {
        cout << "Not Found" << endl;
    }

    return 0;
}