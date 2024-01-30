#include <bits/stdc++.h>
#include <vector>
using namespace std;

int find_ways(int n, vector<int> &heights, int dp[])
{
    if (n == 0)
    {
        return 0;
    }
    if (dp[n] != -1)
    {
        return dp[n];
    }
    int l = find_ways(n - 1, heights, dp) + abs(heights[n] - heights[n - 1]);
    int r = INT_MAX;
    if (n > 1)
        r = find_ways(n - 2, heights, dp) + abs(heights[n] - heights[n - 2]);
    return dp[n] = min(l, r);
}

int main()
{
    int n = 3;
    int k = 1;
    // vector<int> v{10, 20, 30, 10};
    vector<int> height{10, 20, 10};
    vector<int> dp(n);
    dp[0] = 0;
    int temp = INT_MAX;
    for (int j = 1; j <= n; j++)
    {
        for (int i = 1; i <= k; i++)
        {
            if (j - i >= 0)
            {
                int jump = dp[j - i] + abs(height[j] - height[j - i]);
                temp = min(temp, jump);
            }
        }
        dp[j] = temp;
    }
    cout << dp[n - 1];
}