#include "Set.h"
#include "GraphMat.h"
#include "GraphList.h"
#include "W_Or_Graphs.h"
#include "LUP.h"

using Clock = std::chrono::steady_clock;
using std::chrono::microseconds;
using std::chrono::duration_cast;

int main() 
{
    double A[9] = {1, -3, 1, 3, -4, 1, 0, 2, -1};

    double b[3] = {2, 0, 1};

    double* x = rozviazok(A, b, 3);

    for (int i = 0; i < 3; i++)
    {
        cout << x[i] << ", ";
    }

    /*long long total_duration_us = 0;
    int a[5] = { 15, 50, 100, 200, 500 };
    double b[5] = { 0 };

    for (int i = 0; i < 5; i++)
    {
            for (int exp = 0; exp < 100; exp++)
            {
                WGraphMat G = G.RG(a[i], 1);
                WGraphList H = H.Convert(G);
                vector<Edge> E = H.Sort();
                auto start_time = Clock::now();

                H.Kruskal(E);

                auto end_time = Clock::now();

                total_duration_us += duration_cast<milliseconds>(end_time - start_time).count();
            }
            b[i] = static_cast<double>(total_duration_us) / 100;
            cout << i << "st iteration over" << endl;
            total_duration_us = 0;
    }

    for (int i = 0; i < 5; i++)
    {
        cout << "Average execution time: " << b[i] << " milliseconds for Kruskal on Graph with |V| = " << a[i] << endl;
        cout << endl;
    }
    */
    return 0;
}