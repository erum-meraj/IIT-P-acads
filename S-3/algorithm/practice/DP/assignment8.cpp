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
    vector<int> wt = {4, 2, 5, 2};
    vector<int> val = {10, 4, 10, 4};
    int W = 7;
    int n = wt.size();
    vector<vector<int>> dp(n, vector<int>(W + 1, 0));
    vector<vector<int>> selected(n, vector<int>(W + 1, false));

    // cout << solve(0, W, wt, val, n, dp);
    for (int i = wt[0]; i <= W; i++)
    {
        dp[0][i] = val[0];
    }
    for (int i = 1; i < n; i++)
    {
        for (int limit = 0; limit <= W; limit++)
        {
            int r = 0 + dp[i - 1][limit];
            dp[i][limit] = (r);
            selected[i][limit] = false;
            if (wt[i] <= limit)
            {
                int l = val[i] + dp[i - 1][limit - wt[i]];
                dp[i][limit] = max(l, r);
                if (dp[i][limit] == l)
                    selected[i][limit] = true;
                // cout << wt[i];
            }
        }
    }
    cout << dp[n - 1][W] << endl;
    int i = 0;
    int w = W;
    while (i > 0 && w > 0)
    {
        /* code */
    }

    return 0;
}