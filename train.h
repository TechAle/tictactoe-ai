/*
 * @Author: TechAle
 * @Since: 21/09/21
 */


void train() {

    // Get if multithreading or not
    int multithrading;
    do {
        cout    << endl
                << "1) Sequential" << endl
                << "2) Multithreading";
        cin >> multithrading;
    }while (multithrading != 1 && multithrading != 2);

    // Get if we want to reasume something we stopped in the past
    string checkout;
    cout    << endl
            << "Checkout (no/name): ";
    cin >> checkout;
    // To lowercase
    transform(checkout.begin(), checkout.end(), checkout.begin(),
              [](unsigned char c){ return std::tolower(c); });

    // If we have something to load
    if (checkout.length() > 0 && checkout == "no") {
        // TODO add loading
        cout << endl << "loading lol";
    }

    // Start trainingAl
    aiBoard trainingSet = aiBoard();

    // Ask if he want to save
    string salvataggio;
    cout    << endl
            << "Salvare? (si/no): ";
    cin >> salvataggio;
    // ToLower
    transform(salvataggio.begin(), salvataggio.end(), salvataggio.begin(),
              [](unsigned char c){ return std::tolower(c); });

    // If he want to save
    if (salvataggio.compare("si") == 0) { // NOLINT(readability-string-compare)
        // Create directory "trains"
        std::__fs::filesystem::create_directory("trains");

        // Start creating file
        ofstream myfile;

        // Get name of the file (day-month-year hour-minute-second).txt
        auto t = time(nullptr);
        auto tm = *localtime(&t);

        ostringstream oss;
        oss << put_time(&tm, "%d-%m-%Y %H-%M-%S");
        auto str = oss.str();

        // Open file
        myfile.open ("./trains/"+str+".train");

        // Write everything
        trainingSet.printFile(myfile);

        // Save
        myfile.close();
    }

}


