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

    void setCode(string code);

    void setReservoir(string reservoir);

    void setMaxDelivery(int maxDelivery);

    void setCity(string city);

    void setDemand(int demand);

    void setPopulation(int population);

    void setMunicipality(string municipality);

    int getId();

    string getCode();

    string getReservoir();

    string getMunicipality();

    int getMaxDelivery();

    string getCity();

    int getDemand();

    int getPopulation();

    bool operator==(const Node &other) const;
};

#endif //DA_PROJ_1_NODE_H
