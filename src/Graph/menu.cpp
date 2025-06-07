#include "Task3.h"

Graph<int, string, int> *graph;
void printFillMenu();
void itm();
void vitm();
void eitm();
void oeitm(int v);
void t2m();
void t3m();

int main() {
    Edge<int, string, int> *e;
    int v1Ind, v2Ind;
  int command = -1;
  while (command != 14) {
    printf("\tМеню\n"
           "1) Работа с графом\n"
           "2) Кол-во вершин.\n"
           "3) Кол-во ребер.\n"
           "4) Направленность .\n"
           "5) Форма представлениие.\n"
           "6) Коэффициент насыщенности.\n"
           "7) Преобразование в M-граф.\n"
           "8) Преобразование в L-граф\n"
           "9) Вывод графа\n"
           "10) Работа с итераторами\n"
           "11) Получить значение на вершине\n"
           "12) Кратчайшее расстояние между парами всеми вершин невзвешанного графа(Задание 2)\n"
           "13) Кратчайшее расстояние между парами всеми вершин взвешанного графа (Задание 3)\n"
           "14) Выход\n"
           "Действие:");
    scanf("%d", &command);
    switch (command) {
    case 1:
      printFillMenu();
      break;
    case 2:
        cout << graph->V() << endl;
      break;
    case 3:
        cout << graph->E() << endl;
      break;
    case 4:
        cout << graph->Directed() << endl;
      break;
    case 5:
        cout << graph->Dense() << endl;
      break;
    case 6:
        cout <<  graph->K() << endl;
      break;
    case 7:
        graph->toMatrixGraph();
      break;
    case 8:
        graph->toListGraph();
      break;
    case 9:
        graph->printGraph();
      break;
    case 10:
        itm();
      break;
    case 11:
        cout << "Введите первый индекс вершины: ";
        cin >> v1Ind;
        cout << "Введите второй индекс вершины: ";
        cin >> v2Ind;
        cout << graph->getEdge(v1Ind, v2Ind)->getData() << endl;
        break;
    case 12:
        t2m();
        break;
    case 13:
        t3m();
        break;
    default:
      break;
    }
  }
  return 0;
}

void printFillMenu() {
  int command = -1;
  int vCount, eCount, weight;
  bool dir, den;
  Vertex<int, string> *v1, *v2;
  Edge<int, string, int> *e;
  int v1Ind, v2Ind;
  string vertexName;

  while (command != 9) {
    printf("\n=== МЕНЮ ЗАПОЛНЕНИЯ ГРАФА ===\n\n"
           "Выберите действие:\n"
           "1) Инициализация графа\n"
           "2) Инициализация со случйными значениями\n"
           "3) Вставка вершины\n"
           "4) Вставка вершины с именем\n"
           "5) Вставка ребра\n"
           "6) Вставка ребра с весом\n"
           "7) Удалить вершину\n"
           "8) Удалить ребро\n"
           "9) Назад\n\n"
           "Действие: ");

    scanf("%d", &command);
    switch (command) {
    case 1:
        cout << "Введите количество вершин: ";
        cin >> vCount;
        cout << "Тип графа (1 - ориентированный, 0 - неориентированный): ";
        cin >> dir;
        cout << "Форма представления (1 - матрица, 0 - список): ";
        cin >> den;
        graph = new Graph<int, string, int>(vCount, dir, den);
        break;
    case 2:
        cout << "Введите количество вершин: ";
        cin >> vCount;
        cout << "Введите количество ребер: ";
        cin >> eCount;
        cout << "Тип графа (1 - ориентированный, 0 - неориентированный): ";
        cin >> dir;
        cout << "Форма представления (1 - матрица, 0 - список): ";
        cin >> den;
        graph = new Graph<int, string, int>(vCount, eCount, dir, den);
      break;

    case 3:
      cout << graph->insertV()->getInd() << endl;
      break;

    case 4:
      cout << "Введите имя вершины: ";
      cin >> vertexName;
      cout << graph->insertV(vertexName)->getInd() << endl;
      break;
    case 5:
        cout << "Введите первый индекс вершины: ";
        cin >> v1Ind;
        cout << "Введите второй индекс вершины: ";
        cin >> v2Ind;
        v1 = new Vertex<int, string>;
        v2 = new Vertex<int, string>;
        v1->setInd(v1Ind);
        v2->setInd(v2Ind);
        cout << graph->insertE(v1, v2)->getW() << endl;
      break;
    case 6:
        cout << "Введите индекс первой вершины: ";
        cin >> v1Ind;
        cout << "Введите индекс второй вершины: ";
        cin >> v2Ind;
        cout << "Введите вес ребра: ";
        cin >> weight;
        v1 = new Vertex<int, string>;
        v2 = new Vertex<int, string>;
        v1->setInd(v1Ind);
        v2->setInd(v2Ind);
        cout << graph->insertE(v1, v2, weight)->getW() << endl;
      break;
    case 7:
      cout << "Введите индекс вершины: ";
      cin >> v1Ind;
      v1 = new Vertex<int, string>;
      v1->setInd(v1Ind);
      cout << graph->deleteV(v1) << endl;
      break;
    case 8:
      cout << "Введите индекс первой вершины: ";
      cin >> v1Ind;
      cout << "Введите индекс второй вершины: ";
      cin >> v2Ind;
      v1 = new Vertex<int, string>;
      v2 = new Vertex<int, string>;
      v1->setInd(v1Ind);
      v2->setInd(v2Ind);
      cout << graph->deleteE(v1, v2) << endl;
      break;
    default:
      break;
    }
  }
}

