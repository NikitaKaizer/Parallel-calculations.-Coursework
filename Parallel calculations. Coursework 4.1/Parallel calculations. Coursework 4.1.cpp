#include <iostream>
#include <chrono>
#include "InvertedIndex.h"
using namespace std;

int main() {
    system("chcp 65001");

    // index.ShowFileName("for");

    for (int threadCount = 1; threadCount <= 10; ++threadCount) { 
        auto start = chrono::high_resolution_clock::now(); 

        InvertedIndex index;
        index.IndexDirectory("datasets", threadCount);

        auto end = chrono::high_resolution_clock::now(); 
        chrono::duration<double> diff = end - start; 

        cout << "Час, витрачений на " << threadCount << " потоки: "
            << diff.count() << " секунди" << endl;
    }

    return 0;
}

