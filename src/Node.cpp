#include "Node.h"


Node::Node(station_type Water_Reservoir,string reservoir,string municipality, int id, string code, int maxDelivery) {
    _type = Water_Reservoir;
    _reservoir = reservoir;
    _municipality = municipality;
    _id = id;
    _code = code;
    _maxDelivery = maxDelivery;
}
Node::Node(station_type City,string city, int id, string code, int demand, int population){
    _type = City;
    _city = city;
    _id = id;
    _demand = demand;
    _population = population;
}
Node::Node(station_type Pumping_Station, int id, string code){
    _id = id;
    _code = code;
}

void Node::setId(int id) {_id = id;}
void Node::setCode(string code) {_code = code;}
void Node::setReservoir(string reservoir) {_reservoir = reservoir;}
void Node::setMaxDelivery(int maxDelivery) {_maxDelivery = maxDelivery;}
void Node::setCity(string city) {_city = city;}
void Node::setDemand(int demand) {_demand = demand;}
void Node::setPopulation(int population) {_population = population};

station_type Node::getType(){
    return _type;
}
int Node::getId(){ return _id;}
string Node::getCode(){    return _code;}
string Node::getReservoir(){    return _reservoir;}
string Node::getMunicipality(){    return _municipality;}
int Node::getMaxDelivery(){    return _maxDelivery;}
string Node::getCity(){    return _city;}
int Node::getDemand() {    return _demand;}
int Node::getPopulation() {    return _population;};