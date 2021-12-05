/*
 * @Author: TechAle
 * @Since: 05/11/21
 */


// I have to do this because, for some reasons every functions mess up when we are working with pointers
static bool check2String(const string& now, const string& toCheck) {
    //  Get length
    int len = now.length();
    // If it's not the same
    if (len != toCheck.length())
        // They are not the same
        return false;
    // Else
    for(int i = 0; i < len; i++)
        // If something is different
        if (now[i] != toCheck[i])
            // False
            return false;
    // Everything is the same
    return true;
}

static bool hasExtension(const string& path, const string& extension) {
    // Check the lenght
    int len = path.length();
    int extensionLenght = extension.length();
    if (len < extensionLenght)
        return false;

    // Check if the end is the same
    for(int i = 1; i < extension.length() + 1; i++)
        if (path[len - i] != extension[extensionLenght - i])
            return false;
    return true;
}

// Request a number
static int requestInt(const string& text, int length) {
    int temp;
    do {
        cout    << text << endl
                << "Choose: ";
        cin >> temp;
    }while (temp < 0 || temp > length);
    return temp;
}

// Request a string
static string requestString(const string& text) {
    cout << text;
    string output;
    cin >> output;
    transform(output.begin(), output.end(), output.begin(),
              [](unsigned char c){ return std::tolower(c); });
    return output;
}

