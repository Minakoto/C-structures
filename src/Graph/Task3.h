#include "Task2.h"
#include <limits>
#include <stdexcept>

template <typename DATA, typename NAME, typename WD>
class Task3 {
private:
    Graph<DATA, NAME, WD>* G;
    vector<vector<WD>> res;
    vector<vector<vector<int>>> paths;
    bool hasNegativeCycle;
    void Bellman_Ford() {
        if (!G) return;
        const int V = G->V();
        const WD INF = numeric_limits<WD>::max();
        res.assign(V, vector<WD>(V, INF));
        paths.assign(V, vector<vector<int>>(V));
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (i == j) {
                    res[i][j] = 0;
                    paths[i][j] = {i};
                }
                if (G->getEdge(i, j)) paths[i][j] = {i, j};
            }
        }
        for (int src = 0; src < V; ++src) {
            res[src][src] = 0;
            for (int i = 1; i < V; ++i) {
                for (auto eIt = G->eBegin(); eIt != G->eEnd(); ++eIt) {
                    int u = (*eIt)->getV1()->getInd();
                    int v = (*eIt)->getV2()->getInd();
                    WD w = (*eIt)->getW();
                    if (res[src][u] != INF && res[src][v] > res[src][u] + w) {
                        res[src][v] = res[src][u] + w;
                        paths[src][v] = paths[src][u];
                        paths[src][v].push_back(v);
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
    Task3(Graph<DATA, NAME, WD>* g) : G(g), hasNegativeCycle(false) { restart(); }
    Task3(const Task3& other) : G(other.G), res(other.res), paths(other.paths), hasNegativeCycle(other.hasNegativeCycle) {}
    ~Task3() { 
        res.clear(); 
        paths.clear();
    }
    void set(Graph<DATA, NAME, WD>* g) {
        G = g;
        hasNegativeCycle = false;
        restart();
    }
    void restart() { Bellman_Ford(); }
    WD getDistance(int from, int to) const {
        if (hasNegativeCycle) throw runtime_error("Graph contains negative cycle");
        if (from < 0 || to < 0 || from >= G->V() || to >= G->V())
            throw "Invalid index";
        return res[from][to];
    }
    vector<int> getPath(int from, int to) const {
        if (hasNegativeCycle) throw runtime_error("Graph contains negative cycle");
        if (from < 0 || to < 0 || from >= G->V() || to >= G->V())
            throw runtime_error("Invalid vertex indices");
        return paths[from][to];
    }
    struct PathInfo {
        vector<int> path;
        WD distance;
    };
    vector<vector<PathInfo>> getAllPaths() const {
        if (hasNegativeCycle) throw "Graph contains negative cycle";
        const int V = G->V();
        vector<vector<PathInfo>> allPaths(V, vector<PathInfo>(V));
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                allPaths[i][j].path = paths[i][j];
                allPaths[i][j].distance = res[i][j];
            }
        }   
        return allPaths;
    }
    vector<vector<PathInfo>> result() const {
        if (hasNegativeCycle) throw "Graph contains negative cycle";
        return getAllPaths();
    }
    bool containsNegativeCycle() const {
        return hasNegativeCycle;
    }
};
