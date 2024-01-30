#include <iostream>
#include <bits/stdc++.h>
#include <vector>
using namespace std;

int fib(int n, int dp[])
{
    if (n <= 1)
    {
        return n;
    }
    else if (dp[n] != -1)
    {
        return dp[n];
    }
    return dp[n] = fib(n - 1, dp) + fib(n - 2, dp);
}

int main()
{
    int n = 5;
    int dp[5 + 1];
    memset(dp, -1, sizeof(dp));
    cout << fib(n, dp);
    return 0;
}