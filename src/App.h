#include "GraphManager.h"

#ifndef DA_PROJ_1_APP_H
#define DA_PROJ_1_APP_H


class App {
private:
    GraphManager _graphManager;

public:
    App();
    void run();
    bool removeOption();
    string toUpperString(string &str);
};


#endif //DA_PROJ_1_APP_H
