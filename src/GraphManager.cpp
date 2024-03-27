#include "GraphManager.h"

GraphManager::GraphManager() {
    makeNodes();
    makePipes();
    addPipes();
}

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

void GraphManager::makeNodes() {
    auto cityinfo = _vectors.getCitiesFile();
    auto stationinfo = _vectors.getStationsFile();
    auto reservoirinfo = _vectors.getReservoirsFile();

    for (int i = 0; i<cityinfo.size(); i=i+5){
        Node newNode = Node();
        newNode.setCity(cityinfo[i]);
        newNode.setId(stoi(cityinfo[i+1]));
        newNode.setCode(cityinfo[i+2]);
        newNode.setDemand(stoi(cityinfo[i+3]));
        newNode.setPopulation(stoi(cityinfo[i+4]));

        _graph.addVertex(newNode, City);
    }

    for (int i = 0; i<stationinfo.size(); i=i+2){
        Node newNode = Node();
        newNode.setId(stoi(stationinfo[i]));
        newNode.setCode(stationinfo[i+1]);

        _graph.addVertex(newNode, Pumping_Station);
    }

    for (int i = 0; i<reservoirinfo.size(); i=i+5){
        Node newNode = Node();
        newNode.setReservoir(reservoirinfo[i]);
        newNode.setMunicipality(reservoirinfo[i+1]);
        newNode.setId(stoi(reservoirinfo[i+2]));
        newNode.setCode(reservoirinfo[i+3]);
        newNode.setMaxDelivery(stoi(reservoirinfo[i+4]));

        _graph.addVertex(newNode, Water_Reservoir);
    }
}

void GraphManager::addPipes() {
    for(int i = 0; i<_pipes.size(); i++){
        Vertex<Node>* source = nodeFinder(_pipes[i].getPointA());
        Vertex<Node>* target = nodeFinder(_pipes[i].getPointB());

        int weight = _pipes[i].getCapacity();
        _graph.addEdge(source->getInfo(), target->getInfo(), weight);

        if (_pipes[1].getDirection() == 0){
            _graph.addEdge(target->getInfo(), source->getInfo(), weight);
        }
    }
}

Vertex<Node> * GraphManager::nodeFinder(std::string code) {
    string newsource;
    for(auto i : _graph.getVertexSet()){
        if(i->getInfo().getCode() == code){
            return i;
        }
    }
}

void GraphManager::maxEdmondsKarp(Graph<Node> *graph, Node target) {


}

void GraphManager::maxEdmondsKarp(Graph<Node> *graph) {

}

void GraphManager::testAndVisit(queue<Vertex<Node> *> &queue, Edge<Pipe> *pipe, Vertex<Node> *node, int residual) {

}

bool GraphManager::findAugmentingPath(Graph<Node> *graph, Vertex<Node> *source, Vertex<Node> *target) {
    return false;
}

int GraphManager::findMinResidualAlongPath(Vertex<Node> *source, Vertex<Node> *target) {
    return 0;
}

//template <class T>
void GraphManager::augmentFlowAlongPath(Vertex<Node> *source, Vertex<Node> *target, int f) {
    // Traverse the augmenting path and update the flow values accordingly
    for (auto v = target; v != source;)
    {
        auto e = v->getPath();
        double flow = e->getFlow();
        if (e->getDest() == v)
        {
            e->setFlow(flow + f);
            v = e->getOrig();
        }
        else
        {
            e->setFlow(flow - f);
            v = e->getDest();
        }
    }
}

