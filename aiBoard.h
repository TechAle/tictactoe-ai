/*
 * @Author: TechAle
 * @Since: 21/09/21
 */
#include <list>

using namespace std;

class aiBoard {
private:
    int table[9]{};
    aiBoard* father;
    list<aiBoard*> childrens;

    void createChildrens() {
        int  nextPlayer = this->round % 2 + 1;
        for(int i = 0; i < 9; i++) {
            if (table[i] == 0) {
                // New table
                int newTable[9];
                // Copy original
                std::copy(std::begin(this->table), std::end(this->table), std::begin(newTable));
                // Set new value
                newTable[i] = nextPlayer;
                // Push new chidren
                childrens.push_front(new aiBoard(newTable, this, round));
            }
        }
    }

    int win = 0;
    int defeat = 0;
    int round;
public:
    // First aiBoard, empty
    aiBoard() {
        std::fill(table, table+9, 0);
        this->father = this;
        this->round = 0;
        createChildrens();
    }

    // New aiBoard
    explicit aiBoard(const int table[9], aiBoard *father, int round) {
        for(int i = 0; i < 9; i++)
            this->table[i] = *(table + i);
        this->father = father;
        this->round = round + 1;
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
     *
     * target -> The beginning
     *
     * aimRound -> Which round we want
     */
    aiBoard* checkExists(aiBoard *target, int aimRound, bool stage) {

        // If we have to go at the top
        if (!stage) {
            // If we are not at the top
            if (this->father != nullptr) {
                // Lets continue. Temp contains the result
                aiBoard *temp = this->father->checkExists(target, aimRound, stage);
            // We are at the top
            } else stage = true;
        }

        // If we have to go down
        if (stage) {
            // For every childrens
            for(aiBoard *toCheck : childrens) {
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
