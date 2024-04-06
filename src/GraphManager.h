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

    int getAverageFlow() const;

    Vertex<Node> *nodeFinder(const string& code);

    string IdToCode(int id, station_type type);

    bool findAugmentingPath(Vertex<Node>* source, Vertex<Node>* target);
    int findBottleneck(string source, string target);
    void setOptimalFlows(string ss, string ts);
    void addFlowToEdges(string source, string target, int f);

    void writeFlow(string code);

    void networkStrength();
    int averageNetworkFlowRatio(const Graph<Node>& graph);
    int averageCityFlowRatio(const string& code);
    void flowRatioBalancer();

    void removeNodeAddNode(string code);
    void removePipeAddPipe(string orig, string dest);

    Graph<Node> getGraph();
    FileManager getFileManager();
};


#endif //DA_PROJ_1_GRAPHMANAGER_H