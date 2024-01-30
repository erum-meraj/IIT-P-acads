#include <iostream>
using namespace std;

int cnt(int num, int digit)
{
    int c = 0;
    while (num > 0)
    {
        if (num % 10 == digit)
        {
            c++;
        }
        num /= 10;
    }
    return c;
}

int solve(int n, int digit)
{

    if (n < 0)
    {
        return 0;
    }
    return cnt(n, digit) + solve(n - 1, digit);
}

int main()
{
    int n;
    cin >> n;
    int digit;
    cin >> digit;
    cout << solve(n, digit);

    return 0;
}