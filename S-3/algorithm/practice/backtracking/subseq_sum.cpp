#include <iostream>
#include <vector>
using namespace std;

void display(vector<int> arr)
{
    for (auto it : arr)
    {
        cout << it << " ";
    }
    cout << endl;
    return;
}

void solve(int ind, vector<int> ds, int arr[], int n, int target)
{
    if (ind >= n)
    {
        int sum = 0;
        for (int i = 0; i < ds.size(); i++)
        {
            sum += ds[i];
        }
        if (sum == target)
        {
            display(ds);
        }
        return;
    }
    ds.push_back(arr[ind]);
    solve(ind + 1, ds, arr, n, target);
    ds.pop_back();
    solve(ind + 1, ds, arr, n, target);
}

int main()
{

    int arr[] = {1, 2, 3, 4, 5, 6, 7};
    vector<int> v;
    solve(0, v, arr, 7, 15);

    return 0;
}