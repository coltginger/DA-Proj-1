#include "GraphManager.h"

GraphManager::GraphManager() {
    makeNodes();
    makePipes();
    addPipes();
    makeSuperSource();
    makeSuperSink();
    setOptimalFlows();
    averageFlowRatio = averageNetworkFlowRatio();
}

Graph<Node> GraphManager::getGraph() {
    return _graph;
}

void GraphManager::makePipes() {
    auto pipeinfo = _vectors.getPipesFile();
    for (int i = 0; i < pipeinfo.size(); i = i + 4) {
        string pointA = pipeinfo[i];
        string pointB = pipeinfo[i + 1];
        int capacity = stoi(pipeinfo[i + 2]);
        int direction = stoi(pipeinfo[i + 3]);
        Pipe newPipe = Pipe(pointA, pointB, capacity, direction);
        _pipes.push_back(newPipe);
    }
}

void GraphManager::makeNodes() {
    auto cityinfo = _vectors.getCitiesFile();
    auto stationinfo = _vectors.getStationsFile();
    auto reservoirinfo = _vectors.getReservoirsFile();

    for (int i = 0; i < cityinfo.size(); i = i + 5) {
        Node newNode = Node();
        newNode.setCity(cityinfo[i]);
        newNode.setId(stoi(cityinfo[i + 1]));
        newNode.setCode(cityinfo[i + 2]);
        newNode.setDemand(stoi(cityinfo[i + 3]));
        newNode.setPopulation(stoi(cityinfo[i + 4]));

        _graph.addVertex(newNode, City);
    }

    for (int i = 0; i < stationinfo.size(); i = i + 2) {
        Node newNode = Node();
        newNode.setId(stoi(stationinfo[i]));
        newNode.setCode(stationinfo[i + 1]);

        _graph.addVertex(newNode, Pumping_Station);
    }

    for (int i = 0; i < reservoirinfo.size(); i = i + 5) {
        Node newNode = Node();
        newNode.setReservoir(reservoirinfo[i]);
        newNode.setMunicipality(reservoirinfo[i + 1]);
        newNode.setId(stoi(reservoirinfo[i + 2]));
        newNode.setCode(reservoirinfo[i + 3]);
        newNode.setMaxDelivery(stoi(reservoirinfo[i + 4]));

        _graph.addVertex(newNode, Water_Reservoir);
    }
}

void GraphManager::addPipes() {
    for (int i = 0; i < _pipes.size(); i++) {
        Vertex<Node> *source = nodeFinder(_pipes[i].getPointA());
        Vertex<Node> *target = nodeFinder(_pipes[i].getPointB());

        int weight = _pipes[i].getCapacity();
        if (_pipes[1].getDirection() == 0) {
            _graph.addBidirectionalEdge(source->getInfo(), target->getInfo(), weight);
        }
        else _graph.addEdge(source->getInfo(), target->getInfo(), weight);
    }
}

void GraphManager::makeSuperSource() {
    Node supeSource = Node();
    supeSource.setCode("SuperSource");
    _graph.addVertex(supeSource, Super_Node);
    auto s = nodeFinder("SuperSource");

    for (auto i: _graph.getVertexSet()) {
        if (i->getType() == Water_Reservoir) {
            _graph.addEdge(s->getInfo(), i->getInfo(), i->getInfo().getMaxDelivery());
        }
    }
}

void GraphManager::makeSuperSink() {
    Node superSink = Node();
    superSink.setCode("ASuperSink");
    _graph.addVertex(superSink, Super_Node);
    auto s = nodeFinder("ASuperSink");

    for (auto i: _graph.getVertexSet()) {
        if (i->getType() == City) {
            _graph.addEdge(i->getInfo(), s->getInfo(), i->getInfo().getDemand());
        }
    }
}

Vertex<Node> *GraphManager::nodeFinder(const string& code) {
    string newsource;
    for (auto i: _graph.getVertexSet()) {
        if (i->getInfo().getCode() == code) {
            return i;
        }
    }
    return nullptr;
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
    return "Type not found";
}

