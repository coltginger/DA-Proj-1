#include "App.h"
#include <iostream>
#include <string>
using namespace std;

App::App() {}

void App::run() {
    bool STOP = false;

    while (!STOP) {
        cout << "Welcome to the Water Management System!" << endl <<
             "1. Max amount of water that can reach each or a specific city. " << endl <<
             "2. Verify satisfiability of water needs. " << endl <<
             "3. Rebalance the network" << endl <<
             "4. Remove an element from the network (Reservoir, Station or Pipe).\" << endl; " << endl <<
             "0. Close the program." << endl <<
             "Please select an option (number): ";

        int option, a, id;
        string enter;
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
                    for (auto i : _graphManager.getGraph().getVertexSet()){
                        if (i->getType() == City){
                            _graphManager.writeFlow(i->getInfo().getCode());
                        }
                    }

                    cout << endl << "Press enter to continue." << endl;
                    cin.ignore(std::numeric_limits<streamsize>::max(),'\n');
                    cin.get();
                }
                else if (a==2) {
                    cout << endl << "Please write the city ID: ";
                    cin >> id;
                    cout << endl;
                    auto cityCode = _graphManager.IdToCode(id, City);
                    _graphManager.writeFlow(cityCode);

                    cout << endl << "Press enter to continue." << endl;
                    cin.ignore(std::numeric_limits<streamsize>::max(),'\n');
                    cin.get();
                }
                break;
            case 2:
                _graphManager.networkStrength();

                cout << endl << "Press enter to continue." << endl;
                cin.ignore(std::numeric_limits<streamsize>::max(),'\n');
                cin.get();
                break;
            case 3:
                _graphManager.flowRatioBalancer();

                cout << endl << "Press enter to continue." << endl;
                cin.ignore(std::numeric_limits<streamsize>::max(),'\n');
                cin.get();
                break;
            case 4:
                removeOption();
                break;
            default:
                cout << "Invalid option. Please select a valid option." << endl;
                break;
        }
    }
}

void App::removeOption() {
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
                break;
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
    bool STOP = false;

    string code;

    while(!STOP){
        cout << endl << "Input the code of the Pumping Station:" << endl;

        cout << "Input 0 to exit." << endl;

        cin >> code;

        if(code == "0"){
            STOP = true; // Exit the program
        }
        else if(_graphManager.nodeFinder(code) == nullptr){
            cout << endl << "No node found with given code." << endl << endl;
        }
        else {
            if (toUpperString(code).substr(0, 3) != "PS_") {
                cout << endl << "Wrong code format for pumping stations." << endl
                     << "Please input a new code." << endl;
            }
            else {
                _graphManager.removeNodeAddNode(code);
                STOP = true;
            }
        }
    }
}

void App::removeReservoire() {
    bool STOP = false;

    string code;

    while(!STOP){
        cout << endl << "Input the code of the reservoir:" << endl;
        cout << "Input 0 to exit." << endl;

        cin >> code;

        if(code == "0"){
            STOP = true; // Exit the program
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
                _graphManager.removeNodeAddNode(code);
                STOP = true;
            }
        }
    }
}

void App::removePiping() {
    bool STOP = false;

    string start, dest;
    bool valid_edge;

    while(!STOP){
        cout << "Input the codes for the start and destination of the pipes." << endl;
        cout << "Input 0 to exit." << endl;
        cout << "Start node code:" << endl;
        cin >> start;

        if(start == "0"){
            STOP = true; // Exit the program
        }
        else if(_graphManager.nodeFinder(start) == nullptr){
            cout << endl << "No node found with given code." << endl << endl;
        }
        else{
            cout <<endl << "Destination node code:";
            cin >> dest;

            for(auto edge: _graphManager.nodeFinder(start)->getAdj()){
                if(edge->getDest()->getInfo().getCode() == dest){
                    valid_edge = true;
                }
            }

            if(dest == "0"){
                STOP = true; // Exit the program
            }
            else if (!valid_edge){
                cout <<endl << "No node found with given code. " << endl << endl;
            }
            else{
                _graphManager.removePipeAddPipe(start,dest);
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