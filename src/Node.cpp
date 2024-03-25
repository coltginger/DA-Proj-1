#include "Node.h"

Node::Node(station_type type) {
    _type = type;
    _id = 0;
    _code = "";
    _reservoir = "";
    _municipality = "";
    _maxDelivery = 0;
    _city = "";
    _demand = 0;
    _population = 0;
}

void Node::setId(int id) {_id = id;}
void Node::setCode(string code) {_code = code;}
void Node::setReservoir(string reservoir) {_reservoir = reservoir;}
void Node::setMaxDelivery(int maxDelivery) {_maxDelivery = maxDelivery;}
void Node::setCity(string city) {_city = city;}
void Node::setDemand(int demand) {_demand = demand;}
void Node::setPopulation(int population) {_population = population;};
void Node::setMunicipality(std::string municipality) {_municipality = municipality;};

station_type Node::getType(){    return _type;}
int Node::getId(){ return _id;}
string Node::getCode(){    return _code;}
string Node::getReservoir(){    return _reservoir;}
string Node::getMunicipality(){    return _municipality;}
int Node::getMaxDelivery(){    return _maxDelivery;}
string Node::getCity(){    return _city;}
int Node::getDemand() {    return _demand;}
int Node::getPopulation() {    return _population;};

bool Node::operator==(const Node &other) const {
    return _type == other._type &&
            _id == other._id &&
           _code == other._code &&
           _reservoir == other._reservoir &&
           _municipality == other._municipality &&
           _maxDelivery == other._maxDelivery &&
           _city == other._city &&
           _demand == other._demand &&
           _population == other._population;
}