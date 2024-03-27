#include "App.h"
#include <iostream>
#include <string>
using namespace std;

App::App() {}
void App::run(){
    bool STOP = false;

    while(!STOP){
        cout << "1. Max amount of water that can reach each or a specific city. " << endl
             << "0. Close the program." << endl
             << "Please select an option (number): ";

        int option;
        int a, id;
        cin >> option;

        switch (option) {
            case 0:
                STOP = true;
                break;

            case 1:
                cout << endl << "1. Each city." << endl
                     << "2. Specific city." << endl
                     << "Please select an option: "<< endl;
                cin >> a;
                if(a == 2){
                    cout << endl << "City ID: " << endl;
                    cin >> id;
                }
                break;

        }
    }
};