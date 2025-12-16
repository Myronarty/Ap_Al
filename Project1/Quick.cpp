#include "QuickSort.h"

int op_last(int* x, int n)
{
    return n - 1;
}

int op_rand(int* x, int n)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, n - 1);
    return distrib(gen);
}

int op_med(int* x, int n)
{
    if ((x[0] < x[n / 2] && x[0] > x[n - 1]) || (x[0] > x[n / 2] && x[0] < x[n - 1]))
    {
        return 0;
    }
    else if ((x[n / 2] < x[0] && x[n / 2] > x[n - 1]) || (x[n / 2] > x[0] && x[n / 2] < x[n - 1]))
    {
        return n / 2;
    }
    else
    {
        return n - 1;
    }
}

int op_med_rand(int* x, int n)
{
    if (n < 3)
    {
        return op_rand(x, n);
    }

    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, n - 1);

    int a[3];
    a[0] = distrib(gen);
    do { a[1] = distrib(gen); } while (a[0] == a[1]);
    do { a[2] = distrib(gen); } while (a[0] == a[2] || a[1] == a[2]);

    int a_[3] = { x[a[0]], x[a[1]], x[a[2]] };
    int k = op_med(a_, 3);
    return a[k];
}

void QS_Lomuto(int* x, int low, int high, int (*op)(int*, int), Stats_QS& stats)
{
    if (low >= high) return;

    int n = high - low + 1;

    int t_relative = op(&x[low], n);

    int t_absolute = low + t_relative;

    std::swap(x[t_absolute], x[high]);
    stats.swaps++;

    int pivot = x[high];
    stats.copies++; // запам'ятали pivot

    int i = low - 1;

    for (int j = low; j < high; j++)
    {
        stats.comparisons++; // порівняння
        if (x[j] <= pivot)
        {
            i++;
            std::swap(x[i], x[j]);
            stats.swaps++;
        }
    }
    std::swap(x[i + 1], x[high]);
    stats.swaps++;

    int pi = i + 1;

    QS_Lomuto(x, low, pi - 1, op, stats);
    QS_Lomuto(x, pi + 1, high, op, stats);
}

void QS_Goar(int* x, int p, int n, int (*op)(int*, int), Stats_QS& stats)
{
    if (p >= n) return;

    int count = n - p + 1;

    int relative_idx = op(&x[p], count);

    int abs_idx = p + relative_idx;

    std::swap(x[p], x[abs_idx]);
    stats.swaps++;

    int t = x[p];
    stats.copies++;

    int i = p - 1;
    int j = n + 1;

    while (true)
    {
        do
        {
            i++;
            stats.comparisons++;
        } while (x[i] < t);

        do
        {
            j--;
            stats.comparisons++;
        } while (x[j] > t);

        if (i >= j)
        {
            break;
        }

        std::swap(x[i], x[j]);
        stats.swaps++;
    }

    QS_Goar(x, p, j, op, stats);
    QS_Goar(x, j + 1, n, op, stats);
}

void three_sides(int* x, int low, int high, int (*op)(int*, int), Stats_QS& stats)
{
    if (low >= high) return;

    int i = op(&x[low], high - low + 1);

    std::swap(x[low], x[low + i]);
    stats.swaps++;

    stats.comparisons++;
    if (x[low] > x[high])
    {
        std::swap(x[low], x[high]);
        stats.swaps++;
    }

    int p1 = x[low];
    int p2 = x[high];
    stats.copies += 2;

    int lt = low + 1;
    int gt = high - 1;
    int k = low + 1;

    while (k <= gt)
    {
        stats.comparisons++;
        if (x[k] < p1)
        {
            std::swap(x[k], x[lt]);
            stats.swaps++;
            lt++;
            k++;
        }
        else
        {
            stats.comparisons++; // перевірка else if
            if (x[k] > p2)
            {
                while (k < gt && x[gt] > p2)
                {
                    stats.comparisons++;
                    gt--;
                }
                stats.comparisons++; // остання перевірка while, яка дала false

                std::swap(x[k], x[gt]);
                stats.swaps++;
                gt--;

                stats.comparisons++;
                if (x[k] < p1)
                {
                    std::swap(x[k], x[lt]);
                    stats.swaps++;
                    lt++;
                }
                k++;
            }
            else
            {
                k++;
            }
        }
    }

    lt--;
    std::swap(x[low], x[lt]);
    stats.swaps++;

    gt++;
    std::swap(x[high], x[gt]);
    stats.swaps++;

    three_sides(x, low, lt - 1, op, stats);

    stats.comparisons++;
    if (x[lt] < x[gt])
    {
        three_sides(x, lt + 1, gt - 1, op, stats);
    }

    three_sides(x, gt + 1, high, op, stats);
}