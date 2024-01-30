#include <iostream>
#include <vector>
using namespace std;

int cnt = 0;

void display(vector<char> v)
{
    for (auto it : v)
    {
        cout << it;
    }
    cout << endl;
}

void solve(vector<char> &ds, string arr, int n, int freq[], int len)
{
    if (ds.size() == len)
    {
        display(ds);
        cnt++;
        return;
    }

    for (int i = 0; i < n; i++)
    {

        if (ds.size() == 0 || (ds[ds.size() - 1] != arr[i]))
        {

            ds.push_back(arr[i]);
            // freq[i] = 1;
            solve(ds, arr, n, freq, len);
            // freq[i] = 0;
            ds.pop_back();
        }
    }
}

int main()
{
    int n;
    cin >> n;
    string arr;
    cin >> arr;
    int len;
    cin >> len;
    vector<char> v;
    int freq[n];
    for (int i = 0; i < n; i++)
    {
        freq[i] = 0;
    }

    // solve(0, v, arr, 3);
    solve(v, arr, 3, freq, len);
    cout << cnt << endl;
    return 0;
}