void itm() {
  int command = -1;
  while (command != 4) {
    printf("Выберите действие:\n"
           "1) Итератор вершин.\n"
           "2) Итератор ребер.\n"
           "3) Итератор исходящих ребер.\n"
           "4) Вернуться в меню.\n"
           "Действие:");
    scanf("%d", &command);
    switch (command) {
    case 1:
      vitm();
      return;
    case 2:
      eitm();
      break;
    case 3:
      int v;
      cout << "Введите индекс вершины: ";
      cin >> v;
      if (!(v < 0 || v >= graph->V()))
        oeitm(v);
      break;
    default:
      break;
    }
  }
}

void vitm() {
  int command = -1;
  vector<Vertex<int, string> *> vertexVector;
  Graph<int, string, int>::VertexIterator iter =
      Graph<int, string, int>::VertexIterator(vertexVector, -1);
  Graph<int, string, int>::VertexIterator end =
      Graph<int, string, int>::VertexIterator(vertexVector, -1);

  while (command != 4) {
    printf("Итератор вершины:\n"
           "1) Установка итератора\n"
           "2) Перемещение вперед\n"
           "3) Значение на позиции\n"
           "4) Назад\n"
           "Действие: ");
    scanf("%d", &command);
    int re = 0;
    switch (command) {
    case 1:
      iter = graph->vBegin();
      break;
    case 2:
      iter++;
      break;
    case 3:
      try {
        re = (*iter)->getInd();
      } catch (...) {
        cout << "Исключение" << endl;
      }
      cout << re << endl;
      break;
    default:
      break;
    }
  }
}

void eitm() {
  int command = -1;
  Graph<int, string, int>::EdgeIterator iter =
      Graph<int, string, int>::EdgeIterator(nullptr, -1);
  Graph<int, string, int>::EdgeIterator end =
      Graph<int, string, int>::EdgeIterator(nullptr, -1);
  int ind1, ind2;
  while (command != 4) {
    printf("Итератор ребра:\n"
           "1) Установка итератора\n"
           "2) Перемещение вперед\n"
           "3) Значение на позиции\n"
           "4) Назад\n"
           "Действие: ");
    scanf("%d", &command);
    switch (command) {
    case 1:
      iter = graph->eBegin();
      break;
    case 2:
      iter++;
      break;
    case 3:
      try {
        ind1 = (*iter)->getV1()->getInd();
        ind2 = (*iter)->getV2()->getInd();
      } catch (...) {
        cout << "Исключение" << endl;
      }
      cout << ind1 << " " << ind2 << endl;
      break;
    default:
      break;
    }
  }
}

void oeitm(int v) {
  int command = -1;
  Graph<int, string, int>::EdgeIterator iter =
      Graph<int, string, int>::EdgeIterator(nullptr, -1);
  Graph<int, string, int>::EdgeIterator end =
      Graph<int, string, int>::EdgeIterator(nullptr, -1);
  int ind1, ind2;
  while (command != 4) {
    printf("Итератор исходящих ребер:\n"
           "1) Установка итератора\n"
           "2) Перемещение вперед\n"
           "3) Значение на позиции\n"
           "4) Назад\n"
           "Действие: ");
    scanf("%d", &command);
    switch (command) {
    case 1:
      iter = graph->adjEBegin(v);
      break;
    case 2:
      iter++;
      break;
    case 3:
    try {
        ind1 = (*iter)->getV1()->getInd();
        ind2 = (*iter)->getV2()->getInd();
      } catch (...) {
        cout << "Исключение" << endl;
      }
      cout << ind1 << " " << ind2 << endl;
      break;
    default:
      break;
    }
  }
}
void t2m() {
  Task2<int, string, int> task2(graph);
  cout << "Result:" << endl;
  auto allPaths = task2.result();
  for (int i = 0; i < graph->V(); i++) {
      for (int j = 0; j < graph->V(); j++) {
          if (i != j && allPaths[i][j].distance != numeric_limits<int>::max()) {
              cout << "(" << i << ", " << j << "): ";
              for (size_t k = 0; k < allPaths[i][j].path.size(); k++) {
                  cout << allPaths[i][j].path[k];
                  if (k < allPaths[i][j].path.size() - 1) {
                      cout << " -> ";
                  }
              }
              cout << endl;
          }
      }
  }
}

void t3m() {
  Task3<int, string, int> task3(graph);
  cout << "Result:" << endl;
  try {
      auto allPaths = task3.result();
      for (int i = 0; i < graph->V(); i++) {
          for (int j = 0; j < graph->V(); j++) {
              if (i != j && allPaths[i][j].distance != numeric_limits<int>::max()) {
                  cout << "(" << i << ", " << j << "): ";
                  for (size_t k = 0; k < allPaths[i][j].path.size(); k++) {
                      cout << allPaths[i][j].path[k];
                      if (k < allPaths[i][j].path.size() - 1) {
                          cout << " -> ";
                      }
                  }
                  cout << endl;
              }
          }
      }
  } catch (const runtime_error& e) {
      cout << "Отрицательный путь\n";
  }

}