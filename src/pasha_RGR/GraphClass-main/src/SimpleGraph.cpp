#include "SimpleGraph.h"

template<typename DATA, typename NAME, typename WEIGHT>
SimpleGraph<DATA, NAME, WEIGHT>::SimpleGraph() {
    VCount = 0;
    ECount = 0;
    D = false;
    dense = false;
    graphForm = new LGraph<DATA, NAME, WEIGHT>(VCount, D);
}

template<typename DATA, typename NAME, typename WEIGHT>
SimpleGraph<DATA, NAME, WEIGHT>::SimpleGraph(int _VCount, bool _D, bool _F) {
    VCount = _VCount;
    ECount = 0;
    D = _D;
    dense = _F;

    if (dense == LGraphType)
        graphForm = new LGraph<DATA, NAME, WEIGHT>(VCount, D);
    else
        graphForm = new MGraph<DATA, NAME, WEIGHT>(VCount, D);

    for (int i = 0; i < VCount; ++i) {
        graphForm->getVertexVector().push_back(new VertexT());
        graphForm->getVertexVector()[i]->setName(to_string(i));
        graphForm->getVertexVector()[i]->setInd(i);
        graphForm->getVertexVector()[i]->setData(i+10);
    }
}

template<typename DATA, typename NAME, typename WEIGHT>
SimpleGraph<DATA, NAME, WEIGHT>::SimpleGraph(int _VCount, int _ECount, bool _D, bool _F) {
    VCount = _VCount;
    ECount = _ECount;
    D = _D;
    dense = _F;

    if (dense == LGraphType)
        graphForm = new LGraph<DATA, NAME, WEIGHT>(VCount, D);
    else
        graphForm = new MGraph<DATA, NAME, WEIGHT>(VCount, D);

    for (int i = 0; i < VCount; ++i) {
        graphForm->getVertexVector().push_back(new VertexT());
        graphForm->getVertexVector()[i]->setName(to_string(i));
        graphForm->getVertexVector()[i]->setInd(i);
        graphForm->getVertexVector()[i]->setData(i+10);
    }
    if (ECount <= 0) return;
    if (D) {
        if (ECount > VCount * (VCount - 1))
            ECount = VCount * (VCount - 1);
        srand(time(0));
    } else {
        if (ECount > (VCount * (VCount - 1)) / 2)
            ECount = (VCount * (VCount - 1)) / 2;
    }
    int v1, v2;
    for (int i = 0; i < ECount; ++i) {

        v1 = rand() % VCount;
        v2 = rand() % VCount;
        if (v1 == v2)
            continue;
        if (graphForm->hasEdge(v1, v2))
            continue;
        if (!graphForm->hasEdge(v1, v2))
            graphForm->insertE(graphForm->getVertexVector()[v1], graphForm->getVertexVector()[v2]);
    }
}

template<typename DATA, typename NAME, typename WEIGHT>
SimpleGraph<DATA, NAME, WEIGHT>::SimpleGraph(SimpleGraph &G) {
    VCount = G.VCount;
    ECount = G.ECount;
    D = G.D;
    dense = G.dense;
    if (dense == LGraphType)
        graphForm = new LGraph<DATA, NAME, WEIGHT>(
                reinterpret_cast<LGraph<int, basic_string<char>, int> &>(G.graphForm));
    else
        graphForm = new MGraph<DATA, NAME, WEIGHT>(
                reinterpret_cast<MGraph<int, basic_string<char>, int> &>(G.graphForm));
}

template<typename DATA, typename NAME, typename WEIGHT>
SimpleGraph<DATA, NAME, WEIGHT>::~SimpleGraph() {
    delete graphForm;
}


template<typename DATA, typename NAME, typename WEIGHT>
bool SimpleGraph<DATA, NAME, WEIGHT>::deleteV(VertexT *v) {
    for (int i = 0; i < VCount; ++i) {
        if (graphForm->getVertexVector()[i]->getInd() == v->getInd()) {
            delete graphForm->getVertexVector()[i];
            for (int j = i; j < VCount - 1; ++j) {
                graphForm->getVertexVector()[j] = graphForm->getVertexVector()[j + 1];
            }
            graphForm->deleteV(v->getInd());
            VCount--;
            graphForm->getVertexVector().resize(VCount);
            return true;
        }
    }
    return false;
}

template<typename DATA, typename NAME, typename WEIGHT>
Vertex<DATA, NAME> *SimpleGraph<DATA, NAME, WEIGHT>::insertV() {
    auto *v = new Vertex<DATA, NAME>;
    VCount++;
    v->setInd(VCount - 1);
    graphForm->getVertexVector().push_back(v);
    graphForm->insertV(VCount - 1);
    return v;
}

template<typename DATA, typename NAME, typename WEIGHT>
Vertex<DATA, NAME> *SimpleGraph<DATA, NAME, WEIGHT>::insertV(NAME name) {
    auto *v = new Vertex<DATA, NAME>;
    VCount++;
    v->setName(name);
    v->setInd(VCount - 1);
    graphForm->getVertexVector().push_back(v);
    graphForm->insertV(VCount - 1);
    return v;
}

