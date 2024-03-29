#include "GraphManager.h"

GraphManager::GraphManager() {
    makeNodes();
    makePipes();
    addPipes();
    makeSuperSource();
    setOptimalFlows();
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

void GraphManager::makeSuperSource() {
    Node supeSource = Node();
    supeSource.setCode("Super");
    _graph.addVertex(supeSource, Super_Node);
    auto s = nodeFinder("Super");

    for (auto i : _graph.getVertexSet()){
        if (i->getType() == Water_Reservoir){
            _graph.addEdge(s->getInfo(), i->getInfo(), i->getInfo().getMaxDelivery());
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

string GraphManager::IdToCode(int id, station_type type) {
    switch (type) {
        case City:
            return ("C_" + to_string(id));
        case Water_Reservoir:
            return ("R_" + to_string(id));
        case Pumping_Station:
            return ("PS_" + to_string(id));
    }
}

void GraphManager::setOptimalFlows() {
    for (auto i: _graph.getVertexSet()) {
        for (auto j: i->getAdj()) {
            j.setFlow(0);
        }
    }
    map<string, string> parentMap;

    int maxFlow = 0;

    while (bfsPath("Super", parentMap)) {
        int pathFlow = INT_MAX;
        string v = parentMap.begin()->first;
        while(v!= "Super") {
            string u = parentMap[v];
            for (auto j: nodeFinder(u)->getAdj()) {
                if (j.getDest()->getInfo().getCode() == v) {
                    pathFlow = min(pathFlow, (j.getWeight() - j.getFlow()));
                    break;
                }
            }
            v = parentMap.at(v);
        }

        v = parentMap.begin()->first;
        while(v!= "Super") {
            string u = parentMap[v];
            auto parentNode = nodeFinder(u);
            for (int j = 0; j < parentNode->getAdj().size(); j++){
                if(parentNode->getAdj()[j].getDest()->getInfo().getCode() == v){
                    parentNode->getAdj()[j].addFlow(pathFlow);
                    for(int k = 0; k < parentNode->getAdj()[j].getDest()->getAdj().size(); k++){
                        if(parentNode->getAdj()[j].getDest()->getAdj()[k].getDest()->getInfo().getCode() == u){
                            parentNode->getAdj()[j].getDest()->getAdj()[k].setFlow(parentNode->getAdj()[j].getDest()->getAdj()[k].getWeight());
                        }
                    }
                    break;
                }
            }

            v = parentMap.at(v);
        }
        maxFlow += pathFlow;
        parentMap.clear();
    }
}

bool GraphManager::bfsPath( std::string source, map<string, string>& parentMap) {
    queue<Vertex<Node> *> q;
    parentMap[source] = "";
    for(auto i: _graph.getVertexSet()){
        i->setVisited(false);
    }
    auto sourceVertex = nodeFinder(source);
    sourceVertex->setVisited(true);
    q.push(sourceVertex);

    while(!q.empty()){

        auto v = q.front();
        string parent = v->getInfo().getCode();
        q.pop();

        for (auto e : v->getAdj()){

            if (!e.getDest()->isVisited() && (e.getWeight() - e.getFlow()) > 0){
                auto d = e.getDest();
                q.push(d);
                d->setVisited(true);

                string child = d->getInfo().getCode();
                parentMap[child] = parent;
                if (d->getType() == City) return true;
            }
        }
    }
    return false;
}