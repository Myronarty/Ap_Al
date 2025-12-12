#include "MergeSort.h"

void Top_DownMS(int* x, int n)
{
    if (n == 1)
    {
        return;
    }
    int m = (n - (n >> 1));
    int* y = new int[m];
    for (int i = 0; i < m; i++)
    {
        y[i] = x[i];
    }
    Top_DownMS(y, m);
    int* y_ = new int[n - m];
    for (int i = 0; i < n - m; i++)
    {
        y_[i] = x[m + i];
    }
    Top_DownMS(y_, n - m);

    int i = 0;
    int j = 0;
    int k = 0;

    while (i < m && j < n - m)
    {
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

void Bottom_UpMS_withMods(int* x, int n)
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

            if (x[j] <= x[m+1]) //stop if sorted
            {
                continue;
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
