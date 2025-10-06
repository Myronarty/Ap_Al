#include "Set.h"
#include "GraphMat.h"
#include "GraphList.h"
#include "W_Or_Graphs.h"

using Clock = std::chrono::steady_clock;
using std::chrono::microseconds;
using std::chrono::duration_cast;

int main() {
    const int num_experiments = 1000;
    long long total_duration_us = 0;
    int a[5] = {15, 50, 100, 200, 500};
    double b[5] = { 0 };

    for (int j = 0; j < 5; j++)
    {
        for (int i = 0; i < num_experiments; ++i)
        {
            WGraphMat G = G.RG(a[j], 0.9);
            WGraphList H = H.Convert(G);
            auto start_time = Clock::now();

            H.BF(1);

            auto end_time = Clock::now();

            total_duration_us += duration_cast<microseconds>(end_time - start_time).count();
        }
        b[j] = static_cast<double>(total_duration_us) / num_experiments;
        cout << j <<"st iteration over" << endl;
    }
    for (int j = 0; j < 5; j++)
    {
        cout << "Average execution time: " << b[j] << " microseconds for BF on Graph with |V| = " << a[j] << endl;
    }

    return 0;
}