#include <iostream>
#include "board.h"
#include "play.h"
using namespace std;

int main() {
    cout << "Tic Tac Toe";
    bool game = true;

    // Main loop
    while (game) {

        // Choose
        cout        << endl
                    << "Select option:" << endl
                    << "1) Train" << endl
                    << "2) Load" << endl
                    << "3) Play" << endl
                    << "4) Close" << endl
                    << "Choose: ";

        int choose;
        cin >> choose;

        // Switch looks good
        switch(choose) {
            case 1:
                break;
            case 2:
                break;
            case 3:
                play();
                break;
            case 4:
                game = false;
                break;
        }

    }


    return 0;
}
