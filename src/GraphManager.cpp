#include "GraphManager.h"

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
        string city = cityinfo[i];
        int id = stoi(cityinfo[i+1]);
        string code = cityinfo[i+2];
        int demand = stoi(cityinfo[i+3]);
        int population = stoi(cityinfo[i+4]);
        Node newNode = Node(City, city, id, code, demand, population);
        Vertex<Node> newVertex = Vertex<Node>(newNode, City);
        _graph.addVertex(newVertex.getInfo());
    }

    for (int i = 0; i<stationinfo.size(); i=i+3){
        int id = stoi(stationinfo[i]);
        string code = cityinfo[i++];
        Node newNode = Node(Pumping_Station, id, code);
        Vertex<Node> newVertex = Vertex<Node>(newNode, Pumping_Station);
        _graph.addVertex(newVertex.getInfo());
    }

    for (int i = 0; i<reservoirinfo.size(); i=i+5){
        string reservoir = reservoirinfo[i];
        string municipality = reservoirinfo[i+1];
        int id = stoi(reservoirinfo[i+2]);
        string code = cityinfo[i+3];
        int maxdelivery = stoi(reservoirinfo[i+4]);
        Node newNode = Node(Water_Reservoir, reservoir, municipality, id, code, maxdelivery);
        Vertex<Node> newVertex = Vertex<Node>(newNode, Water_Reservoir);
        _graph.addVertex(newVertex.getInfo());
    }
}