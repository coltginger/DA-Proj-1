#include "GraphManager.h"


GraphManager::GraphManager() {
    makeNodes();
    makePipes();
    addPipes();
    makeSuperSource();
    makeSuperSink();
    setOptimalFlows("SuperSource", "ASuperSink");
    averageFlowRatio = averageNetworkFlowRatio(_graph);
}

Graph<Node> GraphManager::getGraph() {
    return _graph;
}

/**
 * @brief Creates pipes from the Pipes file
 * @details Time complexity O(n) where n is the number of strings in the Pipes file
 */
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

/**
 * @brief Creates and adds vertex to the graph from the three Node files
 * @details Time complexity O(n) where n is the number of total strings in the three corresponding files
 */
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

/**
 * @brief Adds the pipes as edges to the graph
 * @details Time complexity 0(n) where n is the number of Pipes in the vector
 */
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

/**
 * @brief Adds a vertex to the graph with edges to all Water Reservoirs with weight equal to their MaxDelivery
 * @details Time complexity 0(n) where n is the number of vertex in the graph
 */
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

/**
 * @brief Adds a vertex to the graph with edges incoming from all Cities with weight equal to their demand
 * @details Time complexity 0(n) where n is the number of vertex in the graph
 */
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

/**
 * @brief Finds the vertex pointer when given its Node's code
 * @details Time complexity O(n) where n is the number of vertex in the graph
 * @param string code
 * @return the pointer of the Vertex with the Node with the code given
 */
Vertex<Node> *GraphManager::nodeFinder(const string& code) {
    string newsource;
    for (auto i: _graph.getVertexSet()) {
        if (i->getInfo().getCode() == code) {
            return i;
        }
    }
    return nullptr;
}

/**
 * @brief turns a given id into the respective code, according to the type given
 * @details Time complexity 0(1)
 * @param int id
 * @param station_type type
 * @return the node's code
 */
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

/**
 * @brief Through BFS, finds the currently shortest paths with capacity to the Super Sink
 * @details Time complexity O(V + E), where V is the number of vertex and E is the number of edges in the graph
 * @param source
 * @param target
 * @return True if a path is found, false if not
 */
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

/**
 * @brief Finds the shortest available capacity in the paths given by findAugmentingPath
 * @details Time complexity O(V), where V is the number of vertex in the graph
 * @param source
 * @param target
 * @return The path's bottleneck
 */
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

/**
 * @brief Adds the bottleneck as a flow through the augmenting path
 * @details Time complexity O(V), where V is the number of vertex in the graph
 * @param source
 * @param target
 * @param f
 */
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

/**
 * @brief With the implementation of the methods that are called, this method uses a Edmonds-Karp algorithm to fill the edges with the most optimal flow
 * @details Time complexity is O(V*E^2) where V is the number of vertex and E is the number of edges in the graph
 * @param ss
 * @param ts
 */
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

}

/**
 * @brief Prints the maximum amount of water that a given city can recieve
 * @details Time complexity O(n) where n is the number of edges incoming to the given city
 * @param code
 */
void GraphManager::writeFlow(std::string code) {
    auto i = nodeFinder(code);
    for (auto j : i->getAdj()){
        cout << i->getInfo().getCode() << " : " << j->getFlow() << endl;
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
        cout << "It is not possible to supply all cities completely even without flow limits";

    for (auto node: _graph.getVertexSet()) {
        if (node->getType() == City) {
            underservedCities.emplace_back(node->getInfo().getCode(),node->getAdj()[0]->getFlow(), node->getInfo().getDemand());
        }
    }

    bool deficient = false;
    for (const auto &underserved: underservedCities) {
        int deficit = get<2>(underserved) - get<1>(underserved);
        if (deficit > 0) {
            if (!deficient) {
                deficient = true;
                cout << "Cities with water deficit: " << endl;
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
    cout << "Final average network flow ratio is: " << averageNetworkFlowRatio(networkCopy) << endl;
}

/*
 * Looks for a node with a given code and removes it from the graph, as well as its outgoing and incoming edges
 * Time complexity is O(V + E), where V is the number of vertices and E is the number of edges
 * Code of a node
 * Returns nothing
 */
void GraphManager::removeNodeAddNode(string code){

    cout << "Flow values before:" << endl;

    networkStrength();

    Vertex<Node> *removedVertex = nodeFinder(code);
    Vertex<Node>temp_vertex = *removedVertex;
    Node node = temp_vertex.getInfo();

    auto adj = removedVertex->getAdj();
    auto incoming = removedVertex->getIncoming();

    _graph.Graph::removeVertex(node);

    setOptimalFlows("SuperSource", "ASuperSink");

    cout << "Flow values after:"<<endl;

    networkStrength();

    station_type type;
    if(node.getCode().substr(0, 1) == "R"){
        type = station_type::Water_Reservoir;
    }
    else if (node.getCode().substr(0, 1) == "P"){
        type = station_type::Pumping_Station;
    }
    else{
        type = station_type::City;
    }

    _graph.addVertex(node,type);

    for (auto edge: adj){
        Vertex<Node> *start = edge ->getOrig();
        Vertex<Node> *end = edge ->getDest();
        _graph.addEdge(start->getInfo(),end->getInfo(),edge->getWeight());
    }

    for (auto edge: incoming){
        Vertex<Node> *start = edge ->getOrig();
        Vertex<Node> *end = edge ->getDest();
        _graph.addEdge(start->getInfo(),end->getInfo(),edge->getWeight());
    }

    setOptimalFlows("SuperSource", "ASuperSink");

    cout << endl;

}

/*
 * Removes a pipe from the graph, outgoing edge from one node to the other and incoming edge from the other node to the first
 * The time complexity is O(V + E), where V is the number of vertices and E is the number of edges
 * Two codes for the origin and the destination of the pipe
 * Returns an int with the weight of the removed edge from the graph
 */
int GraphManager::removeAPipe(string origin, string dest){

    cout << endl << "Flow values before:" << endl;

    networkStrength();

    Vertex<Node> *originNode = nodeFinder(origin);
    Vertex<Node> *destNode = nodeFinder(dest);

    int weight;
    for(auto edge: originNode->getAdj()){
        if(edge->getDest() == destNode){
            weight = edge->getWeight();
            break;
        }
    }

    _graph.removeEdge(originNode->getInfo(),destNode->getInfo());

    setOptimalFlows("SuperSource", "ASuperSink");

    cout <<endl << "Flow values after:"<<endl;

    networkStrength();

    return weight;
}

/*
 * Re insterts previously removed edges from graphs and re-calculates the max flow of the graph
 * The time complexity of the function is O(V), where V is the number of vertexes
 * Receives two vectors, one with codes for the re-introduction of pipes and a vector of weights
 * Returns nothing
 */
void GraphManager::pipeRestore(vector<std::string> codes, vector<int> weights) {

    for(int i = 0; i<codes.size(); i+=2){
        string orig = codes[i];
        string dest = codes[i+1];

        int weight = weights[i/2];

        Vertex<Node> *originNode = nodeFinder(orig);
        Vertex<Node> *destNode = nodeFinder(dest);

        _graph.addEdge(originNode->getInfo(),destNode->getInfo(),weight);

    }

    setOptimalFlows("SuperSource", "ASuperSink");

}