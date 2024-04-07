#include "FileManager.h"
#include <sstream>
#include <fstream>
#include <iostream>
using namespace std;

/**
 * @brief Before any methods are made and the graph is created, the class by default asks which data set to use
 * @details Time complexity O(1)
 */
FileManager::FileManager() {
    cout << "What dataset would you like to build?" << endl
         << "1. Madeira Data Set" << endl
         << "2. Continental Portugal Data Set" << endl
         << "Please select an option (number): ";
    string choice;
    bool done = false;
    while(!done){
        cin >> choice;
        if (choice == "1") {
            madeiraChosen();
            done = true;
        } else if (choice == "2") {
            continenteChosen();
            done = true;
        } else {
            cout << endl << "Please choose a possible answer" << endl;
        }
    }
}

void FileManager::madeiraChosen() {
    _reservoirsfile = filetoVector("../src/csv_small/Reservoirs_Madeira.csv");
    _stationsfile = filetoVector("../src/csv_small/Stations_Madeira.csv");
    _citiesfile = filetoVector("../src/csv_small/Cities_Madeira.csv");
    _pipesfile = filetoVector("../src/csv_small/Pipes_Madeira.csv");
}

void FileManager::continenteChosen() {
    _reservoirsfile = filetoVector("../src/csv_large/Reservoir.csv");
    _stationsfile = filetoVector("../src/csv_large/Stations.csv");
    _citiesfile = filetoVector("../src/csv_large/Cities.csv");
    _pipesfile = filetoVector("../src/csv_large/Pipes.csv");
}

void FileManager::setReservoirsFile(vector<std::string> reservoirsfile) {
    _reservoirsfile = reservoirsfile;
}

void FileManager::setStationsFile(vector<std::string> stationsfile) {
    _stationsfile = stationsfile;
}

void FileManager::setPipesFile(vector<std::string> pipesfile) {
    _pipesfile = pipesfile;
}

void FileManager::setCitiesFile(vector<std::string> citiesfile) {
    _citiesfile = citiesfile;
}

vector<string> FileManager::getReservoirsFile() {
    return _reservoirsfile;
}

vector<string> FileManager::getStationsFile() {
    return _stationsfile;
}

vector<string> FileManager::getCitiesFile() {
    return _citiesfile;
}

vector<string> FileManager::getPipesFile() {
    return _pipesfile;
}

/**
 * @brief Turns a file with the name given into a vector with all strings separated by commas and newliens as an iteration in it
 * @param filename
 * @return Returns a vector of strings with all the file content
 */
vector<string> FileManager::filetoVector(std::string filename) {
    vector<string> res;

    ifstream file;
    file.open(filename);
    string line;
    string word;
    getline(file, line);

    while(getline(file, line)){
        stringstream ss(line);

        while(getline(ss, word, ',')) res.push_back(word);
    }
    return res;
}