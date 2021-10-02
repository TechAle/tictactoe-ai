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

    /*
     * This second type, teorically, is the best one but, it's really too slow.
     * Basically, for every childrens it checks if there is another children that is the same.
     * If yes, it will redirect to that children
     */

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
                aiBoard* exists = checkExists(newTable, this->round + 1);
                if (exists == nullptr) {
                    // Push new chidren
                    childrens.push_front(new aiBoard(newTable, this->father, round));
                } else childrens.push_front(exists);
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

    aiBoard* checkChildren(const int toCheck[9], aiBoard* aimCheck, int aimRound) {
        if (aimRound > aimCheck->round) {
            aiBoard* temp;
            for(aiBoard* child : aimCheck->childrens)
                if ((temp = checkChildren(toCheck, child, aimRound)) != nullptr)
                    return temp;
        } else {
            bool found = true;
            for (int i = 0; i < 9; i++)
                if (aimCheck->table[i] != toCheck[i]) {
                    found = false;
                    break;
                }
            if (found)
                return aimCheck;

        }

        return nullptr;
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
    aiBoard* checkExists(const int target[9], int aimRound) {
        return checkChildren(target, this->father, aimRound);
    }


};
