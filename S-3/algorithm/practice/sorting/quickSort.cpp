
#include <bits/stdc++.h>
#include <vector>
using namespace std;

int partition(int arr[], int low, int high)
{
    int pivot = arr[low];
    int i = low;
    int j = high;
    while (i < j)
    {
        while (i <= high && arr[i] <= pivot)
        {
            i++;
        }
        while (j >= low && arr[j] > pivot)
        {
            j--;
        }
        if (i < j)
        {
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[low], arr[j]);

    return j;
}

void qs(int arr[], int low, int high)
{
    while (low < high)
    {
        int pivot_ind = partition(arr, low, high);
        qs(arr, low, pivot_ind - 1);
        qs(arr, pivot_ind + 1, high);
    }
    return;
}

int main()
{

    int arr[] = {2, 4, 1, 3, 6, 5, 2, 3, 7, 8, 9};
    int n = 11;
    qs(arr, 0, n - 1);
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }
    return 0;
}
// #include <iostream>
// #include <vector>

// using namespace std;

// int partition(vector<int> &arr, int low, int high)
// {
//     int pivot = arr[low];
//     int i = low;
//     int j = high;

//     while (i < j)
//     {
//         while (i <= high && arr[i] <= pivot)
//         {
//             i++;
//         }
//         while (j >= low && arr[j] > pivot)
//         {
//             j--;
//         }
//         if (i < j)
//         {
//             swap(arr[i], arr[j]);
//         }
//     }

//     swap(arr[low], arr[j]);

//     return j;
// }

// void quicksort(vector<int> &arr, int low, int high)
// {
//     if (low < high)
//     {
//         int pivot_index = partition(arr, low, high);
//         quicksort(arr, low, pivot_index - 1);
//         quicksort(arr, pivot_index + 1, high);
//     }
// }

// int main()
// {
//     vector<int> arr = {2, 4, 1, 3, 6, 5, 2, 3, 7, 8, 9};
//     int n = arr.size();
//     quicksort(arr, 0, n - 1);

//     for (int i = 0; i < n; i++)
//     {
//         cout << arr[i] << " ";
//     }

//     return 0;
// }
