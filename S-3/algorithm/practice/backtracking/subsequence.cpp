#include <iostream>
#include <vector>
using namespace std;
void display(vector<int> arr, int ind)
{
    for (auto it : arr)
    {
        cout << it << " ";
    }
    cout << endl;
}

void solve(int ind, vector<int> &ds, int arr[], int n)
{
    if (ind >= n)
    {
        display(ds, ind);
        return;
    }
    ds.push_back(arr[ind]);
    solve(ind + 1, ds, arr, n);
    ds.pop_back();

    // not added
    solve(ind + 1, ds, arr, n);
}

int main()
{
    int arr[] = {1, 2, 3};
    vector<int> v;

    solve(0, v, arr, 3);
    return 0;
}