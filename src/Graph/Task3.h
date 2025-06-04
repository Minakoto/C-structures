#include "Task2.h"

using namespace std;

template<typename DATA, typename NAME, typename WD>
class Task3 {
    private:
    Graph<DATA, NAME, WD> *G;
    vector<vector<WD>> res;
public:
    Task3(Graph<DATA, NAME, WD> *g) {
        set(g);
        // Bellman_Ford();
        // restart();
    }
    Task3(Task3 &o) : G(o.G) { restart();} 
    ~Task3() {}
    void set(Graph<DATA, NAME, WD> *g) { G = g; }
    void restart() {
        // Bellman_Ford();
    }
    vector<vector<int>> result() {

        // return res;
    }
    void Bellman_Ford() {
        if (!G->Directed()) return;
        const int V = G->V();
        const WD INF = std::numeric_limits<WD>::max();
        for (int i = 0; i < V; ++i) res[i][i] = 0;

        cout << "who" << endl;
        for (auto eIt = G->eBegin(); eIt != G->eEnd(); ++eIt) {
            int u = (*eIt)->getV1()->getInd();
            int v = (*eIt)->getV2()->getInd();
            WD w = (*eIt)->getW();
            res[u][v] = w;
        }
        cout << "Nope" << endl;
        // Релаксация всех рёбер V-1 раз
        for (int k = 0; k < V-1; ++k) {
            for (auto eIt = G->eBegin(); eIt != G->eEnd(); ++eIt) {
                int u = (*eIt)->getV1()->getInd();
                int v = (*eIt)->getV2()->getInd();
                WD w = (*eIt)->getW();
    
                if (res[u][u] != INF && res[u][v] > res[u][u] + w) {
                    res[u][v] = res[u][u] + w;
                }
            }
        }
        cout << "Yep" << endl;
        // Проверка на отрицательные циклы
        for (auto eIt = G->eBegin(); eIt != G->eEnd(); ++eIt) {
            int u = (*eIt)->getV1()->getInd();
            int v = (*eIt)->getV2()->getInd();
            WD w = (*eIt)->getW();
    
            if (res[u][u] != INF && res[u][v] > res[u][u] + w) return;
        }
    
        // Вывод результатов
        std::cout << "Кратчайшие пути между всеми парами вершин:\n";
        for (int i = 0; i < V; ++i) {
            for (int j = 0; j < V; ++j) {
                if (res[i][j] == INF)
                    std::cout << "INF\t";
                else
                    std::cout << res[i][j] << "\t";
            }
            std::cout << "\n";
        }
    }
};
