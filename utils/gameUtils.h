/*
 * @Author: TechAle
 * @Since: 05/11/21
 */


// Check if someone is winning
bool isWinning(const int table[9]) {
    // Check for columns and rows
    for(int i = 0; i < 3; i++) {
        if ((table[i] != 0 && table[i] == table[i + 3] && table[i] == table[i + 6])
            || (table[i*3] != 0 && table[i*3] == table[i*3+1] && table[i*3] == table[i*3+2])
                )
            return true;
    }

    // Check oblique
    if ((table[0] != 0 && table[0] == table[8] && table[4] == table[0])
        || (table[2] != 0 && table[2] == table[4] && table[2] == table[6]))
        return true;

    return false;
}

// Check if we have filled the game (isnt this useless?)
bool isFilled(const int table[9]) {
    for(int i = 0; i < 9; i++)
        if (table[i] == 0)
            return false;
    return true;
}

// Join isFilled and isWinning in 1 function
bool isOver(const int table[9]) {
    if (isWinning(table))
        return true;
    if (isFilled(table))
        return true;
    return false;
}
