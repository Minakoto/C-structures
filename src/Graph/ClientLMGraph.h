#include "GraphForm.h"

template<typename DATA, typename NAME, typename WD>
class LGraph : public GraphForm<DATA, NAME, WD> {
private:
    class ENode {
    public:
        Edge<DATA, NAME, WD> *e;
        ENode *next;
        ENode(Edge<DATA, NAME, WD> *edge, ENode *nxt) : e(edge), next(nxt) {}
    };
    class VNode {
    public:
        int v_ind;
        ENode *eNode;
        VNode *next;
        VNode(int id, ENode *enode, VNode *nxt) : v_ind(id), eNode(enode), next(nxt) {}
    };
    vector<edge *> *edgeVector;
    VNode *list;
    unsigned size;
    bool directed;
    Edge<DATA, NAME, WD> *insert(vertex *v1, vertex *v2);
public:
    using vertex = Vertex<DATA, NAME>;
    using edge = Edge<DATA, NAME, WD>;
    vector<vertex*> vertexVector;
    LGraph(unsigned sz, bool D);
    LGraph(LGraph &other);
    ~LGraph();
    bool hasEdge(int i, int j);
    edge *insertE(vertex *v1, vertex *v2);
    bool deleteE(edge *e);
    edge *getEdge(int v1, int v2);
    edge *getEdge(vertex *v1, vertex *v2);
    void print();
    bool deleteV(int v);
    void insertV(int v);
    void setDirected(bool d);
    vector<vertex*>& getVertexVector();
    vector<edge*>* getEdgeVector();
    vector<edge*>* getEdgeVector(int v);
};

template<typename DATA, typename NAME, typename WD>
class MGraph : public GraphForm<DATA, NAME, WD> {
private:
    vector<vector<Edge<DATA, NAME, WD> *>> matrix;
    vector<edge *> *edgeVector;
    unsigned size;
    bool directed;
public:
    using vertex = Vertex<DATA, NAME>;
    using edge = Edge<DATA, NAME, WD>;
    vector<vertex *> vertexVector;
    MGraph(unsigned _size, bool directed);
    MGraph(MGraph &G);
    ~MGraph();
    bool hasEdge(int i, int j);
    edge *insertE(vertex *v1, vertex *v2);
    bool deleteE(edge *e);
    edge *getEdge(int v1, int v2);
    edge *getEdge(vertex *v1, vertex *v2);
    void print();
    void setDirected(bool d);
    bool deleteV(int v);
    void insertV(int v);
    vector<vertex*>& getVertexVector();
    vector<edge*>* getEdgeVector();
    vector<edge*>* getEdgeVector(int v);
};