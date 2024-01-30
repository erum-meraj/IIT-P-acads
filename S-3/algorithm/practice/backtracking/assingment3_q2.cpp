#include <iostream>
using namespace std;

void display(int arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}

void solve(int ind, int ds[], int arr[], int n, int c = 0)
{
    if (ind >= n)
    {
        display(ds, 2 * n);
        return;
    }
}

int main()
{
    int n;
    cin >> n;
    int ds[2 * n];
    int arr[n];
    for (int i = 1; i <= n; i++)
    {
        arr[i - 1] = i;
    }

    return 0;
}