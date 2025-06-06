// #include <queue>
// #include <vector>
// #include <limits>
// #include "Graph.h"
// using namespace std;

// template<typename DATA, typename NAME, typename WD>
// class Task2 {
//     private:
//     Graph<DATA, NAME, WD> *G;
//     vector<vector<int>> res;

// void BFS(Vertex<DATA, NAME>* start) {
//     if (!G->V()) return;
//     const int V = G->V();
//     vector<bool> visited(V, false);
//     vector<int> rt(V, -1);
//     queue<Vertex<DATA, NAME>*> q;
//     int startId = start->getInd();
//     visited[startId] = true;
//     rt[startId] = 0;
//     q.push(start);
//     while (!q.empty()) {
//         Vertex<DATA, NAME>* current = q.front();
//         q.pop();
//         int currentId = current->getInd();

//         auto adjIt = G->adjEBegin(currentId);
//         auto adjEnd = G->adjEEnd(currentId);
        
//         for (; adjIt != adjEnd; ++adjIt) {
//             Vertex<DATA, NAME>* neighbor = (*adjIt)->getV2();
//             int neighborId = neighbor->getInd();
//             if (!visited[neighborId]) {
//                 visited[neighborId] = true;
//                 rt[neighborId] = rt[currentId] + 1;
//                 q.push(neighbor);
//             }
//         }
//     }
//     res.push_back(rt);
    
// }

// public:
//     Task2(Graph<DATA, NAME, WD> *g) : G(g) { 
//         restart();
//     }
//     Task2(Task2 &o) : G(o.G) { restart(); } 
//     ~Task2() {res.clear();}
//     void set(Graph<DATA, NAME, WD> *g) { G = g; }
//     void restart() {
//         for(auto it = G->vBegin(); it != G->vEnd(); ++it) BFS(*it);
//     }
//     vector<vector<int>> result() {

//         return res;
//     }
// };
#include <queue>
#include <vector>
#include <limits>
#include <list>
#include "Graph.h"
using namespace std;

template<typename DATA, typename NAME, typename WD>
class Task2 {
private:
    Graph<DATA, NAME, WD>* G;
    vector<vector<int>> res;  // Матрица расстояний
    vector<vector<vector<int>>> paths;  // Матрица путей (имена вершин)
    
    void BFS(Vertex<DATA, NAME>* start) {
        if (!G->V()) return;
        const int V = G->V();
        int startId = start->getInd();
        
        // Инициализация
        vector<bool> visited(V, false);
        res[startId].assign(V, -1);
        paths[startId].resize(V);
        
        // Для хранения предыдущих вершин (для восстановления пути)
        vector<Vertex<DATA, NAME>*> prev(V, nullptr);
        
        queue<Vertex<DATA, NAME>*> q;
        visited[startId] = true;
        res[startId][startId] = 0;
        paths[startId][startId].push_back(start->getInd());
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
                    res[startId][neighborId] = res[startId][currentId] + 1;
                    prev[neighborId] = current;
                    q.push(neighbor);
                }
            }
        }

        // Восстановление путей для всех вершин
        for (int targetId = 0; targetId < V; ++targetId) {
            if (targetId == startId) continue;
            
            if (res[startId][targetId] != -1) {
                // Восстанавливаем путь от target к start
                list<int> path;
                Vertex<DATA, NAME>* current = G->graphForm->getVertexVector()[targetId];
                
                while (current != nullptr && current != start) {
                    path.push_front(current->getInd());
                    current = prev[current->getInd()];
                }
                
                if (current == start) {
                    path.push_front(start->getInd());
                    // Копируем путь в результат
                    paths[startId][targetId].assign(path.begin(), path.end());
                }
            }
        }
    }

public:
    Task2(Graph<DATA, NAME, WD>* g) : G(g) { 
        restart();
    }
    
    Task2(Task2& o) : G(o.G), res(o.res), paths(o.paths) {}
    
    ~Task2() {
        res.clear();
        paths.clear();
    }
    
    void set(Graph<DATA, NAME, WD>* g) { 
        G = g; 
        restart();
    }
    
    void restart() {
        const int V = G->V();
        res.assign(V, vector<int>(V, -1));
        paths.assign(V, vector<vector<int>>(V));
        
        for(auto it = G->vBegin(); it != G->vEnd(); ++it) {
            BFS(*it);
        }
    }    
        // Get the path between two vertices
        vector<int> getPath(int from, int to) const {
            if (from < 0 || to < 0 || from >= G->V() || to >= G->V())
                throw runtime_error("Invalid vertex indices");
            return paths[from][to];
        }
    
        // Get all shortest paths and res
        struct PathInfo {
            vector<int> path;
            WD distance;
        };
    
        vector<vector<PathInfo>> getAllPaths() const {            
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
};