/*
 * @Author: TechAle
 * @Since: 21/09/21
 */

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

    // Start with a table that exists
    explicit game(const int *initTable, int turn) {
        for(int i = 0; i < 9; i++)
            table[i] = *(initTable + i);
        this->turn = turn;
    }

    int* getBoard() {
        return &table[0];
    }

    // Play a letter
    bool play(int num) {
        if (table[num] != 0)
            return true;
        table[num] = turn % 2 + 1;
        ++turn;
        return false;
    }

    // Check if someone is winning
    bool isWinning() {
        for(int i = 0; i < 3; i++) {
            if ((table[i] != 0 && table[i] == table[i + 3] && table[i] == table[i + 6])
                || (table[i*3] != 0 && table[i*3] == table[i*3+1] && table[i*3] == table[i*3+2])
                )
                return true;
        }

        if ((table[0] != 0 && table[0] == table[8] && table[4] == table[0])
            || (table[2] != 0 && table[2] == table[4] && table[2] == table[6]))
            return true;

        return false;
    }

    // Check if we have filled the game
    bool isFilled() {
        return std::any_of(&table[0], &table[9], [](int i) {return i == 0;});
    }

    // Join isFilled and isWinning in 1 function
    bool isOver() {
        return isWinning() || !isFilled();
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

};
