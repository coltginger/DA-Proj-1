#include <string>
#include <climits>

using namespace std;

#ifndef DA_PROJ_1_NODE_H
#define DA_PROJ_1_NODE_H

class Node {
private:
    int _id;
    string _code;
    string _reservoir;
    string _municipality;
    int _maxDelivery;
    string _city;
    int _demand;
    int _population;

public:
    Node();

    void setId(int id);
    int getId();
    void setCode(string code);
    string getCode();
    void setReservoir(string reservoir);
    string getReservoir();
    string getMunicipality();
    void setMaxDelivery(int maxDelivery);
    int getMaxDelivery();
    void setCity(string city);
    string getCity();
    void setDemand(int demand);
    int getDemand();
    void setPopulation(int population);
    int getPopulation();
    void setMunicipality(string municipality);

    bool operator==(const Node &other) const;
};

#endif //DA_PROJ_1_NODE_H
