#include <iostream>
#include <vector>
#include <string>
#include <bits/stdc++.h>
using namespace std;

int display(vector<char> v)
{
    for (int i = 0; i < v.size(); i++)
    {
        cout << v[i] << " ";
    }
    cout << endl;
}

int check_edge(string n1, string n2)
{
    vector<char> unique1;
    vector<char> unique2;
    // cout << n1 << n2;
    for (int i = 0; i < 5; i++)
    {
        auto it1 = find(unique1.begin(), unique1.end(), n1[i]);
        if (it1 != unique1.end())
        {
            continue;
        }
        unique1.push_back(n1[i]);
    }
    for (int i = 0; i < 5; i++)
    {

        auto it2 = find(unique2.begin(), unique2.end(), n2[i]);
        if (it2 != unique2.end())
        {
            continue;
        }
        unique2.push_back(n2[i]);
    }

    display(unique1);
    display(unique2);
    int cmn = 0;
    for (int i = 0; i < unique1.size(); i++)
    {
        for (int j = 0; j < unique2.size(); j++)
        {
            if (unique1[i] == unique2[j])
            {
                cmn++;
            }
        }
    }

    return cmn;
}

int span(int V, vector<vector<int>> adj[])
{
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    vector<int> vis(V, 0);
    pq.push({0, 0});
    int result = 0;
    while (pq.empty())
    {
        auto it = pq.top();
        pq.pop();
        int node = it.second;
        int wt = it.first;
        if (vis[node] == 1)
        {
            continue;
        }
        else
        {
            vis[node] = 1;
            result += wt;
            for (auto it : adj[node])
            {
                int adjNode = it[0];
                int edge_wt = it[1];
                if (vis[node] != 1)
                {
                    pq.push({edge_wt, adjNode});
                }
            }
        }
    }
    return result;
}

int main()
{
    // get graph
    int no_nodes;
    cin >> no_nodes;
    int matrix[no_nodes][no_nodes];
    string nodes[no_nodes];
    for (int i = 0; i < no_nodes; i++)
    {
        cin >> nodes[i];
    }
    for (int i = 0; i < no_nodes; i++)
    {
        for (int j = i; j < no_nodes; j++)
        {
            if (i == j)
            {
                matrix[i][j] = 0;
                continue;
            }
            int cmn = check_edge(nodes[i], nodes[j]);
            cout << "  " << cmn << endl;
            if (cmn >= 2)
            {
                matrix[i][j] = cmn;
            }
            else
            {
                matrix[i][j] = 0;
            }
        }
    }

    for (int i = 0; i < no_nodes; i++)
    {

        for (int j = 0; j < no_nodes; j++)
        {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}