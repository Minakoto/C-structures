#include "Task2.h"
#include <limits>
#include <stdexcept>

template <typename DATA, typename NAME, typename WD>
class Task3 {
private:
    Graph<DATA, NAME, WD>* G;
    vector<vector<WD>> res;
    bool hasNegativeCycle;

    void Bellman_Ford() {
        if (!G) return;
        const int V = G->V();
        const WD INF = numeric_limits<WD>::max();
        res.assign(V, vector<WD>(V, INF));
        for (int src = 0; src < V; ++src) {
            res[src][src] = 0;
            for (int i = 1; i < V; ++i) {
                for (auto eIt = G->eBegin(); eIt != G->eEnd(); ++eIt) {
                    int u = (*eIt)->getV1()->getInd();
                    int v = (*eIt)->getV2()->getInd();
                    WD w = (*eIt)->getW();
                    if (res[src][u] != INF && res[src][v] > res[src][u] + w) {
                        res[src][v] = res[src][u] + w;
                    }
                }
            }
            for (auto eIt = G->eBegin(); eIt != G->eEnd(); ++eIt) {
                int u = (*eIt)->getV1()->getInd();
                int v = (*eIt)->getV2()->getInd();
                WD w = (*eIt)->getW();
                if (res[src][u] != INF && res[src][v] > res[src][u] + w) {
                    hasNegativeCycle = true;
                    return;
                }
            }
        }
    }
public:
    Task3(Graph<DATA, NAME, WD>* g) : G(g), hasNegativeCycle(false){
        restart();
    }
    Task3(const Task3& other) : G(other.G), res(other.res), hasNegativeCycle(other.hasNegativeCycle) {}
    ~Task3() { res.clear(); }
    void set(Graph<DATA, NAME, WD>* g) {
        G = g;
        hasNegativeCycle = false;
        restart();
    }

    void restart() {
        Bellman_Ford();
    }

    const vector<vector<WD>>& result() const {
        if (hasNegativeCycle) throw ("Граф содержит отрицательный цикл");
        return res;
    }

    bool containsNegativeCycle() const {
        return hasNegativeCycle;
    }
};
