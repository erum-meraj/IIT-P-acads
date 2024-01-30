#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> result;

void display(vector<int> v)
{
    for (auto it : v)
    {
        cout << it << " ";
    }
    cout << endl;
}

void solve(int ind, vector<int> &ds, int arr[], int n)
{

    if (ind >= n)
    {
        result.push_back(ds);
        return;
    }
    ds.push_back(arr[ind]);
    solve(ind + 1, ds, arr, n);
    ds.pop_back();

    solve(ind + 1, ds, arr, n);
}

int main()
{
    int arr[] = {1, 2, 3};
    vector<int> v;
    solve(0, v, arr, 3);
    // print vectors of vectors
    for (int i = 0; i < result.size(); i++)
    {
        display(result[i]);
    }
    return 0;
}