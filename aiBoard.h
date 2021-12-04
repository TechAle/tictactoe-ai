/*
 * @Author: TechAle
 * @Since: 21/09/21
 */
#include <list>
#include <utility>
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

    // First aiBoard, empty
    aiBoard() {
        fill(table, table+9, 0);
        this->father = nullptr;
        this->round = 0;
        played = -1;
        createChildrens();
    }

    explicit aiBoard(const string& path) { // NOLINT(cppcoreguidelines-pro-type-member-init)
        ifstream fin (path);
        string     myStr;

        string tempFather;
        aiBoard* toCheck = this;

        getline(fin, myStr);
        this->father = nullptr;

        this->loadString(myStr, tempFather);

        while(getline(fin, myStr))
        {
            aiBoard tempBoard = aiBoard(myStr, tempFather);

            aiBoard* toAdd = toCheck->whereAdd(tempFather, "");

            toAdd->childrens.push_back(new aiBoard(tempBoard.table, toAdd, tempBoard.round, tempBoard.winCross, tempBoard.winCircle, tempBoard.tieGame,
                                                  tempBoard.lostCircle, tempBoard.lostCross, tempBoard.played, tempBoard.id));
            toCheck = toAdd->childrens.back();

        }

        int a = 0;

    }

    static bool check2String(const string& now, const string& toCheck) {
        int len = now.length();
        if (len != toCheck.length())
            return false;
        for(int i = 0; i < len; i++)
            if (now[i] != toCheck[i])
                return false;
        return true;
    }

    aiBoard* whereAdd(const string& idCheck, const string& coming) {
        if (check2String(this->id, idCheck))
            return this;
        else {
            for (auto child : this->childrens) {
                aiBoard *temp = child->whereAdd(idCheck, "");
                if (temp != nullptr)
                    return temp;
            }
            if (this->father != nullptr)
                return this->father->whereAdd(idCheck, this->id);
            else return this;

        }
    }

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

    explicit aiBoard(const string& toLoad, string& father) { // NOLINT(cppcoreguidelines-pro-type-member-init)
        this->loadString(toLoad, father);
    }


    // Modified version of https://stackoverflow.com/questions/16826422/c-most-efficient-way-to-convert-string-to-int-faster-than-atoi/16826908
    static int fast_atoi( const string& str, int len )
    {
        int val = 0;
        for(int i = 0; i < len - 1; i++) {
            char value = str[i];
            val = val*10 + (value - '0');
        }
        return val;
    }

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



};
