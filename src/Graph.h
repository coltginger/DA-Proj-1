/*
 * Graph.h
 */
#ifndef GRAPH_H_
#define GRAPH_H_

#include <cstddef>
#include <vector>
#include <queue>
#include <stack>
#include <list>
#include <string>

using namespace std;

template <class T> class Edge;
template <class T> class Graph;
template <class T> class Vertex;


/****************** Provided structures  ********************/

enum station_type{
    Water_Reservoir,
    Pumping_Station,
    City,
    Super_Node
};

/************************* Vertex  **************************/

template <class T>
class Vertex {

    T info;                // contents
    vector<Edge<T> *> incoming; //list of incoming edges
    vector<Edge<T> *> adj;  // list of outgoing edges
    bool visited;          // auxiliary field
    bool processing;       // auxiliary field
    int indegree;          // auxiliary field
    int num;               // auxiliary field
    int low;               // auxiliary field
    station_type type;     // auxiliary field
    Edge<T> *path = nullptr;

public:
    Vertex(T in, station_type newType);
    T getInfo() const;
    void setInfo(T in);
    bool isVisited() const;
    void setVisited(bool v);
    bool isProcessing() const;
    void setProcessing(bool p);

    vector<Edge<T> *> getIncoming() const;
    vector<Edge<T> *> getAdj();
    void setAdj(const vector<Edge<T>> &adj);
    Edge<T> * addEdge(Vertex<T> *dest, double w);
    //void addEdge(Vertex<T> *dest, double w);
    bool removeEdgeTo(Vertex<T> *d);
    bool removeEdgeFrom(Vertex<T> *d);
    int getIndegree() const;
    void setIndegree(int indegree);

    int getNum() const;
    void setNum(int num);

    int getLow() const;
    void setLow(int low);

    void setType(station_type newType);
    station_type getType();

    void setPath(Edge<T> *path);
    Edge<T>* getPath();

    friend class Graph<T>;
};

/********************** Edge  ****************************/

template <class T>
class Edge {
    Vertex<T> *orig;       // origin vertex
    Vertex<T> *dest;      // destination vertex
    int weight;         // edge weight
    int flow;
    int baseWeight;
    Edge<T> *reverse = NULL;

public:
    Edge(Vertex<T> *dest, int w);
    Edge(Vertex<T> *orig, Vertex<T> *dest, int w);

    Vertex<T> *getOrig() const;
    Vertex<T> *getDest() const;
    Edge<T> *getReverse() const;
    void setOrig(Vertex<T> *orig);
    void setDest(Vertex<T> *dest);
    void setReverse(Edge<T> *reverse);
    int getWeight() const;
    void setWeight(int weight);
    int getBaseWeight() const;
    void setBaseWeight(int weight);
    int getFlow() const;
    void setFlow(int flow);
    void addFlow(int pathflow);
    float flowRatio() const;


    friend class Graph<T>;
    friend class Vertex<T>;
};

/********************** Graph  ****************************/

template <class T>
class Graph {

    vector<Vertex<T> *> vertexSet;      // vertex set

    void dfsVisit(Vertex<T> *v,  vector<T> & res) const;
    bool dfsIsDAG(Vertex<T> *v) const;
public:
    vector<Vertex<T> *> getVertexSet() const;
    int getNumVertex() const;
    Vertex<T> *findVertex(const T &in) const;
    bool addVertex(const T &in, const station_type &type);
    bool removeVertex(const T &in);
    bool addEdge(const T &sourc, const T &dest, double w);
    bool removeEdge(const T &sourc, const T &dest);
    bool addBidirectionalEdge(const T &sourc, const T &dest, double w);

    vector<T> dfs() const;
    vector<T> dfs(const T & source) const;
    vector<T> bfs(const T &source) const;
    vector<T> topsort() const;
    bool isDAG() const;

};

/****************** Provided constructors and functions ********************/

template <class T>
Vertex<T>::Vertex(T in, station_type newType): info(in), type(newType) {}


template <class T>
Edge<T>::Edge(Vertex<T> *d, int w) {
    dest = d;
    weight = w;
    baseWeight = w;
    flow = 0;
}

template <class T>
Edge<T>::Edge(Vertex<T> *o, Vertex<T> *d, int w) {
    orig = o;
    dest = d;
    weight = w;
    baseWeight = w;
    flow = 0;
}

template <class T>
int Graph<T>::getNumVertex() const {
    return vertexSet.size();
}

template <class T>
vector<Vertex<T> * > Graph<T>::getVertexSet() const {
    return vertexSet;
}

template<class T>
T Vertex<T>::getInfo() const {
    return info;
}

template<class T>
void Vertex<T>::setInfo(T in) {
    Vertex::info = in;
}

template<class T>
bool Vertex<T>::isProcessing() const {
    return processing;
}

template<class T>
void Vertex<T>::setProcessing(bool p) {
    Vertex::processing = p;
}

template<class T>
Vertex<T> *Edge<T>::getOrig() const {
    return orig;
}

template<class T>
void Edge<T>::setOrig(Vertex<T> *o) {
    Edge::orig = o;
}

