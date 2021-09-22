/*
 * @Author: TechAle
 * @Since: 21/09/21
 */
#include <list>

using namespace std;

class board {
private:
    int table[9]{};
    board* father;
    list<board*> childrens;

    void createChildrens() {
        for(int i : table) {
            if (i == 0) {
                int newTable[9];

                std::copy(std::begin(this->table), std::end(this->table), std::begin(newTable));

                newTable[i] = this->nextPlayer;

                childrens.push_front(new board());
            }
        }
    }

    int win = 0;
    int defeat = 0;
    int round;
    int nextPlayer;
public:
    // First board, empty
    board() {
        std::fill(table, table+9, 0);
        this->father = nullptr;
        this->round = 0;
        this->nextPlayer = 0;
        createChildrens();
    }

    // New board
    explicit board(const int table[9], board *father, int round) {
        for(int i = 0; i < 9; i++)
            this->table[i] = *(table + i);
        this->father = father;
        this->round = round + 1;
        this->nextPlayer = this->round % 2 + 1;
        createChildrens();
    }

    // Update numbers of win
    void updateWin() {
        this->win++;
    }

    // Update numbers of defeats
    void updateDefeat() {
        this->defeat++;
    }

    /*
     * Stage:
     * false -> Go to beginning
     * true -> Lets go down
     */
    board* checkExists(board *target, int aimRound, bool stage) {

        // If we have to go at the top
        if (!stage) {
            // If we are not at the top
            if (this->father != nullptr) {
                // Lets continue. Temp contains the result
                board *temp = this->father->checkExists(target, aimRound, stage);
            // We are at the top
            } else stage = true;
        }

        // If we have to go down
        if (stage) {
            // For every childrens
            for(board *toCheck : childrens) {
                // If the round is the same
                if (toCheck->round == aimRound) {
                    // Check if it's not the one we started
                    if (target != toCheck) {
                        // Check if the array is the same
                        for(int i = 0; i < 9; i++)
                            if (target->table[i] != toCheck->table[i])
                                // It's not
                                return nullptr;
                        // Return new value
                        return toCheck;
                    }
                } else toCheck->checkExists(target, aimRound + 1, true);
            }
        }

        return nullptr;
    }


};