void GraphManager::setOptimalFlows() {
    for (auto i: _graph.getVertexSet()) {
        for (auto j: i->getAdj()) {
            j->setFlow(0);
        }
    }
    map<string, string> parentMap;

    int maxFlow = 0;

    while (bfsPath("SuperSource", parentMap)) {
        int pathFlow = INT_MAX;
        string v = parentMap.begin()->first;
        while (v != "SuperSource") {
            string u = parentMap[v];
            for (auto j: nodeFinder(u)->getAdj()) {
                if (j->getDest()->getInfo().getCode() == v) {
                    pathFlow = min(pathFlow, (j->getWeight() - j->getFlow()));
                    break;
                }
            }
            v = parentMap.at(v);
        }

        v = parentMap.begin()->first;
        while (v != "SuperSource") {
            string u = parentMap[v];
            auto parentNode = nodeFinder(u);
            for (int j = 0; j < parentNode->getAdj().size(); j++) {
                if (parentNode->getAdj()[j]->getDest()->getInfo().getCode() == v) {
                    parentNode->getAdj()[j]->addFlow(pathFlow);
                    for (int k = 0; k < parentNode->getAdj()[j]->getDest()->getAdj().size(); k++) {
                        if (parentNode->getAdj()[j]->getDest()->getAdj()[k]->getDest()->getInfo().getCode() == u) {
                            parentNode->getAdj()[j]->getDest()->getAdj()[k]->setFlow(
                                    parentNode->getAdj()[j]->getDest()->getAdj()[k]->getWeight());
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

bool GraphManager::bfsPath(const string& source, map<string, string> &parentMap) {
    queue<Vertex<Node> *> q;
    parentMap[source] = "";
    for (auto i: _graph.getVertexSet()) {
        i->setVisited(false);
    }
    auto sourceVertex = nodeFinder(source);
    sourceVertex->setVisited(true);
    q.push(sourceVertex);

    while (!q.empty()) {

        auto v = q.front();
        string parent = v->getInfo().getCode();
        q.pop();

        for (auto e: v->getAdj()) {

            if (!e->getDest()->isVisited() && (e->getWeight() - e->getFlow()) > 0) {
                auto d = e->getDest();
                q.push(d);
                d->setVisited(true);

                string child = d->getInfo().getCode();
                parentMap[child] = parent;
                if (child == "ASuperSink") return true;
            }
        }
    }
    return false;
}

void supplyUpdater(vector<tuple<string, int, int>> &vector, const string &cityCode, int supply, int demand) {
    for (auto &triplet: vector) {
        if (get<0>(triplet) == cityCode) {
            get<1>(triplet) = get<1>(triplet) + supply;
            return;
        } else continue;
    }
    vector.emplace_back(cityCode, supply, demand);
}


void GraphManager::networkStrength() {
    long total_capacity = 0;
    long total_demand = 0;
    vector<tuple<string, int, int>> underservedCities;

    for (int i = 4; i < _vectors.getReservoirsFile().size(); i = i + 5)
        total_capacity += stoi(_vectors.getReservoirsFile()[i]);
    for (int i = 3; i < _vectors.getCitiesFile().size(); i = i + 5)
        total_demand += stoi(_vectors.getCitiesFile()[i]);
    if (total_demand > total_capacity)
        cout << "Não é possível abastecer todas as cidades completamente mesmo sem limites de caudal";

    for (auto node: _graph.getVertexSet()) {
        if (node->getType() != City) {
            for (auto pipe: node->getAdj())
                if (pipe->getDest()->getType() == City) {
                    supplyUpdater(underservedCities, pipe->getDest()->getInfo().getCode(), pipe->getFlow(),
                                  pipe->getDest()->getInfo().getDemand());
                }
        }
    }

    bool deficient = false;
    for (const auto &underserved: underservedCities) {
        int deficit = get<2>(underserved) - get<1>(underserved);
        if (deficit > 0) {
            if (!deficient) {
                deficient = true;
                cout << "Cidades com defice de agua:" << endl;
                cout << get<0>(underserved) << ": " << deficit << endl;
            } else cout << get<0>(underserved) << ": " << deficit << endl;
        }
    }
}

int GraphManager::averageNetworkFlowRatio() {
    vector<float> flowRatios;
   float sumRatios = 0;

    for (auto node : _graph.getVertexSet()) {
        if (node->getType() == Super_Node) continue;
        for (auto edge : node->getAdj()) {
            flowRatios.push_back((float)edge->getFlow()/edge->getWeight());
        }
    }

    for (float ratio : flowRatios) {sumRatios += ratio;}
    return sumRatios/flowRatios.size()*100;
}

int GraphManager::averageCityFlowRatio(const string& code) {
    vector<float> flowRatios;
    float sumRatios = 0;
    for (auto edge : nodeFinder(code)->getIncoming()) {
        flowRatios.push_back((float)edge->getFlow()/edge->getWeight());
    }

    for (float ratio : flowRatios) {sumRatios += ratio;}
    return sumRatios/flowRatios.size()*100;
}

void GraphManager::flowRatioBalancer() {


}






