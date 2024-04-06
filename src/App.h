#include "GraphManager.h"

#ifndef DA_PROJ_1_APP_H
#define DA_PROJ_1_APP_H


class App {
private:
    GraphManager _graphManager;

public:
    App();
    void run();
    void removeOption();
    void removePiping();
    void removeReservoire();
    void removePumpingStation();
    string toUpperString(string &str);
};


#endif //DA_PROJ_1_APP_H
