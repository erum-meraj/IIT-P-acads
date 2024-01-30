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

int solve(int ind, vector<int> ds, int arr[], int n, int target)
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
            return 1;
        }
        return 0;
    }
    ds.push_back(arr[ind]);
    int l = solve(ind + 1, ds, arr, n, target);
    ds.pop_back();
    int r = solve(ind + 1, ds, arr, n, target);
    return l + r;
}

int main()
{

    int arr[] = {1, 2, 3, 4, 5, 6, 7};
    vector<int> v;
    cout << "*****" << endl;
    cout << solve(0, v, arr, 7, 20);

    return 0;
}