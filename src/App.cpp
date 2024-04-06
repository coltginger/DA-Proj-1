#include "App.h"
#include <iostream>
#include <string>
using namespace std;

App::App() {}

void clearScreen() {
    system("clear");
}

void App::run() {
    bool STOP = false;

    while (!STOP) {
        clearScreen();
        cout << "Welcome to the Water Management System!" << endl;
        cout << "Please select an option (number): " << endl;
        cout << "1. Max amount of water that can reach each or a specific city." << endl;
        cout << "2. Verify satisfiability of water needs." << endl;
        cout << "3. Remove an element from the network (Reservoir, Station or Pipe)." << endl;
        cout << "0. Close the program." << endl;

        int option, a, id;
        cin >> option;

        // Handle invalid input
        if (cin.fail()) {
            cout << "Invalid input. Please enter a valid option." << endl;
            cin.clear(); // Clear error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            continue;
        }

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
                break;
            case 2:
                _graphManager.networkStrength();
                break;
            case 3:
                removeOption();
                break;
            case 4:
                removePipe();
                break;
            default:
                cout << "Invalid option. Please select a valid option." << endl;
                break;
        }
    }
}

void App::removeOption() {
    clearScreen();
    bool STOP = false;

    while (!STOP) {
        cout << "1. Remove Reservoir." << endl;
        cout << "2. Remove Station." << endl;
        cout << "3. Remove Pipe." << endl;
        cout << "b. Go back." << endl;
        cout << "0. Close the program." << endl;
        cout << "Please select an option: ";

        char choice;
        string code, start, dest;
        cin >> choice;

        switch (choice) {
            case '1':
                removeReservoire();
                break;
            case '2':
                removePumpingStation();
            case '3':
                removePiping();
                break;
            case 'b':
                STOP = true;
                break;
            case '0':
                exit(0); // Exit the program
            default:
                cout << "Invalid input. Please enter a valid option." << endl;
                break;
        }
    }
}







void App::removePumpingStation() {
    clearScreen();
    bool STOP = false;

    string code;

    while(!STOP){
        cout << endl << "Input the code of the reservoir:" << endl;
        cout << "Press 0 to exit." << endl;

        cin >> code;

        if(code == "0"){
            exit(0); // Exit the program
        }
        else if(_graphManager.nodeFinder(code) == nullptr){
            cout << endl << "No node found with given code." << endl << endl;
        }
        else {
            if (toUpperString(code).substr(0, 3) != "PS_") {
                cout << endl << "Wrong code format for reservoires." << endl
                     << "Please input a new code." << endl;
            }
            else {
                _graphManager.removeSOrRNode(code);
                cout << endl << "With the pipe removed:" << endl;
                _graphManager.networkStrength();
                STOP = true;
            }
        }
    }
}

void App::removeReservoire() {
    clearScreen();
    bool STOP = false;

    string code;

    while(!STOP){
        cout << endl << "Input the code of the reservoir:" << endl;
        cout << "Press 0 to exit." << endl;

        cin >> code;

        if(code == "0"){
            exit(0); // Exit the program
        }
        else if(_graphManager.nodeFinder(code) == nullptr){
            cout << endl << "No node found with given code." << endl << endl;
        }
        else {
            if (toUpperString(code).substr(0, 2) != "R_") {
                cout << endl << "Wrong code format for reservoires." << endl
                     << "Please input a new code." << endl;
            }
            else {
                _graphManager.removeSOrRNode(code);
                cout << endl << "With the pipe removed:" << endl;
                _graphManager.networkStrength();
                STOP = true;
            }
        }
    }
}

void App::removePiping() {
    clearScreen();
    bool STOP = false;

    string start, dest;

    while(!STOP){
        cout << "Input the codes for the start and destination of the pipes." << endl;
        cout << "Press 0 to exit." << endl;
        cout << "Start node code:" << endl;
        cin >> start;

        if(start == "0"){
            exit(0); // Exit the program
        }
        else if(_graphManager.nodeFinder(start) == nullptr){
            cout << endl << "No node found with given code." << endl << endl;
        }
        else{
            cout <<endl << "Destination node code:";
            cin >> dest;

            if(dest == "0"){
                exit(0); // Exit the program
            }
            else if (_graphManager.nodeFinder(dest) == nullptr){
                cout <<endl << "No node found with given code. " << endl << endl;
            }
            else{
                GraphManager withoutPipe = _graphManager.removePipe(start, dest);
                cout << endl << "With the pipe removed:" << endl;
                _graphManager.networkStrength();
                STOP = true;

            }
        }

    }
}






string App::toUpperString(string &str) {
    string newString; // Corrected declaration of newString
    for (char ch : str) { // Corrected syntax of for loop
        // convert 'a' to uppercase
        newString += toupper(ch);
    }
    return newString;
}