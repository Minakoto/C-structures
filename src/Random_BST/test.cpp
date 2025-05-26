#include "rnd_btree.h"
// #include "btree.h"
#include <time.h>
#include <math.h>

typedef unsigned long long INT_64;

static INT_64 rrand = 15750;
const INT_64 mrand = (1ULL << 63) - 1;
const INT_64 arand = 6364136223846793005;
const INT_64 crand = 1442695040888963407;

void sRand() { srand(time(0)); rrand = (INT_64)rand();}

INT_64 generate() {
    INT_64 one, two;
    one = (arand * rrand + crand) % mrand;
    two = (arand * one + crand) % mrand;
    rrand = one & 0xFFFFFFFF00000000LL ^
        (two & 0xFFFFFFFF00000000LL) >> 32;
    return rrand;
}

void test(int n) {
    RND_Btree<INT_64, int> tree;
    Btree<INT_64, int> tree2;
    INT_64* m = new INT_64[n];
    sRand();

    for(int i = 0; i < n; i++) {
        m[i] = generate();
        tree.add(m[i], i);
        tree2.add(m[i], i);
    }
    cout << "Размер рандомизированного дерева до тестирования: " << tree.get_size() << endl;
    cout << "Размер дерева до тестирования: " << tree2.get_size() << endl;


    double I = 0, D = 0, S = 0;
    double I1 = 0, D1 = 0, S1 = 0;


    for(int i = 0; i < n/2; i++) {
        if(i%10 == 0) {
            tree.del(generate());
            tree2.del(generate());
            D += tree.count_nodes();
            D1 += tree2.count_nodes();
            tree.add(m[rand()%n], 1);
            tree2.add(m[rand()%n], 1);
            I+= tree.count_nodes();
            I1+= tree2.count_nodes();

            try {
                tree.read(generate());
                S += tree.count_nodes();
            } catch(...) {S += tree.count_nodes();}
            try {
                tree2.read(generate());
                S1 += tree2.count_nodes();
            } catch(...) {S1 += tree2.count_nodes();}
        }
        else {
            int ind = rand() % n;
            tree.del(m[ind]);
            tree2.del(m[ind]);
            D += tree.count_nodes();
            D1 += tree2.count_nodes();

            INT_64 key = generate();
            tree.add(key, 1);
            tree2.add(key, 1);

            I += tree.count_nodes();
            I1 += tree2.count_nodes();
            m[ind] = key;
            try{
                tree.read(m[rand()%n]);
                S += tree.count_nodes();
            } catch(...) {S += tree.count_nodes();}
            try{
                tree2.read(m[rand()%n]);
                S1 += tree2.count_nodes();
            } catch(...) {S1 += tree2.count_nodes();}
        }
    }
    cout << "Размер рандомизированного дерева после теста: " << tree.get_size() << endl;
    cout << "1.39*log2(n)=" << 1.39*log((double)n)/log(2.0) << endl;
    cout << "Вставка: " << I/(n/2) << endl;
    cout << "Удаление: " << D/(n/2) << endl;
    cout << "Поиск: " << S/(n/2) << endl;

    cout << "Размер дерева после теста: " << tree2.get_size() << endl;
    cout << "1.39*log2(n)=" << 1.39*log((double)n)/log(2.0) << endl;
    cout << "Вставка: " << I1/(n/2) << endl;
    cout << "Удаление: " << D1/(n/2) << endl;
    cout << "Поиск: " << S1/(n/2) << endl;
    delete[] m;
}

void test_ord(int n) {
    RND_Btree<INT_64, int> tree;
    Btree<INT_64, int> tree2;

    INT_64* m = new INT_64[n];

    for(int i = 0; i < n; i++) {
        m[i] = i * 10000;
        tree.add(m[i], 1);
        tree2.add(m[i], 1);
    }

    cout << "Размер рандомизированного дерева до тестирования: " << tree.get_size() << endl;
    cout << "Размер дерева до тестирования: " << tree2.get_size() << endl;

    double I = 0, D = 0, S = 0;
    double I1 = 0, D1 = 0, S1 = 0;


    sRand();

    for(int i = 0; i < n/2;i++) {
        if(i%10 == 0) {
            int key = generate() % (10000*n);
            key += !(key%2);
            tree.del(key);
            tree2.del(key);
            D += tree.count_nodes();
            D1 += tree2.count_nodes();
            tree.add(m[rand()%n], 1);
            tree2.add(m[rand()%n], 1);
            I += tree.count_nodes();
            I1 += tree2.count_nodes();
            key = generate() % (10000*n);
            key += !(key%2);
            try {
                tree.read(key);
                S += tree.count_nodes();
            } catch(...) {S += tree.count_nodes();}
            try {
                tree2.read(key);
                S1 += tree2.count_nodes();
            } catch(...) {S1 += tree2.count_nodes();}
        }
        else {
            int ind = rand() % n;
            tree.del(m[ind]);
            tree2.del(m[ind]);

            D += tree.count_nodes();
            D1 += tree2.count_nodes();

            int key = generate() % (10000*n);
            key += !(key%2);
            tree.add(key, 1);
            tree2.add(key, 1);

            I += tree.count_nodes();
            I1 += tree2.count_nodes();

            m[ind] = key;
            try {
                tree.read(m[rand()%n]);
                S += tree.count_nodes();
            } catch(...) {S += tree.count_nodes();}
            try {
                tree2.read(m[rand()%n]);
                S1 += tree2.count_nodes();
            } catch(...) {S1 += tree2.count_nodes();}
        }
    }
    cout << "Размер рандомизированного дерева после теста: " << tree.get_size() << endl;
    cout << "1.39*log2(n)=" << 1.39*log((double)n)/log(2.0) << endl;
    cout << "Вставка: " << I/(n/2) << endl;
    cout << "Удаление: " << D/(n/2) << endl;
    cout << "Поиск: " << S/(n/2) << endl;

    cout << "Размер дерева после теста: " << tree2.get_size() << endl;
    cout << "n/2 = " << n/2 << endl;
    cout << "Вставка: " << I1/(n/2) << endl;
    cout << "Удаление: " << D1/(n/2) << endl;
    cout << "Поиск: " << S1/(n/2) << endl;
    delete[] m;
}

int main(int argc, char* argv[]) {
    int num = 0;
    if(argc > 1) num = atoi(argv[1]);
    else num =100 + rand() % (100000 - 100);

    cout << "Случайное дерево" << endl << "_____________________" << endl;
    test(num);
    cout <<  "_____________________" << endl <<  "\nВырожденное дерево" << endl << "_____________________" << endl;
    test_ord(num);


}

