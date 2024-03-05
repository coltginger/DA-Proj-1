#include <vector>
#include <string>
using namespace std;
#ifndef DA_PROJ_1_FILEMANAGER_H
#define DA_PROJ_1_FILEMANAGER_H

//esta classe toda serve para passar o conteúdo dos ficheiros para vetores, depois, o graphmanager, passa esses vetores para um graph
class FileManager {
private:
    vector<string> _reservoirsfile;
    vector<string> _stationsfile;
    vector<string> _citiesfile;
    vector<string> _pipesfile;

public:
    FileManager();

    void setReservoirsFile(vector<string> reservoirsfile);
    void setStationsFile(vector<string> stationsfile);
    void setCitiesFile(vector<string> citiesfile);
    void setPipesFile(vector<string> pipesfile);

    vector<string> getReservoirsFile();
    vector<string> getStationsFile();
    vector<string> getCitiesFile();
    vector<string> getPipesFile();

    vector<string> filetoVector(string filename);

};


#endif //DA_PROJ_1_FILEMANAGER_H
