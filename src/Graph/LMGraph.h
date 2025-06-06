#include "GraphForm.h"

template<typename DATA, typename NAME, typename WD>
class LGraph : public GraphForm<DATA, NAME, WD> {
public:
    using vertex = Vertex<DATA, NAME>;
    using edge = Edge<DATA, NAME, WD>;
    vector<vertex*> vertexVector;
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
    Edge<DATA, NAME, WD> *insert(vertex *v1, vertex *v2) {
        VNode *vtmp = list;
        ENode *etmp;
        Edge<DATA, NAME, WD> *res;
        while (vtmp) {
            if (vtmp->v_ind == v1->getInd()) {
                etmp = vtmp->eNode;
                res = new Edge<DATA, NAME, WD>(v1, v2, 1);
                if (!etmp) {
                    vtmp->eNode = new ENode(res, nullptr);
                } else {
                    while (etmp->next) {
                        etmp = etmp->next;
                    }
                    etmp->next = new ENode(res, nullptr);
                }
                return res;
            }
            vtmp = vtmp->next;
        }
        return nullptr;
    }
    Edge<DATA, NAME, WD> *insert(vertex *v1, vertex *v2, WD w) {
        VNode *vtmp = list;
        ENode *etmp;
        Edge<DATA, NAME, WD> *res;
        while (vtmp) {
            if (vtmp->v_ind == v1->getInd()) {
                etmp = vtmp->eNode;
                res = new Edge<DATA, NAME, WD>(v1, v2, w);
                if (!etmp) {
                    vtmp->eNode = new ENode(res, nullptr);
                } else {
                    while (etmp->next) {
                        etmp = etmp->next;
                    }
                    etmp->next = new ENode(res, nullptr);
                }
                return res;
            }
            vtmp = vtmp->next;
        }
        return nullptr;
    }

public:
    LGraph(unsigned sz, bool D) : size(sz), directed(D) {
        list = new VNode(0, nullptr, nullptr);
        for (int i = 1; i < size; i++) {
            list = new VNode(i, nullptr, list);
        }
        edgeVector = new vector<Edge<DATA, NAME, WD> *>();
    }
    LGraph(LGraph &other) :size(other.size), directed(other.directed),
                        edgeVector(other.edgeVector), list(other.list) {}
    ~LGraph() {
        VNode *vtmp;
        ENode *elist, *etmp;
        while (list) {
            elist = list->eNode;
            while (elist) {
                etmp = elist->next;
                delete elist;
                elist = etmp;
            }
            vtmp = list->next;
            delete list;
            list = vtmp;
        }
        delete edgeVector;
    }
    bool hasEdge(int i, int j) {
        VNode *vtmp = list;
        ENode *etmp;
        Edge<DATA, NAME, WD> *e;
        while (vtmp) {
            etmp = vtmp->eNode;
            while (etmp) {
                e = etmp->e;
                if (e->getV1()->getInd() == i && e->getV2()->getInd() == j) return true;
                etmp = etmp->next;
            }
            vtmp = vtmp->next;
        }
        return false;
    }
    edge *insertE(vertex *v1, vertex *v2) {
        if (!directed) insert(v2, v1);
        Edge<DATA, NAME, WD> *res = insert(v1, v2);
        return res;
    }
    edge *insertE(vertex *v1, vertex *v2, WD w) {
        if (!directed) insert(v2, v1, w);
        Edge<DATA, NAME, WD> *res = insert(v1, v2, w);
        return res;
    }
    bool deleteE(vertex* v1, vertex* v2) {
        bool result = true;
        if(!directed) result &= delE(v2, v1);
        result &= delE(v1, v2);
        return result;
    }

