#ifndef ASD_RGR_TASK3_H
#define ASD_RGR_TASK3_H

#include <vector>
#include "SimpleGraph.h"
#include <map>

template<typename DATA, typename NAME, typename WEIGHT>
class Task3 {

public:
    Task3(SimpleGraph<DATA, NAME, WEIGHT> *g);

    Task3(Task3 &o);

    ~Task3();

    void set(SimpleGraph<DATA, NAME, WEIGHT> *g);
    string getPath();
    void restart();

    int result();

private:
    SimpleGraph<DATA, NAME, WEIGHT> *G;
    vector<vector<Edge<DATA, NAME, WEIGHT> *>> p;
    vector<vector<double> > d;
    string path;
    map<int, string> pathMap;
    int res;
};



template
class Task3<int, string, int>;


#endif //ASD_RGR_TASK3_H
