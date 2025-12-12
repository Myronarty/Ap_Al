#include "MergeSort.h"

int* generateArray(int n, ArrayType type) {
    int* arr = new int[n];
    std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

    switch (type) 
    {
    case SORTED:
        for (int i = 0; i < n; i++) arr[i] = i;
        break;

    case REVERSE_SORTED:
        for (int i = 0; i < n; i++) arr[i] = n - 1 - i;
        break;

    case RANDOM: {
        std::uniform_int_distribution<int> dist(0, n * 10);
        for (int i = 0; i < n; i++) arr[i] = dist(rng);
        break;
    }
    case ALMOST_SORTED:
        for (int i = 0; i < n; i++) arr[i] = i;
        {
            std::uniform_int_distribution<int> distInd(0, n - 1);
            int swaps = std::max(1, n / 100);
            for (int k = 0; k < swaps; k++) 
            {
                std::swap(arr[distInd(rng)], arr[distInd(rng)]);
            }
        }
        break;

    case FEW_UNIQUE: 
    {
        std::uniform_int_distribution<int> distFew(0, 9);
        for (int i = 0; i < n; i++) arr[i] = distFew(rng);
        break;
    }
    }
    return arr;
}

void Top_DownMS(int* x, int n, Stats& stats)
{
    if (n == 1)
    {
        return;
    }
    int m = (n - (n >> 1));
    stats.memory += (m * sizeof(int)) + ((n - m) * sizeof(int));
    int* y = new int[m];
    for (int i = 0; i < m; i++)
    {
        y[i] = x[i];
        stats.copies++;
    }
    Top_DownMS(y, m, stats);
    int* y_ = new int[n - m];
    for (int i = 0; i < n - m; i++)
    {
        y_[i] = x[m + i];
    }
    Top_DownMS(y_, n - m, stats);

    int i = 0;
    int j = 0;
    int k = 0;

    while (i < m && j < n - m)
    {
        stats.comparisons++;

        if (y[i] < y_[j])
        {
            x[k] = y[i];
            i++;
        }
        else
        {
            x[k] = y_[j];
            j++;
        }
        stats.copies++;
        k++;
    }

    while (i < m)
    {
        x[k] = y[i];
        i++;
        k++;
    }

    while (j < n - m)
    {
        x[k] = y_[j];
        stats.copies++;
        j++;
        k++;
    }

    delete[] y;
    delete[] y_;

    return;
}

Node_* merge(Node_* left, Node_* right) 
{
    if (left == nullptr) return right;
    if (right == nullptr) return left;

    Node_* result = nullptr;

    if (left->data <= right->data) {
        result = left;
        result->next = merge(left->next, right);
    }
    else {
        result = right;
        result->next = merge(left, right->next);
    }

    return result;
}

Node_* getMiddle(Node_* head) 
{
    if (head == nullptr) return head;

    Node_* slow = head;
    Node_* fast = head->next;

    while (fast != nullptr && fast->next != nullptr) 
    {
        slow = slow->next;
        fast = fast->next->next;
    }

    return slow;
}

void Top_DownMS_Node_(Node_** x)
{
    Node_* head = *x;
    if (head == nullptr || head->next == nullptr)
    {
        return;
    }

    Node_* middle = getMiddle(head);

    Node_* rightHead = middle->next;

    middle->next = nullptr;

    Node_* leftHead = head;

    Top_DownMS_Node_(&leftHead);
    Top_DownMS_Node_(&rightHead);

    *x = merge(leftHead, rightHead);
}

void Bottom_UpMS(int* x, int n)
{
    int* a = new int[n];

    for (int i = 1; i < n; i *= 2)
    {
        for (int j = 0; j < n - i; j += (i << 1))
        {
            int m = i + j - 1;
            int temp;
            if ((j + 2 * i - 1) < n - 1)
            {
                temp = j + 2 * i - 1;
            }
            else
            {
                temp = n - 1;
            }

            for (int k = j; k <= temp; k++)
            {
                a[k] = x[k];
            }

            int i_ = j;
            int j_ = m + 1;

            for (int t = j; t <= temp; t++)
            {
                if (i_ > m)
                {
                    x[t] = a[j_];
                    j_++;
                }
                else if (j_ > temp)
                {
                    x[t] = a[i_];
                    i_++;
                }
                else if (a[j_] < a[i_])
                {
                    x[t] = a[j_];
                    j_++;
                }
                else
                {
                    x[t] = a[i_];
                    i_++;
                }
            }
        }
    }

    delete[] a;
}

void Bottom_UpMS_withMods(int* x, int n, Stats& stats)
{
    if (n < 11) //cutoff
    {
        for (int i = 1; i < n; i++)
        {
            int k = x[i];

            int j = i - 1;

            while (j >= 0 && x[j] > k)
            {
                x[j + 1] = x[j];
                j = j - 1;
            }

            x[j + 1] = k;
        }
    }

    int* a = new int[n]; // eliminate the copy to the auxiliary array
    stats.memory += n * sizeof(int);

    int* src = x;   // Поточний масив для читання
    int* dest = a; // Поточний масив для запису

    for (int width = 1; width < n; width *= 2)
    {
        for (int i = 0; i < n; i += 2 * width)
        {
            int left = i;
            int mid = std::min(i + width, n);
            int right = std::min(i + 2 * width, n);

            if (mid < right) {
                stats.comparisons++;
                if (src[mid - 1] <= src[mid]) {
                    // Вони вже в порядку! 
                    // Але оскільки ми перемикаємо масиви, треба перенести дані в dest.
                    // Це швидше, ніж злиття, бо немає if-else на кожен елемент.
                    for (int k = left; k < right; k++) {
                        dest[k] = src[k];
                        stats.copies++;
                    }
                    continue; // Пропускаємо процес злиття
                }
            }

            // Стандартне злиття (Merge)
            int l = left, r = mid, k = left;
            while (l < mid && r < right) {
                stats.comparisons++;
                if (src[l] <= src[r]) {
                    dest[k++] = src[l++];
                }
                else {
                    dest[k++] = src[r++];
                }
                stats.copies++;
            }
            while (l < mid) {
                dest[k++] = src[l++];
                stats.copies++;
            }
            while (r < right) {
                dest[k++] = src[r++];
                stats.copies++;
            }
        }

        // --- ВИМОГА 3: Eliminate the copy (частина 2) ---
        // Замість копіювання dest назад у src, ми просто міняємо їх ролями.
        // Тепер dest стає джерелом даних для наступної ітерації.
        std::swap(src, dest);
    }

    // Фінальна перевірка:
    // Якщо після останнього swap актуальні дані опинилися в aux (який зараз src),
    // треба скопіювати їх у вихідний масив x.
    if (src != x) {
        for (int i = 0; i < n; i++) {
            x[i] = src[i];
            stats.copies++;
        }
    }

    delete[] a;
}
