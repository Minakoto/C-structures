#include "LMGraph.h"
using namespace std;

#define LType false
#define MType true
#define DType true
#define NDType false

template<typename DATA, typename NAME, typename WD>
class Graph {
friend class VertexIterator;
friend class EdgeIterator;
private:
    void Transform(GraphForm<DATA, NAME, WD> *form) {
        for (int i = 0; i < graphForm->getVertexVector().size(); i++) {
            form->insertV(graphForm->getVertexVector()[i]->getInd());
        }
        int v1, v2;
        for (auto it = eBegin(); it != eEnd(); it++)
            (*it)->isWeighted() ? form->insertE((*it)->getV1(), (*it)->getV2(), (*it)->getW())
                : form->insertE((*it)->getV1(), (*it)->getV2());
        delete graphForm;
        graphForm = form;
    }
    int Vcnt;
    int Ecnt;
    bool isDirected;
    bool isDense;
public:
    using vertex = Vertex<DATA, NAME>;
    using edge = Edge<DATA, NAME, WD>;
    GraphForm<DATA, NAME, WD> *graphForm;
    Graph() : Vcnt(0), Ecnt(0), isDirected(false), isDense(false) {
        graphForm = new LGraph<DATA, NAME, WD>(Vcnt, isDirected);
    }
    Graph(int V, bool D, bool F) : Vcnt(V), Ecnt(0), isDirected(D), isDense(F) {
        if (isDense == LType) graphForm = new LGraph<DATA, NAME, WD> (Vcnt, isDirected);
        else graphForm = new MGraph<DATA, NAME, WD> (Vcnt, isDirected);
        for (int i = 0; i < Vcnt; i++) {
            graphForm->getVertexVector().push_back(new vertex());
            graphForm->getVertexVector()[i]->setName(to_string(i));
            graphForm->getVertexVector()[i]->setInd(i);
        }
    }
    Graph(int V, int E, bool D, bool F) : Vcnt(V), Ecnt(E), isDirected(D), isDense(F) {
        if (isDense == LType) graphForm = new LGraph<DATA, NAME, WD> (Vcnt, D);
        else graphForm = new MGraph<DATA, NAME, WD> (Vcnt, D);
        for (int i = 0; i < Vcnt; i++) {
            graphForm->getVertexVector().push_back(new vertex());
            graphForm->getVertexVector()[i]->setName(to_string(i));
            graphForm->getVertexVector()[i]->setInd(i);
        }
        if (Ecnt <= 0) return;
        if (isDirected) {
            if (Ecnt > Vcnt * (Vcnt - 1)) Ecnt = Vcnt * (Vcnt - 1);
            srand(time(0));
        } else {
            if (Ecnt > (Vcnt * (Vcnt - 1)) / 2) Ecnt = (Vcnt * (Vcnt - 1)) / 2;
        }
        int v1, v2;
        for (int i = 0; i < Ecnt; i++) {
            v1 = rand() % Vcnt;
            v2 = rand() % Vcnt;
            if (v1 == v2 || graphForm->hasEdge(v1, v2)) continue;
            graphForm->insertE(graphForm->getVertexVector()[v1], graphForm->getVertexVector()[v2]);
        }
    }
    Graph(Graph &other) : Vcnt(other.Vcnt), Ecnt(other.Ecnt), isDirected(other.isDirected), isDense(other.isDense) {
        if (isDense == LType) graphForm = new LGraph<DATA, NAME, WD>(
                    reinterpret_cast<LGraph<int, basic_string<char>, int> &>(other.graphForm));
        else graphForm = new MGraph<DATA, NAME, WD>(
                    reinterpret_cast<MGraph<int, basic_string<char>, int> &>(other.graphForm));
    }
    ~Graph() { delete graphForm; }

