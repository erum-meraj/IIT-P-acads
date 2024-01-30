#include <bits/stdc++.h>
#include <vector>
using namespace std;

int solve(int ind, int w, vector<int> weigth, vector<int> value, int n, vector<vector<int>> &dp)
{
    if (ind == n - 1)
    {
        if (weigth[ind] <= w)
        {
            return value[ind];
        }
        return 0;
    }
    if (dp[ind][w] != -1)
    {
        return dp[ind][w];
    }
    if (weigth[ind] <= w)
    {
        int l = value[ind] + solve(ind + 1, w - weigth[ind], weigth, value, n, dp);
        int r = 0 + solve(ind + 1, w, weigth, value, n, dp);
        return dp[ind][w] = max(l, r);
    }
    int r = 0 + solve(ind + 1, w, weigth, value, n, dp);
    return dp[ind][w] = r;
}

int main()
{
    vector<int> wt = {1, 2, 4, 5};
    vector<int> val = {5, 4, 8, 6};
    int W = 5;
    int n = wt.size();
    vector<vector<int>> dp(n, vector<int>(W + 1, -1));
    cout << solve(0, W, wt, val, n, dp);
    return 0;
}