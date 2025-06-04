#ifndef GRAPH_H
#define GRAPH_H

#define LType false
#define MType true
#define DType true
#define NDType false

#include <iostream>


template<typename VD, typename NAME, typename WD>
class Graph {
private:
    void Transform(GraphForm<VD, NAME, WD> *form);

    int Vcnt;
    int Ecnt;
    bool isDirected;
    bool isDense;

public:
    using VertexT = Vertex<VD, NAME>;
    using EdgeT = Edge<VD, NAME, WD>;

    Graph(); // Конструктор по умолчанию
    Graph(int V, bool D, bool F); // V вершин без ребер типа D формы F
    Graph(int V, int E, bool D, bool F); // V вершин E случайных ребер D типа F формы
    Graph(Graph &other); // копирования 
    ~Graph(); // дестр

    int V(); // число вершин
    int E(); // число ребер
    bool Directed(); // тип графк
    bool Dense(); // форма графа
    int K(); // коэф насыщенности
    void toListGraph(); // преобразование в L
    void toMatrixGraph(); // преобразование в M

    VertexT *insertV(); // Безымянная вершин 
    VertexT *insertV(NAME name); // именованная вершин 
    bool deleteV(VertexT *v); // удаление вершины
    EdgeT *insertE(VertexT *i, VertexT *j); // вставка ребра без веса
    EdgeT *insertE(VertexT *i, VertexT *j, WD w); // вставка реба в весом ДОООООБ
    bool deleteE(VertexT* v1, VertexT* v2); // ДОООБ
    EdgeT *getEdge(VertexT *v1, VertexT *v2);

    void printGraph();

    VertexIterator<VD, NAME, WD> vBegin();
    VertexIterator<VD, NAME, WD> vEnd();
    EdgeIterator<VD, NAME, WD> eBegin();
    EdgeIterator<VD, NAME, WD> eEnd();
    EdgeIterator<VD, NAME, WD> adjEBegin(int v);
    EdgeIterator<VD, NAME, WD> adjEEnd(int v);

    GraphForm<VD, NAME, WD> *graphForm;
};

#endif
