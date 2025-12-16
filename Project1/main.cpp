#include "Set.h"
#include "GraphMat.h"
#include "GraphList.h"
#include "W_Or_Graphs.h"
#include "LUP.h"
#include "MergeSort.h"
#include "QuickSort.h"

using Clock = std::chrono::steady_clock;
using std::chrono::microseconds;
using std::chrono::duration_cast;

void runTest(int n, std::string name, SortFunction sortFunc, PivotStrategy opFunc) {
    std::cout << "--------------------------------\n";
    std::cout << "Algorithm: " << name << "\n";
    std::cout << "Generating array of size " << n << "..." << std::endl;

    int* arr = new int[n];

    // Генерація (використовуємо mt19937, як у вашому прикладі)
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, n * 2);

    for (int i = 0; i < n; i++) {
        arr[i] = distrib(gen);
    }

    std::cout << "Sorting started..." << std::endl;

    Stats_QS stats;
    auto start = std::chrono::high_resolution_clock::now();

    // Виклик переданої функції сортування
    // Передаємо stats по посиланню
    sortFunc(arr, 0, n - 1, opFunc, stats);

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start;

    std::cout << "Done!\n";
    std::cout << "Size: " << n << "\n";
    std::cout << "Time: " << std::fixed << std::setprecision(5) << diff.count() << " seconds\n";
    std::cout << "Comparisons: " << stats.comparisons << "\n";
    std::cout << "Swaps: " << stats.swaps << "\n";
    std::cout << "Copies (vars): " << stats.copies << "\n";

    // Пам'ять (Heap + Stack estimate)
    double heapMB = (double)(n * sizeof(int)) / (1024.0 * 1024.0);
    std::cout << "Memory (Heap array): " << heapMB << " MB\n";
    std::cout << "Memory (Stack recursion): ~O(log N)\n";

    delete[] arr;
}

int main() 
{
    int N[3] = { 1000000, 10000000, 50000000 };

    for (int i = 0; i < 3; i++)
    {
        runTest(N[i], "QS Lomuto (Rand Pivot)", QS_Lomuto, op_rand);
        runTest(N[i], "QS Goar (Median Pivot)", QS_Goar, op_med);
        runTest(N[i], "QS 3-Sides (MedRand Pivot)", three_sides, op_med_rand);
        cout << i << " step over." << endl;
    }

    return 0;
}


void push(Node_** headRef, int data) {
    Node_* newNode_ = new Node_(data);
    newNode_->next = *headRef;
    *headRef = newNode_;
}

void printList(Node_* Node_) {
    while (Node_ != nullptr) {
        std::cout << Node_->data << " -> ";
        Node_ = Node_->next;
    }
    std::cout << "nullptr" << std::endl;
}
