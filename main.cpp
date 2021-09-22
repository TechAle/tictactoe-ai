/*
 * @Author: TechAle
 * @Since: 21/09/21
 */

#include <iostream>
#include "game.h"
#include "play.h"
#include "train.h"
using namespace std;

int main() {
    cout << "Tic Tac Toe";
    bool play = true;

    // Main loop
    while (play) {

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
                train();
                break;
            case 2:
                break;
            case 3:
                game();
                break;
            case 4:
                play = false;
                break;
        }

    }


    return 0;
}
