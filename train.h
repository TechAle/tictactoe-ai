/*
 * @Author: TechAle
 * @Since: 21/09/21
 */

#include <algorithm>
#include <cctype>
#include <string>
#include <iostream>
#include <list>
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

    int a = 0;

}


