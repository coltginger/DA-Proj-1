#include <string>
#include "Graph.h"
using namespace std;

#ifndef DA_PROJ_1_NODE_H
#define DA_PROJ_1_NODE_H

class Node {
private:
    station_type _type;
    int _id;
    string _code;
    string _reservoir;
    string _municipality;
    int _maxDelivery;
    string _city;
    int _demand;
    int _population;

public:
    Node(station_type type);

    void setId(int id);
    void setCode(string code);
    void setReservoir(string reservoir);
    void setMaxDelivery(int maxDelivery);
    void setCity(string city);
    void setDemand(int demand);
    void setPopulation(int population);
    void setMunicipality(string municipality);

    station_type getType();
    int getId();
    string getCode();
    string getReservoir();
    string getMunicipality();
    int getMaxDelivery();
    string getCity();
    int getDemand();
    int getPopulation();

    bool operator==(const Node& other) const;
};

#endif //DA_PROJ_1_NODE_H
