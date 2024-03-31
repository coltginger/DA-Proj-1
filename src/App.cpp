#include "App.h"
#include <iostream>
#include <string>
using namespace std;

App::App() {}

void App::run(){
    bool STOP = false;

    while(!STOP){
        cout << "Please select an option (number): " << endl <<
             "1. Max amount of water that can reach each or a specific city. " << endl <<
             "2. Verify satisfiability of water needs. " << endl <<
             "3. " << endl <<
             "0. Close the program." << endl;


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
                if (a == 1) {
                    /*  for (auto city: _graphManager.getGraph().getVertexSet()) {
                          if (city->getType() == City) {
  */
                    //}
                    //}
                }
                if(a == 2){
                    cout << endl << "City ID: " << endl;
                    cin >> id;
                }
                break;

            case 2:
                _graphManager.networkStrength();
                break;
        }
    }
}