/*
 * @Author: TechAle
 * @Since: 21/09/21
 */
#include "aiBoard.h"

using namespace std;

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
        aiBoard bot = aiBoard();
        while (!game.isOver()) {
            if (first) {
                PlayerPlay(game);
                if (!game.isOver())
                    BotPlay(game, bot);
            } else {
                BotPlay(game, bot);
                if (!game.isOver())
                    PlayerPlay(game);
            }

        }
    }

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
