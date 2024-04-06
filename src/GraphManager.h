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
    int averageFlowRatio;

public:
    GraphManager();

    void makePipes();
    void makeNodes();
    void addPipes();
    void makeSuperSource();
    void makeSuperSink();

    Vertex<Node> *nodeFinder(const string& code);

    string IdToCode(int id, station_type type);

    void setOptimalFlows();
    bool bfsPath(const string& source, map<string, string> &parent);

    void networkStrength();
    int averageNetworkFlowRatio();
    int averageCityFlowRatio(const string& code);
    void flowRatioBalancer();

    void removeSOrRNode(string code);
    void removePipe(string origin, string dest);
    void makeNodesWithoutNode(string code);
    void makePipesWithoutNodePipes(string code);
    void makePipesWithoutPipe(string origin, string dest);

    void removeNode(string code);


    Graph<Node> getGraph();
};


#endif //DA_PROJ_1_GRAPHMANAGER_H
