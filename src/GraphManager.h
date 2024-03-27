#include "FileManager.h"
#include "Graph.h"
#include "Node.h"
#include <vector>
#include "Pipe.h"
using namespace std;

#ifndef DA_PROJ_1_GRAPHMANAGER_H
#define DA_PROJ_1_GRAPHMANAGER_H


class GraphManager {
private:
    Graph<Node> _graph;
    FileManager _vectors;
    vector<Pipe> _pipes;

public:
    GraphManager();

    void makePipes();
    void makeNodes();
    void addPipes();


    Vertex<Node> * nodeFinder(string code);
};


#endif //DA_PROJ_1_GRAPHMANAGER_H
