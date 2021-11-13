/*
 * @Author: TechAle
 * @Since: 21/09/21
 */

#include <algorithm>
#include <cctype>
#include <string>
#include <iostream>
#include <list>
#include <fstream>
#include <iomanip>
#include <ctime>
#include <sstream>
#include <filesystem>
#include "aiBoard.h"

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

    string salvataggio;
    cout    << endl
            << "Salvare? (si/no): ";
    cin >> salvataggio;
    transform(salvataggio.begin(), salvataggio.end(), salvataggio.begin(),
              [](unsigned char c){ return std::tolower(c); });

    if (salvataggio.compare("si") == 0) { // NOLINT(readability-string-compare)
        std::__fs::filesystem::create_directory("trains");

        ofstream myfile;

        auto t = time(nullptr);
        auto tm = *localtime(&t);

        ostringstream oss;
        oss << put_time(&tm, "%d-%m-%Y %H-%M-%S");
        auto str = oss.str();

        myfile.open ("./trains/"+str+".txt");


        trainingSet.printFile(myfile);


        myfile.close();
    }

}


