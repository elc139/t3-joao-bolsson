#include <algorithm>
#include <iostream>
#include <string>
#include <omp.h>

using namespace std;

/*
compilado com:
g++ -std=c++11 OpenMPDemoABC.cpp -fopenmp -o OpenMPDemoABC
*/

class SharedArray {
private:
    char *array;
    int index;
    int size;

public:
    SharedArray(int n) : size(n), index(0) {
        array = new char[size];
        fill(array, array + size, '-');
    }

    ~SharedArray() {
        delete[] array;
    }

    void addChar(char c, int pos) {
        if (pos >= 0 && pos < size) {
            array[pos] = c;
            spendSomeTime();
        }
    }

    int countOccurrences(char c) {
        return count(array, array + size, c);
    }

    string toString() {
        return string(array, size);
    }

private:
    void spendSomeTime() {
        for (int i = 0; i < 10000; i++) {
            for (int j = 0; j < 100; j++) {
                // These loops shouldn't be removed by the compiler
            }
        }
    }
};

class ArrayFiller {
private:
    static const int nThreads = 3;
    static const int nTimes = 20;
    SharedArray *array;

public:
    ArrayFiller() {
        array = new SharedArray(nThreads * nTimes);
    }

    /**
     * Static with chunk.
     */
    void fillStaticChunk() {
        printf("\n\nCase: static with chunk\n");
#pragma omp parallel for schedule(static, nTimes) shared(array) num_threads(nThreads)
        for (int i = 0; i < nThreads * nTimes; i++)
            array->addChar('A' + omp_get_thread_num(), i);
    }

    /**
     * Static with chunk.
     */
    void fillStaticNoChunk() {
        printf("\n\nCase: static without chunk\n");
#pragma omp parallel for schedule(static) shared(array) num_threads(nThreads)
        for (int i = 0; i < nThreads * nTimes; i++)
            array->addChar('A' + omp_get_thread_num(), i);
    }

    /**
     * Dynamic with chunk.
     */
    void fillDynamicChunk() {
        printf("\n\nCase: dynamic with chunk\n");
#pragma omp parallel for schedule(dynamic, nTimes) shared(array) num_threads(nThreads)
        for (int i = 0; i < nThreads * nTimes; i++)
            array->addChar('A' + omp_get_thread_num(), i);
    }

    /**
     * Dynamic with chunk.
     */
    void fillDynamicNoChunk() {
        printf("\n\nCase: dynamic without chunk\n");
#pragma omp parallel for schedule(dynamic) shared(array) num_threads(nThreads)
        for (int i = 0; i < nThreads * nTimes; i++)
            array->addChar('A' + omp_get_thread_num(), i);
    }

    /**
     * Guided with chunk.
     */
    void fillGuidedChunk() {
        printf("\n\nCase: guided with chunk\n");
#pragma omp parallel for schedule(guided, nTimes) shared(array) num_threads(nThreads)
        for (int i = 0; i < nThreads * nTimes; i++)
            array->addChar('A' + omp_get_thread_num(), i);
    }

    /**
     * Guided with chunk.
     */
    void fillGuidedNoChunk() {
        printf("\n\nCase: guided without chunk\n");
#pragma omp parallel for schedule(guided) shared(array) num_threads(nThreads)
        for (int i = 0; i < nThreads * nTimes; i++)
            array->addChar('A' + omp_get_thread_num(), i);
    }

    /**
     * Case with schedule runtime.
     */
    void fillRuntime() {
        printf("\n\nCase: runtime\n");
#pragma omp parallel for schedule(runtime) shared(array) num_threads(nThreads)
        for (int i = 0; i < nThreads * nTimes; i++)
            array->addChar('A' + omp_get_thread_num(), i);
    }

    /**
     * Case with schedule runtime.
     */
    void fillAuto() {
        printf("\n\nCase: auto\n");
#pragma omp parallel for schedule(auto) shared(array) num_threads(nThreads)
        for (int i = 0; i < nThreads * nTimes; i++)
            array->addChar('A' + omp_get_thread_num(), i);
    }

    void printStats() {
        cout << array->toString() << endl;
        for (int i = 0; i < nThreads; ++i)
            cout << (char)('A' + i) << "="
                 << array->countOccurrences('A' + i) << " ";
        cout << endl;
    }

    void clear() {
        array = new SharedArray(nThreads * nTimes);
    }

    ~ArrayFiller() {
        delete array;
    }
};

int main() {
    ArrayFiller m1;
    m1.fillStaticChunk();
    m1.printStats();
    m1.clear();

    m1.fillStaticNoChunk();
    m1.printStats();
    m1.clear();

    m1.fillDynamicChunk();
    m1.printStats();
    m1.clear();

    m1.fillDynamicNoChunk();
    m1.printStats();
    m1.clear();

    m1.fillGuidedChunk();
    m1.printStats();
    m1.clear();

    m1.fillGuidedNoChunk();
    m1.printStats();
    m1.clear();

    m1.fillRuntime();
    m1.printStats();
    m1.clear();

    m1.fillAuto();
    m1.printStats();
    m1.clear();
}
