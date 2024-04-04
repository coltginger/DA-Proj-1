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
             "3. Remove a Reservoire or Station" << endl <<
             "4. Remove a Pipe" << endl <<
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
            case 3:
                STOP = removeOption();
                break;
            case 4:
                STOP =
        }
    }
}

bool App::removeOption() {
    bool STOP = false;

    cout << endl << "1.Remove Reservoir" << endl
         << "2.Remove Station" << endl
         << "b. Go back" << endl
         << "0. Close the program." << endl
         << "Please select an option: " << endl;

    char a;
    string code;
    cin >> a;


    while(!STOP) {

        switch (a) {
            case '1':
                cout << endl << "Input the code of the reservoir:" << endl;

                cin >> code;

                if(toUpperString(code).substr(0,1) != "R"){
                    cout << endl << "Wrong code format for reservoires." <<endl
                    << "Please input a new code." << endl;
                    a = 1;
                    break;
                }
                else {
                    _graphManager.removeSOrRNode(code);
                    // analisar flow e printar diferenças;
                    STOP = true;
                }

                break;
            case '2':
                cout << endl << "Input the code of the station:" << endl;

                cin >> code;

                if(toUpperString(code).substr(0,1) != "PS"){
                    cout << endl << "Wrong code format for station." <<endl
                         << "Please input a new code." << endl;
                    a = 2;
                    break;
                }
                else {
                    _graphManager.removePipe(code);
                    // analisar flow e printar diferenças;
                    STOP = true;
                }

                break;
            case 'b':
                STOP = true;
                break;
            case  '0':
                return true;
                break;
            default:
                cout << endl << "Invalid input." << endl
                << "Please try again." << endl;
                return removeOption();
        }
    }

    return false;
}

bool App::pipe(){

}



string App::toUpperString(string &str) {
    string newString; // Corrected declaration of newString
    for (char ch : str) { // Corrected syntax of for loop
        // convert 'a' to uppercase
        newString += toupper(ch);
    }
    return newString;
}