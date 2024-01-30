#include <iostream>
#include <vector>
#include <string>
#include <bits/stdc++.h>
using namespace std;

vector<int> dijk(int V, int S, vector<vector<int>> adj[])
{
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    vector<int> distance(V, INT_MAX);
    distance[S] = 0;
    pq.push({0, S});
    while (!pq.empty())
    {
        int node = pq.top().second;
        int d = pq.top().first;
        pq.pop();
        for (auto it : adj[node])
        {
            int v = it[0];
            int w = it[1];
            int new_d = d + w;
            if (new_d < distance[v])
            {
                distance[v] = new_d;
                pq.push({v, new_d});
            }
        }
    }
    return distance;
}

int main()
{

    return 0;
}