/*
 * @Author: TechAle
 * @Since: 21/09/21
 */
using namespace std;

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
    while (game.isOver()) {
        // Print game
        game.print();
        // Get input
        do {
            cout << endl << "Position: ";
            cin >> choose;
        }while (game.play(choose));

    }

    if (game.isWinning())
        cout << "Win: " << game.player();
    else cout << "Nobody won";
    cout << endl;


}
