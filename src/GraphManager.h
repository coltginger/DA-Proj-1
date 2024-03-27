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
    void maxEdmondsKarp(Graph<Node> *graph, Node target);
    void maxEdmondsKarp(Graph<Node> *graph);
    void testAndVisit(queue<Vertex<Node>*> &queue, Edge<Pipe> *pipe, Vertex<Node> *node, int residual);
    bool findAugmentingPath(Graph<Node> *graph, Vertex<Node> *source, Vertex<Node> *target);
    int findMinResidualAlongPath(Vertex<Node> *source, Vertex<Node> *target);
    void augmentFlowAlongPath(Vertex<Node> *source, Vertex<Node> *target, int flow);
    Vertex<Node> * nodeFinder(string code);
};


#endif //DA_PROJ_1_GRAPHMANAGER_H
