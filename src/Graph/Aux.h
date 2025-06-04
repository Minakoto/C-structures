#include <string>
using namespace std;
template<typename DATA, typename NAME>
class Vertex {
private:
    NAME name;
    DATA data;
    int index;
public:
    Vertex() : data(0), index(0) {}
    Vertex(NAME nm) : name(nm), data(0), index(0) {}
    NAME getName() { return name; }
    void setName(NAME nm) { name = nm; }
    DATA getData() { return data; }
    void setData(int dt) { data = dt; }
    int getInd() { return index; }
    void setInd(int ind) { index = ind; }
};
template<typename DATA, typename NAME, typename WD>
class Edge {
private:
    Vertex<DATA, NAME> *v1;
    Vertex<DATA, NAME> *v2;
    WD w;
    DATA data;
    bool Weighted;
public:
    Edge(Vertex<DATA, NAME> *v1, Vertex<DATA, NAME> *v2) : v1(v1), v2(v2), Weighted(false) { data = v1->getInd()*10+v2->getInd(); }
    Edge(Vertex<DATA, NAME> *v1, Vertex<DATA, NAME> *v2, WD w) : v1(v1), v2(v2), w(w), Weighted(true) {
        data = v1->getInd()*10+v2->getInd(); 
    }
    // Edge(Vertex<DATA, NAME> *_v1, Vertex<DATA, NAME> *_v2, int _w, DATA _data);
    Vertex<DATA, NAME> *getV1() { return v1; }
    Vertex<DATA, NAME> *getV2() { return v2; }
    WD getW() { return w; }
    void setW(WD ww) { w = ww; }
    DATA getData() { return data; }
    void setData(DATA dt) { data = dt; }
    bool isWeighted() { return Weighted; }
};

