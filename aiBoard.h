/*
 * @Author: TechAle
 * @Since: 21/09/21
 */
#include <list>
#include <utility>
#include <vector>
#include "./utils/stringUtils.h"
#include "./utils/mathUtils.h"

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
                // Add new children
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
    // Our id
    string id;
public:


    // Create an empty board with every childrens
    aiBoard() {
        fill(table, table+9, 0);
        this->father = nullptr;
        this->round = 0;
        played = -1;
        createChildrens();
    }

    // Create a new board given every informations
    explicit aiBoard(const int* board, aiBoard* father, int round, int winCross, int winCircle, int tieGame, int lostCircle, int lostCross, int played, string id) {
        for(int i = 0; i < 9; i++)
            this->table[i] = *(board + i);
        this->father = father;
        this->round = round;
        this->winCross = winCross;
        this->winCircle = winCircle;
        this->tieGame = tieGame;
        this->lostCircle = lostCircle;
        this->lostCross = lostCross;
        this->played = played;
        this->id = move(id);
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

    // Given a path of a file, it loads every board
    explicit aiBoard(const string& path) { // NOLINT(cppcoreguidelines-pro-type-member-init)
        ifstream fin (path);
        string     myStr;

        // String of the father of the node we are checking
        string tempFather;
        // Last node we checked
        aiBoard* toCheck = this;

        // Load the first node, the father
        getline(fin, myStr);
        // Set our father as nullptr
        this->father = nullptr;

        // Load every values
        this->loadString(myStr, tempFather);

        // Load every line
        while(getline(fin, myStr))
        {
            // Generate a temporary board
            aiBoard tempBoard = aiBoard(myStr, tempFather);

            // Find of which board the father is
            aiBoard* toAdd = toCheck->whereAdd(tempFather, "", true);

            // Push a new children
            toAdd->childrens.push_back(new aiBoard(tempBoard.table, toAdd, tempBoard.round, tempBoard.winCross, tempBoard.winCircle, tempBoard.tieGame,
                                                   tempBoard.lostCircle, tempBoard.lostCross, tempBoard.played, tempBoard.id));

            // Save the pointer of the last children we saved
            toCheck = toAdd->childrens.back();

        }


    }

    // Create a new board by uploading a string with every data
    explicit aiBoard(const string& toLoad, string& father) { // NOLINT(cppcoreguidelines-pro-type-member-init)
        this->loadString(toLoad, father);
    }

    // Given a string, it loads every data
    void loadString(string values, string& fatherChange) {
        int stage = 1;
        int start = 10;

        // Save table
        for(int i = 0; i < 9; i++) {
            this->table[i] = values[i] - '0';
        }

        for(int i = 10; i < values.length(); i++) {
            // If delimiter
            if (values[i] == '|') {
                switch(stage++) {
                    // Father
                    case 1:
                        fatherChange = values.substr(start, i - start);
                        break;
                        // Our id
                    case 2:
                        this->id = values.substr(start + 1, i - start - 1);
                        break;
                        // Wins cross
                    case 3:
                        this->winCross = fast_atoi(values.substr(start + 1, i - start - 1), i - start);
                        break;
                        // Wins circle
                    case 4:
                        this->winCircle = fast_atoi(values.substr(start + 1, i - start - 1), i - start);
                        break;
                        // Lost cross
                    case 5:
                        this->lostCross = fast_atoi(values.substr(start + 1, i - start - 1), i - start);
                        break;
                        // Lost circle
                    case 6:
                        this->lostCircle = fast_atoi(values.substr(start + 1, i - start - 1), i - start);
                        break;
                        // Tie Game
                    case 7:
                        this->tieGame = fast_atoi(values.substr(start + 1, i - start - 1), i - start);
                        break;
                        // Played
                    case 8:
                        this->played = fast_atoi(values.substr(start + 1, i - start - 1), i - start);
                        break;
                        // Round
                    case 9:
                        this->round = fast_atoi(values.substr(start + 1, i - start - 1), i - start);
                        break;
                }
                start = i;
            }
        }


    }

    /*
     * Recursion function that find of which node a certain id is children
     * idCheck -> The id we want
     * coming -> From which id we are coming from (it's used with up)
     * up -> If we can go up after have searched every childrens (for not creating an infinite loop)
     */
    aiBoard* whereAdd(const string& idCheck, const string& coming, bool up) {
        // Check if it's the one we want
        if (check2String(this->id, idCheck))
            return this;
        else {
            // If not, iterate for every children we have
            for (auto child : this->childrens) {
                // For every children lets check if one of them it's right
                aiBoard *temp = child->whereAdd(idCheck, "", false);
                // If we have found something
                if (temp != nullptr)
                    // Return the value
                    return temp;
            }
            // If we can go above
            if (this->father != nullptr) {
                // If we are not in a children
                if (up)
                    // Continue searching
                    return this->father->whereAdd(idCheck, this->id, true);
            }
            // Else, we reached the end so, we have to return the first node
            else return this;

        }

        // We have found nothing
        return nullptr;
    }

    int choosePosition(const int* tableNow, bool isCross, aiBoard* checkpoint) {

        // The table we are going to check for the best
        aiBoard* nowCheck = checkpoint == nullptr ? this : checkpoint;

        vector<vector<int> > toCheck;
        int player = 0;

        for(int i = 0; i < 9; i++)
            if (*(tableNow + i) != 0) {
                toCheck.push_back(vector<int>{i,*(tableNow + i)});
            }

        while (!toCheck.empty()) {
            for(int i = 0; i < toCheck.size(); i++) {
                if (toCheck[i][1] == player + 1) {
                    for (auto child : nowCheck->childrens) {
                        if (child->table[toCheck[i][0]] == player + 1) {
                            nowCheck = child;
                            toCheck.erase(toCheck.begin() + i);
                            i--;
                            player = (player + 1) % 2;
                            break;
                        }
                    }
                }
            }
        }

        checkpoint = nowCheck;
        return -1;
    }

    static bool isSame(const int* arr1, const int* arr2) {
        for(int i = 0; i < 9; i++)
            if (arr1[i] != 0 && arr2[i] == 0)
                return false;
        return true;
    }

    static bool isBetter(aiBoard* bestNow, aiBoard* newToCheck, bool isCross) {
        if (isCross) {
            if (bestNow->winCross - bestNow->lostCross < newToCheck->winCross - newToCheck->lostCross)
                return true;
        } else {
            if (bestNow->winCircle - bestNow->lostCircle < newToCheck->winCircle - newToCheck->lostCircle)
                return true;
        }
        return true;
    }

    /*
 * Structure file:
 * tabel
 * father
 * wins/looses
 * tie
 * played
 * round
 *
 * Divided with |
 */
    void printFile(ofstream& file) {
        // Add the table
        for(auto i : table)
            file << i;
        // Divide
        file << "|";

        // If we dont have a father, null, else id
        if (father == nullptr)
            file << "null|";
        else file << father << "|";

        // I also need the id of this
        file << this << "|";

        // Add every informations
        file    << winCross << "|" << winCircle << "|" << lostCross << "|" << lostCircle << "|" << tieGame << "|"
                << played   << "|" << round     << "|\n";

        // For every childrens, add the informations
        for(auto child : childrens)
            child->printFile(file);

    }

    // Update numbers of win
    void updateWin(bool circle) {
        // If circle
        if (circle) {
            this->winCircle++;
            this->lostCross++;
        }
        // If cross
        else {
            this->winCross++;
            this->lostCircle++;
        }
        // Update played
        this->played++;
        // Update father's win/loose
        if (this->father != nullptr)
            this->father->updateWin(circle);
    }

    // Update tie
    void updateTie() {
        this->tieGame++;
        this->played++;
        // Go back
        if (this->father != nullptr)
            this->father->updateTie();
    }


};


/*
 * Old algo, i'll keep this here for maybe in the future i can re-use this concept
 * This works just, it's really slow
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
}*/