    bool delE(vertex* v1, vertex* v2) {
        VNode *vtmp = list;
        ENode *etmp, *prev;
        while (vtmp) {
            prev = vtmp->eNode;
            etmp = vtmp->eNode;
            if (etmp && (etmp->e->getV1()->getInd() == v1->getInd() && etmp->e->getV2()->getInd() == v2->getInd())) {
                vtmp->eNode = etmp->next;
                delete etmp->e;
                delete etmp;
                return true;
            }
            if (etmp) etmp = etmp->next;
            while (etmp) {
                if (etmp && (etmp->e->getV1()->getInd() == v1->getInd() && etmp->e->getV2()->getInd() == v2->getInd())) {
                    prev->next = etmp->next;
                    delete etmp->e;
                    delete etmp;
                    return true;
                }
                prev = etmp;
                etmp = etmp->next;
            }
            vtmp = vtmp->next;
        }
        return false;
    }
    void print() {
        int i, j;
        vertex *v;
        VNode *vtmp, *prev;
        vtmp = prev = list;
        ENode *etmp, *edel;
        cout << "LIST" << endl;
        while (vtmp) {
            cout << "*" << vtmp->v_ind << "->";
            etmp = vtmp->eNode;
            while (etmp) {
                cout << etmp->e->getV2()->getInd()  << ":" << etmp->e->getW();
                etmp = etmp->next;
                if(etmp) cout << "->";
            }
            cout << endl;
            vtmp = vtmp->next;
        }
    }
    bool deleteV(int v) {
        VNode *vtmp, *prev;
        vtmp = prev = list;
        ENode *etmp, *edel;
        if (vtmp && vtmp->v_ind == v) {
            etmp = vtmp->eNode;
            while (etmp) {
                edel = etmp;
                etmp = etmp->next;
                delete edel;
            }
            list = vtmp->next;
            delete vtmp;
            size--;
            return true;
        }
        if (vtmp) vtmp = vtmp->next;
        while (vtmp) {
            if (vtmp->v_ind == v) {
                etmp = vtmp->eNode;
                while (etmp) {
                    edel = etmp;
                    etmp = etmp->next;
                    delete edel->e;
                    delete edel;
                }
                prev->next = vtmp->next;
                delete vtmp;
                size--;
                return true;
            }
            prev = prev->next;
            vtmp = vtmp->next;
        }
        return false;
    }
    void insertV(int v) {
        VNode *vtmp, *prev;
        vtmp = prev = list;
        ENode *etmp, *edel;
        if (!vtmp) {
            list = new VNode(v, nullptr, nullptr);
            return;
        }
        if (vtmp->v_ind == v) {
            return;
        }
        vtmp = vtmp->next;
        while (vtmp) {
            if (vtmp->v_ind == v) return;
            vtmp = vtmp->next;
            prev = prev->next;
        }
        prev->next = new VNode(v, nullptr, nullptr);
    }
    void setDirected(bool d) { directed = d; }
    Edge<DATA, NAME, WD>  *getEdge(int v1, int v2) {
        VNode *vtmp = list;
        ENode *etmp;
        Edge<DATA, NAME, WD> *e;
        while (vtmp) {
            etmp = vtmp->eNode;
            while (etmp && etmp->next) {
                e = etmp->next->e;
                if (e->getV1()->getInd() == v1 && e->getV2()->getInd() == v2) {
                    return e;
                }
                etmp = etmp->next;
            }
            vtmp = vtmp->next;
        }
        return nullptr;
    }

    vector<vertex*>& getVertexVector() { return vertexVector; }
    vector<edge*>* getEdgeVector() {
        edgeVector = new vector<Edge<DATA, NAME, WD> *>();
        VNode *vtmp = list;
        ENode *etmp;
        while (vtmp) {
            etmp = vtmp->eNode;
            while (etmp) {
                edgeVector->push_back(etmp->e);
                etmp = etmp->next;
            }
            vtmp = vtmp->next;
        }
        return edgeVector;
    }
    vector<edge*>* getEdgeVector(int v) {
        edgeVector = new vector<Edge<DATA, NAME, WD> *>();
        VNode *vtmp = list;
        ENode *etmp;
        while (vtmp) {
            if (vtmp->v_ind == v) {
                etmp = vtmp->eNode;
                while (etmp) {
                    edgeVector->push_back(etmp->e);
                    etmp = etmp->next;
                }
                break;
            }
            vtmp = vtmp->next;
        }
        return edgeVector;
    }
};