template<class T>
Vertex<T> *Edge<T>::getDest() const{
    return dest;
}

template<class T>
void Edge<T>::setDest(Vertex<T> *d) {
    Edge::dest = d;
}

template<class T>
Edge<T> *Edge<T>::getReverse() const { return reverse;}

template<class T>
void Edge<T>::setReverse(Edge<T> *rev) {Edge::reverse = rev;}

template<class T>
int Edge<T>::getWeight() const {
    return weight;
}

template<class T>
void Edge<T>::setWeight(int w) {
    Edge::weight = w;
}

template<class T>
int Edge<T>::getBaseWeight() const {
    return baseWeight;
}

template<class T>
void Edge<T>::setBaseWeight(int w) {
    Edge::baseWeight = w;
}

template<class T>
int Edge<T>::getFlow() const {
    return flow;
}

template<class T>
void Edge<T>::setFlow(int f) {
    Edge::flow = f;
}

template<class T>
void Edge<T>::addFlow(int pathflow) {
    Edge::flow += pathflow;
}

template<class T>
float Edge<T>::flowRatio() const {
    return (float)flow / (float)baseWeight;
}

/*
 * Auxiliary function to find a vertex with a given content.
 */
template <class T>
Vertex<T> * Graph<T>::findVertex(const T &in) const {
    for (auto v : vertexSet)
        if (v->info == in)
            return v;
    return NULL;
}

template <class T>
bool Vertex<T>::isVisited() const {
    return visited;
}

template<class T>
int Vertex<T>::getIndegree() const {
    return indegree;
}

template<class T>
void Vertex<T>::setIndegree(int indeg) {
    Vertex::indegree = indeg;
}

template<class T>
int Vertex<T>::getNum() const {
    return num;
}

template<class T>
void Vertex<T>::setNum(int n) {
    Vertex::num = n;
}

template<class T>
int Vertex<T>::getLow() const {
    return low;
}

template<class T>
void Vertex<T>::setLow(int l) {
    Vertex::low = l;
}

template<class T>
void Vertex<T>::setType(station_type newType) {
    Vertex::type = newType;
}

template<class T>
station_type Vertex<T>::getType() {
    return type;
}

template<class T>
void Vertex<T>::setPath(Edge<T>* path){
    Vertex::path = path;
}

template<class T>
Edge<T>* Vertex<T>::getPath() {
    return path;
}


template <class T>
void Vertex<T>::setVisited(bool v) {
    Vertex::visited = v;
}

template<class T>
vector<Edge<T> *> Vertex<T>::getIncoming() const {
    return incoming;
}


template<class T>
vector<Edge<T>*> Vertex<T>::getAdj() {
    return adj;
}

template <class T>
void Vertex<T>::setAdj(const vector<Edge<T>> &adj) {
    Vertex::adj = adj;
}


/*
 *  Adds a vertex with a given content or info (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already exists.
 */
template <class T>
bool Graph<T>::addVertex(const T &in, const station_type &type) {
    if (findVertex(in) != NULL)
        return false;
    vertexSet.push_back(new Vertex<T>(in, type));
    return true;
}

/*
 * Adds an edge to a graph (this), given the contents of the source and
 * destination vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */
template <class T>
bool Graph<T>::addEdge(const T &sourc, const T &dest, double w) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == NULL || v2 == NULL)
        return false;
    v1->addEdge(v2,w);
    return true;
}

/*
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination vertex (d) and edge weight (w).
*/
template <class T>
Edge<T> *Vertex<T>::addEdge(Vertex<T> *d, double w) {
    auto newEdge = new Edge<T>(this, d, w);
    adj.push_back(newEdge);
    d->incoming.push_back(newEdge);
    return newEdge;
}

template <class T>
bool Graph<T>::addBidirectionalEdge(const T &sourc, const T &dest, double w) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == NULL || v2 == NULL)
        return false;
    auto e1 = v1->addEdge(v2, w);
    auto e2 = v2->addEdge(v1, w);
    e1->setReverse(e2);
    e2->setReverse(e1);
    return true;
}

/*
 * Removes an edge from a graph (this).
 * The edge is identified by the source (sourc) and destination (dest) contents.
 * Returns true if successful, and false if such edge does not exist.
 */
template <class T>
bool Graph<T>::removeEdge(const T &sourc, const T &dest) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == NULL || v2 == NULL)
        return false;
    return (v1->removeEdgeTo(v2) && v2->removeEdgeFrom(v1));
}

/*
 * Auxiliary function to remove an outgoing edge (with a given destination (d))
 * from a vertex (this).
 * Returns true if successful, and false if such edge does not exist.
 */
template <class T>
bool Vertex<T>::removeEdgeTo(Vertex<T> *d) {
    for (auto it = adj.begin(); it != adj.end(); it++)
        if ((*it)->dest == d) {
            adj.erase(it);
            return true;
        }
    return false;
}
/*
 *  Auxiliary function to remove an incoming edge (with a given origin (o))
 *  Time complexity is O(n) where n is the size of the incoming vector
 *  from a vertex (this)
 *  Returns true if successful, and false if such edge does not exist
 */
