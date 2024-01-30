#include <iostream>
#include <vector>
using namespace std;

void display(vector<int> v)
{
    for (auto it : v)
    {
        cout << it << " ";
    }
    cout << endl;
}

void solve(int ind, vector<int> ds, vector<int> arr, int n, int target)
{
    if (ind >= n)
    {
        if (target == 0)
        {
            display(ds);
        }
        return;
    }
    if (arr[ind] <= target)
    {
        ds.push_back(arr[ind]);
        solve(ind + 1, ds, arr, n, target - arr[ind]);
        ds.pop_back();
    }

    solve(ind + 1, ds, arr, n, target);
}

int main()
{
    vector<int> v{1, 2, 3, 4, 5, 6, 7};
    vector<int> result;
    solve(0, result, v, 7, 14);

    return 0;
}