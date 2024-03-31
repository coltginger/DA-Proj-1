#include "FileManager.h"
#include "Graph.h"
#include "Node.h"
#include <vector>
#include "Pipe.h"
#include <iostream>
#include <limits>
#include <algorithm>
#include <map>

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
    void makeSuperSource();

    void makeSuperSink();

    Vertex<Node> *nodeFinder(string code);

    string IdToCode(int id, station_type type);

    void setOptimalFlows();
    bool bfsPath(string source, map<string, string> &parent);

    void networkStrength();

    Graph<Node> getGraph();
};


#endif //DA_PROJ_1_GRAPHMANAGER_H
