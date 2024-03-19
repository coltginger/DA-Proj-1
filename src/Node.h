#include <string>
using namespace std;

#ifndef DA_PROJ_1_NODE_H
#define DA_PROJ_1_NODE_H

enum station_type{
    Water_Reservoir,
    Pumping_Station,
    City
};

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
    Node();
    Node(station_type Water_Reservoir, string reservoir,string municipality, int id, string code, int maxDelivery); //Reservoir
    Node(station_type City, string city, int id, string code, int demand, int population); //Delivery City
    Node(station_type Pumping_Station, int id, string code); //Pumping_Station

    void setId(int id);
    void setCode(string code);
    void setReservoir(string reservoir);
    void setMaxDelivery(int maxDelivery);
    void setCity(string city);
    void setDemand(int demand);
    void setPopulation(int population);

    station_type getType();
    int getId();
    string getCode();
    string getReservoir();
    string getMunicipality();
    int getMaxDelivery();
    string getCity();
    int getDemand();
    int getPopulation();
};

#endif //DA_PROJ_1_NODE_H