template<typename DATA, typename NAME, typename WEIGHT>
void SimpleGraph<DATA, NAME, WEIGHT>::switchForm(GraphForm<DATA, NAME, WEIGHT> *newForm) {
    // Copy vertices and their data
    for (int i = 0; i < graphForm->getVertexVector().size(); ++i) {
        VertexT* oldVertex = graphForm->getVertexVector()[i];
        // Create new vertex with same data
        VertexT* newVertex = new VertexT(*oldVertex);  // Copy construct vertex
        newForm->getVertexVector().push_back(newVertex);
        newForm->insertV(newVertex->getInd());
    }
    
    // Copy edges using vertices from new form
    for (auto it = eBegin(); it != eEnd(); it++) {
        int v1Idx = (*it)->getV1()->getInd();
        int v2Idx = (*it)->getV2()->getInd();
        newForm->insertE(newForm->getVertexVector()[v1Idx], 
                        newForm->getVertexVector()[v2Idx]);
    }
    
    delete graphForm;
    graphForm = newForm;
}

template<typename DATA, typename NAME, typename WEIGHT>
void SimpleGraph<DATA, NAME, WEIGHT>::toMatrixGraph() {
    if (dense == MGraphType) return;
    auto newForm = new MGraph<DATA, NAME, WEIGHT>(VCount, D);
    switchForm(newForm);
    dense = MGraphType;
}

template<typename DATA, typename NAME, typename WEIGHT>
void SimpleGraph<DATA, NAME, WEIGHT>::toListGraph() {
    if (dense == LGraphType)return;
    auto newForm = new LGraph<DATA, NAME, WEIGHT>(VCount, DGraphType);
    switchForm(newForm);
    newForm->setDirected(D);
    dense = LGraphType;
}

template<typename DATA, typename NAME, typename WEIGHT>
int SimpleGraph<DATA, NAME, WEIGHT>::getK() {
    int K;
    if (D)
        K = ECount / (VCount * (VCount - 1));
    else
        K = VCount * (VCount - 1) / 2;
    return K;
}

template<typename DATA, typename NAME, typename WEIGHT>
bool SimpleGraph<DATA, NAME, WEIGHT>::isDense() {
    return dense;
}

template<typename DATA, typename NAME, typename WEIGHT>
bool SimpleGraph<DATA, NAME, WEIGHT>::isDirected() {
    return D;
}

template<typename DATA, typename NAME, typename WEIGHT>
int SimpleGraph<DATA, NAME, WEIGHT>::getE() {
    return ECount;
}

template<typename DATA, typename NAME, typename WEIGHT>
int SimpleGraph<DATA, NAME, WEIGHT>::getV() {
    return VCount;
}


template<typename DATA, typename NAME, typename WEIGHT>
Edge<DATA, NAME, WEIGHT> *SimpleGraph<DATA, NAME, WEIGHT>::getEdge(VertexT *v1, VertexT *v2) {
    return graphForm->getEdge(v1, v2);
}

template<typename DATA, typename NAME, typename WEIGHT>
Edge<DATA, NAME, WEIGHT> *SimpleGraph<DATA, NAME, WEIGHT>::getEdge(int v1, int v2) {
    return graphForm->getEdge(v1, v2);
}

template<typename DATA, typename NAME, typename WEIGHT>
bool SimpleGraph<DATA, NAME, WEIGHT>::deleteE(EdgeT *e) {
    return graphForm->deleteE(e);
}

template<typename DATA, typename NAME, typename WEIGHT>
Edge<DATA, NAME, WEIGHT> *SimpleGraph<DATA, NAME, WEIGHT>::insertE(VertexT *i, VertexT *j) {
    return graphForm->insertE(i, j);
}

template<typename DATA, typename NAME, typename WEIGHT>
Edge<DATA, NAME, WEIGHT> *SimpleGraph<DATA, NAME, WEIGHT>::insertE(VertexT *i, VertexT *j, int _w) {
    return graphForm->insertE(i, j, _w);
}

template<typename DATA, typename NAME, typename WEIGHT>
void SimpleGraph<DATA, NAME, WEIGHT>::printGraph() {
    graphForm->print();
}

template<typename DATA, typename NAME, typename WEIGHT>
EdgeIterator<DATA, NAME, WEIGHT> SimpleGraph<DATA, NAME, WEIGHT>::eEnd() {
    return EdgeIterator<DATA, NAME, WEIGHT>(nullptr, -1);
}

template<typename DATA, typename NAME, typename WEIGHT>
EdgeIterator<DATA, NAME, WEIGHT> SimpleGraph<DATA, NAME, WEIGHT>::eBegin() {
    return EdgeIterator<DATA, NAME, WEIGHT>(graphForm->getEdgeVector(), 0);
}

template<typename DATA, typename NAME, typename WEIGHT>
VertexIterator<DATA, NAME, WEIGHT> SimpleGraph<DATA, NAME, WEIGHT>::vEnd() {
    return VertexIterator<DATA, NAME, WEIGHT>(graphForm->getVertexVector(), -1);
}

template<typename DATA, typename NAME, typename WEIGHT>
VertexIterator<DATA, NAME, WEIGHT> SimpleGraph<DATA, NAME, WEIGHT>::vBegin() {
    return VertexIterator<DATA, NAME, WEIGHT>(graphForm->getVertexVector(), 0);
}

template<typename DATA, typename NAME, typename WEIGHT>
EdgeIterator<DATA, NAME, WEIGHT> SimpleGraph<DATA, NAME, WEIGHT>::adjEEnd(int v) {
    return EdgeIterator<DATA, NAME, WEIGHT>(nullptr, -1);
}

template<typename DATA, typename NAME, typename WEIGHT>
EdgeIterator<DATA, NAME, WEIGHT> SimpleGraph<DATA, NAME, WEIGHT>::adjEBegin(int v) {
    return EdgeIterator<DATA, NAME, WEIGHT>(graphForm->getEdgeVector(v), 0);
}