template<typename DATA, typename NAME, typename WD>
class MGraph : public GraphForm<DATA, NAME, WD> {
public:
    using vertex = Vertex<DATA, NAME>;
    using edge = Edge<DATA, NAME, WD>;
    vector<vertex *> vertexVector;
private:
    vector<vector<Edge<DATA, NAME, WD>*>> matrix;
    vector<edge*>* edgeVector;
    unsigned size;
    bool directed;
public:
    MGraph(unsigned sz, bool D) : size(sz), directed(D) {
        matrix.resize(size);
        for (int i = 0; i < size; i++) {
            matrix[i].resize(size);
            for (int j = 0; j < size; j++) matrix[i][j] = nullptr;
        }
        edgeVector = new vector<Edge<DATA, NAME, WD>*>();
    } 
    MGraph(MGraph &other): size(other.size), directed(other.directed) {
        matrix.resize(size);
        for (int i = 0; i < size; i++) {
            matrix[i].resize(size);
            for (int j = 0; j < size; j++) matrix[i][j] = other.matrix[i][j];
        }
        for (int i = 0; i < size; i++) vertexVector[i] = other.vertexVector[i];        
    }
    ~MGraph() {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) delete matrix[i][j];
        }
        delete edgeVector;
    }   
    bool hasEdge(int i, int j) {
        return matrix[i][j];
    }
    edge *insertE(vertex *v1, vertex *v2) {
        if (!directed)
            matrix[v2->getInd()][v1->getInd()] = new Edge<DATA, NAME, WD>(v2, v1, 1);
        return matrix[v1->getInd()][v2->getInd()] = new Edge<DATA, NAME, WD>(v1, v2, 1);
    }
    edge *insertE(vertex *v1, vertex *v2, WD w) {
        if (!directed)
            matrix[v2->getInd()][v1->getInd()] = new Edge<DATA, NAME, WD>(v2, v1, w);
        return matrix[v1->getInd()][v2->getInd()] = new Edge<DATA, NAME, WD>(v1, v2, w);
    }
    bool deleteE(vertex *v1, vertex *v2) {
        int i1 = v1->getInd();
        int i2 = v2->getInd();
        bool result = false;
        if (matrix[i1][i2]) {
            delete matrix[i1][i2];
            matrix[i1][i2] = nullptr;
            result = true;
        }
        else result = false;
        if(directed) return result;
        if (matrix[i2][i1]) {
            delete matrix[i2][i1];
            matrix[i2][i1] = nullptr;
            result = true;
        }
        else result = false;
        return result;
    }
    void print() {
        cout << "MATRIX" << endl;
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (matrix[i][j])
                    cout << matrix[i][j]->getW() << " ";
                else
                    cout << "0 ";
            }
            cout << endl;
        }
    }
    void setDirected(bool d) { directed = d; }
    bool deleteV(int v) {
        for (int i = 0; i < size; i++) {
            if (i == v) {
                for (int j = 0; j < size; j++) {
                    delete matrix[i][j];
                    matrix[i][j] = nullptr;
                }
                for (int j = 0; j < size; j++) {
                    if (j != i) {
                        delete matrix[j][i];
                        matrix[j][i] = nullptr;
                    }
                }
                return true;
            }
        }
        return false;
    }
    void insertV(int v) {
        if (v >= size) {
            matrix.resize(v + 1);
            for (int i = 0; i < v + 1; i++) {
                matrix[i].resize(v + 1);
                for (int j = size; j < v + 1; j++) matrix[i][j] = nullptr;
            }
            size++;
        }
    }
    edge *getEdge(int v1, int v2) { return matrix[v1][v2]; }
    vector<vertex*>& getVertexVector() { return vertexVector; }
    vector<edge*>* getEdgeVector() {
        edgeVector = new vector<Edge<DATA, NAME, WD>*>();
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (matrix[i][j]) edgeVector->push_back(matrix[i][j]);
            }
        }
        return edgeVector;
    }
    vector<edge*>* getEdgeVector(int v) {
        edgeVector = new vector<Edge<DATA, NAME, WD> *>();
        if (v < size)
            for (int i = 0; i < size; i++) {
                if (matrix[v][i]) edgeVector->push_back(matrix[v][i]);
            }
        return edgeVector;
    }
};