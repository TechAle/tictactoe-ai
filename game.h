/*
 * @Author: TechAle
 * @Since: 21/09/21
 */
#include "gameUtils.h"
using namespace std;
class game {
private:

    // Our table
    int table[9]{};
    int turn = 0;

public:

    // Start with nothing
    game() {
        std::fill(table, table+9, 0);
    }

    // Play a letter
    bool play(int num) {
        if (table[num] != 0)
            return true;
        table[num] = turn % 2 + 1;
        ++turn;
        return false;
    }

    // Print the game
    void print() {
        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                cout << " " << table[j + i*3] << " ";
                if (j != 2)
                    cout << "|";
            }
            cout << endl;
        }
        cout << "Turn: " << turn << " plays: " << turn % 2 + 1;
    }

    // Return the player at the end of the round
    int player() const {
        return turn % 2 == 1 ? 1 : 2;
    }

    bool isOver() {
        return ::isOver(this->table);
    }

    bool isWinning() {
        return ::isWinning(this->table);
    }


    /*
// Start with a table that exists
explicit game(const int *initTable, int turn) {
    for(int i = 0; i < 9; i++)
        table[i] = *(initTable + i);
    this->turn = turn;
}

int* getBoard() {
    return &table[0];
}*/

};
