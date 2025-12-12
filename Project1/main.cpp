#include "Set.h"
#include "GraphMat.h"
#include "GraphList.h"
#include "W_Or_Graphs.h"
#include "LUP.h"
#include "MergeSort.h"

using Clock = std::chrono::steady_clock;
using std::chrono::microseconds;
using std::chrono::duration_cast;

void runTest(int n) {
    std::cout << "Generating array of size " << n << "..." << std::endl;

    // Генеруємо масив
    int* arr = new int[n];

    // Заповнюємо випадковими числами
    // Використовуємо простий rand() для швидкості генерації, або std::mt19937 для якості
    for (int i = 0; i < n; i++) {
        arr[i] = rand();
    }

    std::cout << "Sorting started..." << std::endl;

    Stats stats;
    auto start = std::chrono::high_resolution_clock::now();

    // Виклик вашої функції
    Top_DownMS(arr, n, stats);

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start;

    std::cout << "Done!\n";
    std::cout << "Size: " << n << "\n";
    std::cout << "Time: " << diff.count() << " seconds\n";
    std::cout << "Comparisons: " << stats.comparisons << "\n";
    std::cout << "Copies: " << stats.copies << "\n";
    std::cout << "--------------------------------\n";

    delete[] arr;
}

int main() 
{
    runTest(1000000);

    runTest(10000000);

    runTest(50000000);

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
