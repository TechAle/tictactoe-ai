/*
 * @Author: TechAle
 * @Since: 21/09/21
 */
#include "aiBoard.h"

/*
 * TODO create new utils where you add "askInputs" and "hasExtension"
 */

using namespace std;

#include <string>
#include <iostream>
#include <filesystem>
namespace fs = std::__fs::filesystem;

void PlayerPlay(game game);

void BotPlay(game game, aiBoard bot);

void play() {

    // Choose if fighting a bot or not
    int choose = -1;
    while(choose != 1 && choose != 2) {

        cout    << endl
                << "1) Player vs Player" << endl
                << "2) Player vs Bot" << endl
                << "Choose: ";

        cin >> choose;

    }

    // Choose if starting first or last
    bool first = true;
    if (choose == 2) {
        while(choose != 1 && choose != 2) {
            cout    << endl
                    << "1) Start first" << endl
                    << "2) Start last" << endl
                    << "Choose: ";

            cin >> choose;
        }
        first = (choose == 1);
    }

    // Game loop
    game game;

    // Without bot
    if (choose == 1) {
        while (!game.isOver()) {
            PlayerPlay(game);
        }
    // With bot
    } else {

        // Ask what he want
        cout << "1) Create new ai" << endl
             << "2) Load new ai" << endl
             << "Choose: ";

        cin >> choose;

        aiBoard bot;

        // If second
        if (choose == 2) {
            string path = "./trains/";
            std::vector<std::string> data;
            // Iterate for every files
            for (const auto & entry : fs::directory_iterator(path)) {
                // Get file
                string file = entry.path().string();
                int len = file.length();
                // If it can contains the extension we want
                if ( len > 4) {
                    // This is horrible
                    // Check if the extension is .train
                    if (file.at(len - 1) == 'n' &&
                        file.at(len - 2) == 'i' &&
                        file.at(len - 3) == 'a' &&
                        file.at(len - 4) == 'r' &&
                        file.at(len - 5) == 't' &&
                        file.at(len - 6) == '.') {
                        // Print
                        cout << data.size() << ") " << file << endl;
                        data.push_back(file);
                    }
                }
            }

            // Make the player choose the file
            cout << "Choose: ";
            cin >> choose;
            // If it's above, create one form 0
            if (choose > data.size())
                bot = aiBoard();
            else {
                // Else, load the bot
                try {
                    bot = aiBoard(data[choose]);
                // Lets prevent useless crashes
                } catch (const std::exception& ex) {
                    bot = aiBoard();
                }
            }
            return;

        } else {
            // Create a new bot
            bot = aiBoard();
        }

        // While the game it's not done
        while (!game.isOver()) {
            // If We want to play first
            if (first) {
                // Player
                PlayerPlay(game);
                // If it's not over
                if (!game.isOver())
                    // Bot play
                    BotPlay(game, bot);
            } else {
                // Bot play
                BotPlay(game, bot);
                // If not over
                if (!game.isOver())
                    // Player play
                    PlayerPlay(game);
            }

        }
    }

    // If someone is winning
    if (game.isWinning())
        cout << "Win: " << game.player();
    else cout << "Nobody won";
    cout << endl;


}

void BotPlay(game game, aiBoard bot) {

}

void PlayerPlay(game game) {
    int choose = -1;
    // Print game
    game.print();
    // Get input
    do {
        cout << endl << "Position: ";
        cin >> choose;
    } while (game.play(choose));
}
