#include "FileManager.h"
#include <sstream>
#include <fstream>
using namespace std;

FileManager::FileManager() {
    _reservoirsfile = filetoVector("../src/csv_small/Reservoirs_Madeira.csv");
    _stationsfile = filetoVector("../src/csv_small/Stations_Madeira.csv");
    _citiesfile = filetoVector("../src/csv_small/Cities_Madeira.csv");
    _pipesfile = filetoVector("../src/csv_small/Pipes_Madeira.csv");
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