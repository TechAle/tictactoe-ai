/*
 * @Author: TechAle
 * @Since: 21/09/21
 */

#include <iostream>
#include <algorithm>
#include <cctype>
#include <string>
#include <iostream>
#include <list>
#include <fstream>
#include <iomanip>
#include <ctime>
#include <sstream>
#include <filesystem>
#include "game.h"
#include "play.h"
#include "train.h"
using namespace std;

int main() {
    cout << "Tic Tac Toe";
    bool gameLoop = true;

    // Main loop
    while (gameLoop) {

        // Choose
        cout        << endl
                    << "Select option:" << endl
                    << "1) Train" << endl
                    << "2) Play" << endl
                    << "3) Close" << endl
                    << "Choose: ";

        int choose;
        cin >> choose;

        // Switch looks good
        switch(choose) {
            case 1:
                train();
                break;
            case 2:
                play();
                break;
            case 3:
                gameLoop = false;
                break;
        }

    }


    return 0;
}
