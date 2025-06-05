#include "Task2.h"
#include <limits>
#include <stdexcept>

template <typename DATA, typename NAME, typename WD>
class Task3 {
private:
    Graph<DATA, NAME, WD>* graph;
    std::vector<std::vector<WD>> shortestPaths;
    bool hasNegativeCycle;
    bool solved;

public:
    // Основной конструктор
    Task3(Graph<DATA, NAME, WD>* g) : graph(g), hasNegativeCycle(false), solved(false) {
        solveAllPairs();
    }

    // Конструктор копирования
    Task3(const Task3& other)
        : graph(other.graph),
          shortestPaths(other.shortestPaths),
          hasNegativeCycle(other.hasNegativeCycle),
          solved(other.solved) {}

    // Деструктор
    ~Task3() {
        shortestPaths.clear();
    }

    // Связывание с новым графом
    void set(Graph<DATA, NAME, WD>* g) {
        graph = g;
        solved = false;
        hasNegativeCycle = false;
        solveAllPairs();
    }

    // Повторное решение
    void restart() {
        if (graph) {
            solved = false;
            hasNegativeCycle = false;
            solveAllPairs();
        }
    }

    // Получение результата
    const std::vector<std::vector<WD>>& result() const {
        if (!solved) {
            throw std::runtime_error("Задача еще не решена");
        }
        if (hasNegativeCycle) {
            throw std::runtime_error("Граф содержит отрицательный цикл");
        }
        return shortestPaths;
    }

    // Проверка на наличие отрицательных циклов
    bool containsNegativeCycle() const {
        return hasNegativeCycle;
    }

private:
    // Решение задачи для всех пар вершин
    void solveAllPairs() {
        if (!graph || solved) return;
        const int V = graph->V();
        const WD INF = std::numeric_limits<WD>::max();
        shortestPaths.assign(V, std::vector<WD>(V, INF));

        for (int src = 0; src < V; ++src) {
            shortestPaths[src][src] = 0;

            for (int i = 1; i < V; ++i) {
                for (auto eIt = graph->eBegin(); eIt != graph->eEnd(); ++eIt) {
                    int u = (*eIt)->getV1()->getInd();
                    int v = (*eIt)->getV2()->getInd();
                    WD w = (*eIt)->getW();

                    if (shortestPaths[src][u] != INF && 
                        shortestPaths[src][v] > shortestPaths[src][u] + w) {
                        shortestPaths[src][v] = shortestPaths[src][u] + w;
                    }
                }
            }
            for (auto eIt = graph->eBegin(); eIt != graph->eEnd(); ++eIt) {
                int u = (*eIt)->getV1()->getInd();
                int v = (*eIt)->getV2()->getInd();
                WD w = (*eIt)->getW();

                if (shortestPaths[src][u] != INF && 
                    shortestPaths[src][v] > shortestPaths[src][u] + w) {
                    hasNegativeCycle = true;
                    solved = true;
                    return;
                }
            }
        }

        solved = true;
    }
};
