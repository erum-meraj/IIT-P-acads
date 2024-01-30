#include <iostream>
#include <vector>
using namespace std;

void solve(vector<int> ds, vector<int> arr, int n, vector<vector<int>> result, int freq[])
{
    if (ds.size() == n)
    {
        result.push_back(ds);
        return;
    }
    for (int i = 0; i < n; i++)
    {
        if (freq[i] == 0)
        {
            ds.push_back(arr[i]);
            freq[i] = 1;
            solve(ds, arr, n, result, freq);
            ds.pop_back();
            freq[i] = 0;
        }
    }
}

int main()
{
    vector<int>

        return 0;
}