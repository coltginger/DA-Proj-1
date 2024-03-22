#include "GraphManager.h"

void GraphManager::makePipes() {
    auto pipeinfo = _vectors.getPipesFile();
    for (int i = 0; i<pipeinfo.size(); i=i+4){
        string pointA = pipeinfo[i];
        string pointB = pipeinfo[i+1];
        int capacity = stoi(pipeinfo[i+2]);
        int direction = stoi(pipeinfo[i+3]);
        Pipe newPipe = Pipe(pointA, pointB, capacity, direction);
        _pipes.push_back(newPipe);
    }
}

