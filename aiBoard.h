/*
 * @Author: TechAle
 * @Since: 21/09/21
 */
#include <list>
#include <vector>

using namespace std;

class aiBoard {
private:
    int table[9]{};
    aiBoard* father;
    vector<aiBoard*> childrens;

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
                // Set new values
                newTable[i] = nextPlayer;
                childrens.push_back(new aiBoard(newTable, this, round, i));
                /*
                 * Old algo, good concept just not as optimized as it could be + too slow.
                 * I think this would be good in other types of games that are more complex
                aiBoard* exists = checkExists(newTable, this->round + 1);
                if (exists == nullptr) {
                    // Push new chidren
                    childrens.push_front(new aiBoard(newTable, this->beginning, round));
                } else childrens.push_front(exists);*/
            }
        }
    }

    // Counter win
    int winCross = 0;
    int winCircle = 0;
    // Counter lost
    int lostCross = 0,
        lostCircle = 0;
    // Counter tie
    int tieGame = 0;
    // What was played
    int played;
    // N^Round (used for "performance purpose" in the slow algo)
    int round;
public:

    /*
     * Struttura file:
     * tabella
     * padre
     * vincite/perdite
     * tie
     * giocate
     * round
     *
     * Diviso con |
     */
    void printFile(ofstream& file) {
        for(auto i : table)
            file << i;
        file << "|";

        if (father == nullptr)
            file << "null|";
        else file << father << "|";

        file    << winCross << "|" << winCircle << "|" << lostCross << "|" << lostCircle << "|" << tieGame
                << played   << "|" << round     << "\n";

        for(auto child : childrens)
            child->printFile(file);

    }

    // First aiBoard, empty
    aiBoard() {
        std::fill(table, table+9, 0);
        this->father = nullptr;
        this->round = 0;
        played = -1;
        createChildrens();
    }

    // New aiBoard
    explicit aiBoard(const int table[9], aiBoard *father, int round, int played) {
        // Copy new table
        for(int i = 0; i < 9; i++)
            this->table[i] = *(table + i);
        // Set new values
        this->father = father;
        this->round = round + 1;
        this->played = played;
        // If winning, update
        if (isWinning(this->table))
            updateWin(this->round % 2 == 0);
        else if (this->round == 9)
            updateTie();
        else
            createChildrens();
    }

    // Update numbers of win
    void updateWin(bool circle) {
        if (circle) {
            this->winCircle++;
            this->lostCross++;
        }
        else {
            this->winCross++;
            this->lostCircle++;
        }
        this->played++;
        if (this->father != nullptr)
            this->father->updateWin(circle);
    }

    void updateTie() {
        this->tieGame++;
        this->played++;
        if (this->father != nullptr)
            this->father->updateTie();
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



};
