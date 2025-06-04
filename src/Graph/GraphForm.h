#ifndef GRAPHFORM_H
#define GRAPHFORM_H

#include "Aux.h"
#include <vector>
#include <iostream>
using namespace std;

template<typename DATA, typename NAME, typename WD>
class GraphForm {
public:
    using vertex = Vertex<DATA, NAME>;
    using edge = Edge<DATA, NAME, WD>;
    virtual bool hasEdge(int i, int j) = 0;
    virtual edge *getEdge(int v1, int v2) = 0;
    virtual edge *insertE(vertex *v1, vertex *v2) = 0;
    virtual edge *insertE(vertex *v1, vertex *v2, WD w) = 0;
    virtual bool deleteE(vertex *v1, vertex *v2) = 0;
    virtual void print() = 0;
    virtual bool deleteV(int v) = 0;
    virtual void setDirected(bool d) = 0;
    virtual void insertV(int v) = 0;
    virtual vector<edge*>* getEdgeVector() = 0;
    virtual vector<edge*>* getEdgeVector(int v) = 0;
    virtual vector<vertex*>& getVertexVector() = 0;
};
#endif //GRAPHFORM_H
