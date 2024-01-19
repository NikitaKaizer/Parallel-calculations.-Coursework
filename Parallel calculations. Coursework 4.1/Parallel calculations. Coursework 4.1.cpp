#include <iostream>
#include <chrono>
#include "invertedindex.h"
using namespace std;

int main() {
    system("chcp 65001");

    // index.showfilename("for");

    for (int threadcount = 1; threadcount <= 10; ++threadcount) { 
        auto start = chrono::high_resolution_clock::now(); 

        InvertedIndex index;
        index.IndexDirectory("datasets", threadcount);

        auto end = chrono::high_resolution_clock::now(); 
        chrono::duration<double> diff = end - start; 

        cout << "час, витрачений на " << threadcount << " потоки: "
            << diff.count() << " секунди" << endl;
    }

    return 0;
}

