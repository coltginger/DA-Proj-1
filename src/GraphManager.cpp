#include "GraphManager.h"

GraphManager::GraphManager() {
    makeNodes();
    makePipes();
    addPipes();
    makeSuperSource();
    makeSuperSink();
    setOptimalFlows("SuperSource", "ASuperSink");
    setOptimalFlows("SuperSource", "ASuperSink");
    averageFlowRatio = averageNetworkFlowRatio(_graph);
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
        if (_pipes[i].getDirection() == 0) {
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

int GraphManager::getAverageFlow() const {return averageFlowRatio;}

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

bool GraphManager::findAugmentingPath(Vertex<Node>* source, Vertex<Node>* target){
    for (auto v : _graph.getVertexSet()){
        v->setVisited(false);
    }

    queue<Vertex<Node>*> q;
    q.push(source);

    while(!q.empty() && !target->isVisited()){
        auto v = q.front();
        q.pop();
        for(auto e: v->getAdj()){
            if (!e->getDest()->isVisited() && ((e->getWeight()-e->getFlow()) > 0)){
                e->getDest()->setVisited(true);
                e->getDest()->setPath(e);
                q.push(e->getDest());
            }
        }
        for(auto e : v->getIncoming()){
            if (!e->getOrig()->isVisited() && (e->getFlow() > 0)){
                e->getOrig()->setVisited(true);
                e->getOrig()->setPath(e);
                q.push(e->getOrig());
            }
        }
    }
    return target->isVisited();
}

int GraphManager::findBottleneck(string source, string target){
    int f = INT_MAX;
    for (auto v = nodeFinder(target) ; v!= nodeFinder(source);){
        Edge<Node>* e = v->getPath();
        if(e->getDest() == v){
            f = min(f, e->getWeight() - e->getFlow());
            v = e->getOrig();
        }
        else{
            f = min(f, e->getFlow());
            v = e->getDest();
        }
    }
    return f;
}

void GraphManager::addFlowToEdges(string source, string target, int f) {
    for (auto v = nodeFinder(target) ; v!= nodeFinder(source);){
        Edge<Node>* e = v->getPath();
        if(e->getDest() == v){
            e->addFlow(f);
            v = e->getOrig();
        }
        else{
            e->addFlow(-f);
            v = e->getDest();
        }
    }

}

void GraphManager::setOptimalFlows(string ss, string ts) {
    auto s = nodeFinder(ss);
    auto t = nodeFinder(ts);

    for (auto vertex : _graph.getVertexSet()){
        for (auto e : vertex->getAdj()){
            e->setFlow(0);
        }
    }

    while (findAugmentingPath(s, t)){
        addFlowToEdges(ss, ts, findBottleneck(ss, ts));
    }

    for (auto vertex : _graph.getVertexSet()){
        int incomingFlow= 0;
        for (auto e: vertex->getIncoming()){
            incomingFlow += e->getFlow();
        }
    }
}


int getSupply(const Vertex<Node>* city) {
    int supply = 0;
    for (auto edge : city->getIncoming()) supply += edge->getFlow();
    return supply;
}

bool isDeficient(const Vertex<Node>* city) {
    if (getSupply(city) < city->getInfo().getDemand()) return true;
    else return false;
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
        if (node->getType() == City) {
            underservedCities.emplace_back(node->getInfo().getCode(),getSupply(node), node->getInfo().getDemand());
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

int GraphManager::averageNetworkFlowRatio(const Graph<Node>& graph) {
    vector<float> flowRatios;
    float sumRatios = 0;

    for (auto node : graph.getVertexSet()) {
        if (node->getType() == Super_Node) continue;
        for (auto edge : node->getAdj()) {
            flowRatios.push_back(edge->flowRatio());
        }
    }

    for (float ratio : flowRatios) {sumRatios += ratio;}
    return (sumRatios/flowRatios.size())*100;
}

int GraphManager::averageCityFlowRatio(const string& code) {
    vector<float> flowRatios;
    float sumRatios = 0;
    for (auto edge : nodeFinder(code)->getIncoming()) {
        flowRatios.push_back(edge->flowRatio());
    }

    for (float ratio : flowRatios) {sumRatios += ratio;}
    return (sumRatios/flowRatios.size())*100;
}

auto compareFlow = [](Edge<Node> *a, Edge<Node> *b) {
    return a->flowRatio() < b->flowRatio();
};

float maxRatio(Vertex<Node> * city) {
    if (city->getIncoming().size() == 1) return city->getIncoming().front()->flowRatio();
    return (*max_element(city->getIncoming().begin(), city->getIncoming().end(), compareFlow))->flowRatio();}

float minRatio(Vertex<Node> * city) {
    if (city->getIncoming().size() == 1) return city->getIncoming().front()->flowRatio();
    return (*min_element(city->getIncoming().begin(), city->getIncoming().end(), compareFlow))->flowRatio();}


void GraphManager::flowRatioBalancer() {
    Graph<Node> networkCopy = getGraph();
    cout << "Initial average network flow ratio is: " << averageNetworkFlowRatio(networkCopy);


    for (auto city: networkCopy.getVertexSet()) {
        if (city->getType() != City) continue;
        if (city->getIncoming().size() == 1) continue;
        //int initialAverageCityRatio = averageCityFlowRatio(city->getInfo().getCode());
        float initialDelta = maxRatio(city) - minRatio(city);

        for (int i = 0; i < city->getIncoming().size() * 5; i++) {
            for (auto edge: city->getIncoming()) {
                int oldRatio = edge->flowRatio() * 100;
                int newRatio;

                float oldDelta = maxRatio(city) - minRatio(city);
                float newDelta;
                int oldWeight;

                if (oldRatio > averageCityFlowRatio(city->getInfo().getCode())) {
                    oldWeight = edge->getWeight();
                    edge->setWeight(edge->getFlow() - 1);
                    setOptimalFlows("SuperSource", "ASuperSink");
                    newDelta = maxRatio(city) - minRatio(city);
                    newRatio = edge->flowRatio() * 100;

                    if (isDeficient(city)) {
                        edge->setWeight(oldWeight);
                        continue;
                    }
                    while ((newRatio > averageCityFlowRatio(city->getInfo().getCode())
                            || newDelta < oldDelta)
                           && !isDeficient(city)) {
                        oldWeight = edge->getWeight();
                        edge->setWeight(edge->getFlow() - 1);
                        setOptimalFlows("SuperSource", "ASuperSink");
                        oldDelta = newDelta;
                        newDelta = maxRatio(city) - minRatio(city);
                        newRatio = edge->flowRatio() * 100;

                        if (isDeficient(city)) {
                            edge->setWeight(oldWeight);
                            continue;
                        }

                    }
                }
            }
        }
    }

    for (auto vertex: networkCopy.getVertexSet()) {
        if (vertex->getType() == City)
            for (auto edge: vertex->getIncoming()) {
                for (auto pipe: _pipes) {
                    if (edge->getOrig()->getInfo().getCode() == pipe.getPointA() &&
                        edge->getDest()->getInfo().getCode() == pipe.getPointB()) {
                        edge->setWeight(pipe.getCapacity());
                        break;
                    } else continue;
                }
            }
    }
    cout << "Final average network flow ratio is: " << averageNetworkFlowRatio(networkCopy);
}
