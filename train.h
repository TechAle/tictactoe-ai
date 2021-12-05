/*
 * @Author: TechAle
 * @Since: 21/09/21
 */


void train() {

    int multithreading = requestInt("1) Sequential\n2) Multithreading", 2);

    // Start trainingAl
    aiBoard trainingSet = aiBoard();

    // Ask if he want to save
    string salvataggio = requestString("Salvare? (si/no)");

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


