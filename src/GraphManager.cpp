#include "GraphManager.h"

void GraphManager::makePipes() {
    auto pipeinfo = _vectors.getPipesFile();
    for (int i = 0; i<pipeinfo.size(); i=i+4){
        string pointA = pipeinfo[i];
        string pointB = pipeinfo[i+1];
        Pipe newPipe = Pipe();
        _pipes.push_back(newPipe);
    }
}