    int V() { return Vcnt; }
    int E() { return Ecnt; }
    bool Directed() { return isDirected; }
    bool Dense() { return isDense; }
    int K() { 
        int K;
        if (isDirected) K = Ecnt / (Vcnt * (Vcnt - 1));
        else K = Vcnt * (Vcnt - 1) / 2;
        return K;
    }
    void toListGraph() {
        if (isDense == LType) return;
        auto tmp = new LGraph<DATA, NAME, WD>(Vcnt, DType);
        Transform(tmp);
        tmp->setDirected(isDirected);
        isDense = LType;
    }
    void toMatrixGraph() {
        if (isDense == MType) return;
        auto tmp = new MGraph<DATA, NAME, WD>(Vcnt, isDirected);
        Transform(tmp);
        isDense = MType;
    }
    vertex *insertV() {
        auto *v = new Vertex<DATA, NAME>;
        Vcnt++;
        v->setInd(Vcnt - 1);
        graphForm->getVertexVector().push_back(v);
        graphForm->insertV(Vcnt - 1);
        return v;
    }
    vertex *insertV(NAME name) {
        auto *v = new Vertex<DATA, NAME>(name);
        Vcnt++;
        v->setInd(Vcnt - 1);
        graphForm->getVertexVector().push_back(v);
        graphForm->insertV(Vcnt - 1);
        return v;
    }
    bool deleteV(vertex *v) {
        for(int i = 0; i < Vcnt; i++) deleteE(graphForm->getVertexVector()[i], v);
        for (int i = 0; i < Vcnt; i++) {
            if (graphForm->getVertexVector()[i]->getInd() == v->getInd()) {
                if(isDirected) for(int j = 0; j < Vcnt; j++) deleteE(v, graphForm->getVertexVector()[j]);
                delete graphForm->getVertexVector()[i];
                for (int j = i; j < Vcnt - 1; ++j)
                    graphForm->getVertexVector()[j] = graphForm->getVertexVector()[j + 1];
                graphForm->deleteV(v->getInd());
                Vcnt--;
                graphForm->getVertexVector().resize(Vcnt);
                return true;
            }
        }
        return false;
    }
    edge *insertE(vertex *i, vertex *j) {
        Ecnt++;
        return graphForm->insertE(i, j);
    }
    edge *insertE(vertex *i, vertex *j, WD w) {
        Ecnt++;
        return graphForm->insertE(i, j, w);
    }
    bool deleteE(vertex* v1, vertex* v2) {
        bool res = graphForm->deleteE(v1, v2);
        if(res) Ecnt--;
        return res;
    }
    edge *getEdge(int v1, int v2) { return graphForm->getEdge(v1, v2); }
    void printGraph() { graphForm->print(); }
    class VertexIterator {
    private:
        vector<vertex*> vertexVector;
        int index;
    public:
        using referenceV = VertexIterator &;
        VertexIterator(vector<vertex*>& vertexVector, int ind) : vertexVector(vertexVector), index(ind) {
            if(vertexVector.size() <= 0) index = -1; 
        }
        Vertex<DATA, NAME>* operator*() const {
            if(index < 0 ) throw "Out of bounds";
            return vertexVector[index]; }
        friend bool operator==(const VertexIterator &a, const VertexIterator &b) { return a.index == b.index; };
        friend bool operator!=(const VertexIterator &a, const VertexIterator &b) { return a.index != b.index; };
        const referenceV &operator++() {
            index++;
            if (index == vertexVector.size()) index = -1;
            return *this;
        }
        const referenceV operator++(int) {
            index++;
            if (index == vertexVector.size()) index = -1;
            return *this;
        }
    };
    class EdgeIterator {
    private:
        vector<edge*>* edgeVector;
        int index;
    public:
        // using edge = Edge<DATA, NAME, WD>;
        using referenceE = EdgeIterator &;
        EdgeIterator(vector<edge*>* edgeVector, int ind) : edgeVector(edgeVector), index(ind) {
            if(!edgeVector || edgeVector->size() <= 0) index = -1;
        }
        Edge<DATA, NAME, WD>* operator*() const {
            if(index < 0 ) throw "Out of bounds";
            return (*edgeVector)[index];
        }
        friend bool operator==(const EdgeIterator& a, const EdgeIterator& b) { return a.index == b.index; };
        friend bool operator!=(const EdgeIterator& a, const EdgeIterator& b) { return a.index != b.index; };
        const referenceE& operator++() {
            index++;
            if (index == edgeVector->size()) index = -1;
            return *this;
        }
        const referenceE operator++(int) {
            index++;
            if (index == edgeVector->size()) index = -1;
            return *this;
        }
        int getSize() { return edgeVector->size(); };
        int getInd() { return index; }
    };
    VertexIterator vBegin() {
        return VertexIterator(graphForm->getVertexVector(), 0);
    }
    VertexIterator vEnd() {
        return VertexIterator(graphForm->getVertexVector(), -1);
    }
    EdgeIterator eBegin() {
        return EdgeIterator(graphForm->getEdgeVector(), 0);
    }
    EdgeIterator eEnd() {
        return EdgeIterator(nullptr, -1);
    }
    EdgeIterator adjEBegin(int v) {
        return EdgeIterator(graphForm->getEdgeVector(v), 0);
    }
    EdgeIterator adjEEnd(int v) {
        return EdgeIterator(nullptr, -1);
    }
};