template <class T>
bool Vertex<T>::removeEdgeFrom(Vertex<T> *o) {
    for (auto it = incoming.begin(); it != incoming.end(); it++)
        if ((*it)->orig == o) {
            incoming.erase(it);
            return true;
        }
    return false;
}



/*
 *  Removes a vertex with a given content (in) from a graph (this), and
 *  all outgoing and incoming edges.
 *  Returns true if successful, and false if such vertex does not exist.
 */
template <class T>
bool Graph<T>::removeVertex(const T &in) {
    for (auto it = vertexSet.begin(); it != vertexSet.end(); it++)
        if ((*it)->info  == in) {
            auto v = *it;
            vertexSet.erase(it);
            for (auto u : vertexSet)
                u->removeEdgeTo(v);
            delete v;
            return true;
        }
    return false;
}


/****************** DFS ********************/
/*
 * Performs a depth-first search (dfs) traversal in a graph (this).
 * Returns a vector with the contents of the vertices by dfs order.
 * Follows the algorithm described in theoretical classes.
 */
template <class T>
vector<T> Graph<T>::dfs() const {
    vector<T> res;
    for (auto v : vertexSet)
        v->visited = false;
    for (auto v : vertexSet)
        if (! v->visited)
            dfsVisit(v, res);
    return res;
}

/*
 * Auxiliary function that visits a vertex (v) and its adjacent, recursively.
 * Updates a parameter with the list of visited node contents.
 */
template <class T>
void Graph<T>::dfsVisit(Vertex<T> *v, vector<T> & res) const {
    v->visited = true;
    res.push_back(v->info);
    for (auto & e : v->adj) {
        auto w = e.dest;
        if ( ! w->visited)
            dfsVisit(w, res);
    }
}


/****************** DFS ********************/
/*
 * Performs a depth-first search (dfs) in a graph (this).
 * Returns a vector with the contents of the vertices by dfs order,
 * from the source node.
 */
template <class T>
vector<T> Graph<T>::dfs(const T & source) const {
    vector<T> res;
    auto s = findVertex(source, City);
    if (s == nullptr)
        return res;

    for (auto v : vertexSet)
        v->visited = false;

    dfsVisit(s, res);
    return res;
}


/****************** BFS ********************/
/*
 * Performs a breadth-first search (bfs) in a graph (this), starting
 * from the vertex with the given source contents (source).
 * Returns a vector with the contents of the vertices by bfs order.
 */
template <class T>
vector<T> Graph<T>::bfs(const T & source) const {
    vector<T> res;
    auto s = findVertex(source, City);
    if (s == NULL)
        return res;
    queue<Vertex<T> *> q;
    for (auto v : vertexSet)
        v->visited = false;
    q.push(s);
    s->visited = true;
    while (!q.empty()) {
        auto v = q.front();
        q.pop();
        res.push_back(v->info);
        for (auto & e : v->adj) {
            auto w = e.dest;
            if ( ! w->visited ) {
                q.push(w);
                w->visited = true;
            }
        }
    }
    return res;
}


/****************** isDAG  ********************/
/*
 * Performs a depth-first search in a graph (this), to determine if the graph
 * is acyclic (acyclic directed graph or DAG).
 * During the search, a cycle is found if an edge connects to a vertex
 * that is being processed in the stack of recursive calls (see theoretical classes).
 * Returns true if the graph is acyclic, and false otherwise.
 */

template <class T>
bool Graph<T>::isDAG() const {
    for (auto v : vertexSet) {
        v->visited = false;
        v->processing = false;
    }
    for (auto v : vertexSet)
        if (! v->visited)
            if ( ! dfsIsDAG(v) )
                return false;
    return true;
}

/**
 * Auxiliary function that visits a vertex (v) and its adjacent, recursively.
 * Returns false (not acyclic) if an edge to a vertex in the stack is found.
 */
template <class T>
bool Graph<T>::dfsIsDAG(Vertex<T> *v) const {
    v->visited = true;
    v->processing = true;
    for (auto & e : v->adj) {
        auto w = e.dest;
        if (w->processing)
            return false;
        if (! w->visited)
            if (! dfsIsDAG(w))
                return false;
    }
    v->processing = false;
    return true;
}


/****************** toposort ********************/

template<class T>
vector<T> Graph<T>::topsort() const {
    vector<T> res;
    //Initialize for each test
    for (auto i : vertexSet){
        i->indegree = 0;
        i->visited = false;
    }

    //Assign indegrees for all vertexs
    for (auto i : vertexSet){
        for (auto j: i->adj){
            j.dest->indegree++;
        }
    }

    //Initialize queue with first nodes
    queue<Vertex<T> *> q;
    for (auto i : vertexSet){
        if (i->indegree == 0){
            q.push(i);
        }
    }

    //Append nodes to List
    while(!q.empty()){
        auto v = q.front();
        q.pop();
        for (auto j: v->adj){
            j.dest->indegree--;
            if (j.dest->indegree == 0){
                q.push(j.dest);
            }
        }
        res.push_back(v->info);
    }
    return res;
}

#endif /* GRAPH_H_ */