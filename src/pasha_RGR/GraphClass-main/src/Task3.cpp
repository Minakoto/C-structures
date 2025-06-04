#include "Task3.h"

template<typename DATA, typename NAME, typename WEIGHT>
Task3<DATA, NAME, WEIGHT>::Task3(SimpleGraph<DATA, NAME, WEIGHT> *g) {
    G = g;
    p = vector<vector<Edge<DATA, NAME, WEIGHT> *>>(g->getV());
    d = vector<vector<double> >(g->getV());
    restart();
}

template<typename DATA, typename NAME, typename WEIGHT>
Task3<DATA, NAME, WEIGHT>::Task3(Task3 &o) {
    G = o.G;
    p = o.p;
    d = o.d;
}

template<typename DATA, typename NAME, typename WEIGHT>
Task3<DATA, NAME, WEIGHT>::~Task3() {
}

template<typename DATA, typename NAME, typename WEIGHT>
int Task3<DATA, NAME, WEIGHT>::result() {
    int max = 0, lmax;
    for (int i = 0; i < d.size(); ++i) {
        for (int j = 0; j < d.size(); ++j) {
            if (d[i][j] > max) {
                max = d[i][j];
                res = i * 100 + j;
            }
        }
    }
    return max;
}


template<typename DATA, typename NAME, typename WEIGHT>
void Task3<DATA, NAME, WEIGHT>::set(SimpleGraph<DATA, NAME, WEIGHT> *g) {
    G = g;
}


template<typename DATA, typename NAME, typename WEIGHT>
string Task3<DATA, NAME, WEIGHT>::getPath() {
    int i, j;
    i = res / 100;
    j = res % 100;
    if (!pathMap[res].empty()) return pathMap[res];
    else return (to_string(i) + "->" + to_string(j));
}

template<typename DATA, typename NAME, typename WEIGHT>
void Task3<DATA, NAME, WEIGHT>::restart() {
    int V = G->getV();
    for (int i = 0; i < V; i++) {
        p[i].assign(V, nullptr);
        d[i].assign(V, 0);
    }
    for (int s = 0; s < V; s++)
        for (int t = 0; t < V; t++) {
            if (G->graphForm->hasEdge(s, t)) {
                p[s][t] = G->getEdge(s, t);
                d[s][t] = p[s][t]->getW();
            }
        }
    for (int s = 0; s < V; s++) d[s][s] = 0;
    for (int i = 0; i < V; i++)
        for (int s = 0; s < V; s++)
            if (p[s][i])
                for (int t = 0; t < V; t++)
                    if (s != t)
                        if (d[s][t] > d[s][i] + d[i][t]) {
                            p[s][t] = p[s][i];
                            d[s][t] = d[s][i] + d[i][t];
                            auto tmp = pathMap.find(s * 100 + t);
                            if (tmp != pathMap.end())
                                pathMap.insert(make_pair(s * 100 + t, tmp->second + to_string(s) + " " + to_string(t)));
                            else
                                pathMap.insert(make_pair(s * 100 + t, to_string(s) + " " + to_string(t)));
                        }
}