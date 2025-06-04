#include <queue>
#include <vector>
#include <limits>
#include "Graph.h"
using namespace std;

template<typename DATA, typename NAME, typename WD>
class Task2 {
    private:
    Graph<DATA, NAME, WD> *G;
    vector<vector<int>> res;

void BFS(Vertex<DATA, NAME>* start) {
    if (!G->V()) return;
    const int V = G->V();
    vector<bool> visited(V, false);
    vector<int> rt(V, -1);
    queue<Vertex<DATA, NAME>*> q;
    int startId = start->getInd();
    visited[startId] = true;
    rt[startId] = 0;
    q.push(start);
    while (!q.empty()) {
        Vertex<DATA, NAME>* current = q.front();
        q.pop();
        int currentId = current->getInd();

        auto adjIt = G->adjEBegin(currentId);
        auto adjEnd = G->adjEEnd(currentId);
        
        for (; adjIt != adjEnd; ++adjIt) {
            Vertex<DATA, NAME>* neighbor = (*adjIt)->getV2();
            int neighborId = neighbor->getInd();
            if (!visited[neighborId]) {
                visited[neighborId] = true;
                rt[neighborId] = rt[currentId] + 1;
                q.push(neighbor);
            }
        }
    }
    res.push_back(rt);
    
}

public:
    Task2(Graph<DATA, NAME, WD> *g) : G(g) { 
        restart();
    }
    Task2(Task2 &o) : G(o.G) { restart(); } 
    ~Task2() {}
    void set(Graph<DATA, NAME, WD> *g) { G = g; }
    void restart() {
        for(auto it = G->vBegin(); it != G->vEnd(); ++it) BFS(*it);
    }
    vector<vector<int>> result() {

        return res;
    }
};
