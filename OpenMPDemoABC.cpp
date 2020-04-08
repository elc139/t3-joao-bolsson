#include <algorithm>
#include <iostream>
#include <string>
#include <omp.h>

#define CHUNK 100

using namespace std;

/*
compilado com:
g++ -std=c++11 OpenMPDemoABC.cpp -fopenmp -pthread -o OpenMPDemoABC
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
    void addChar(char c) {
        array[index] = c;
        spendSomeTime();
        index++;
    }

    void addChar(char c, int pos) {
        if (pos >= 0 && pos < size) {
            array[pos] = c;
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

    void fillArrayConcurrently() {
        int i;
#pragma omp parallel for schedule(static, nTimes) shared(array) private(i) num_threads(nThreads)
        for (i = 0; i < nThreads * nTimes; i++)
            array->addChar('A' + omp_get_thread_num(), i);
    }

    void printStats() {
        cout << array->toString() << endl;
        for (int i = 0; i < nThreads; ++i)
            cout << (char)('A' + i) << "="
                 << array->countOccurrences('A' + i) << " ";
        cout << endl;
    }

    ~ArrayFiller() {
        delete array;
    }
};

int main() {
    cout << "Each thread should add its char to the array n times (n=20)" << endl;
    cout << "Correct results should total exactly nThreads*nTimes chars" << endl;
    cout << "Expecting correct results" << endl;
    ArrayFiller m1;
    m1.fillArrayConcurrently();
    m1.printStats();
}
