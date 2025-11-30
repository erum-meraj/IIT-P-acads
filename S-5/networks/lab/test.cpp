// #include <iostream>
// #include <vector>
// #include <functional>
// #include <array>

// using namespace std;

// #define long long long long

// long long find_max(long long a, long long b) {
//     return (a > b) ? a : b;
// }

// int getMinServers(int n, vector<int> f, vector<int> t, vector<int> w, vector<int> v) {
//     vector<long long> size(n), maxDistance(n);
//     vector<vector<array<long long, 2>>> adjacencyList(n);

//     for (long long i = 0; i < f.size(); i++) {
//         f[i]--;
//         t[i]--;
//         adjacencyList[f[i]].push_back({t[i], w[i]});
//         adjacencyList[t[i]].push_back({f[i], w[i]});
//     }

//     long long answer = 0;

//     function<void(long long, long long)> dfs1 = [&](long long u, long long parent) {
//         size[u] = 1;
//         long long idx = 0;
//         while (idx < adjacencyList[u].size()) {
//             long long vertex = adjacencyList[u][idx][0];
//             long long weight = adjacencyList[u][idx][1];
//             if (vertex != parent) {
//                 maxDistance[vertex] = find_max(maxDistance[u] + weight, weight);
//                 dfs1(vertex, u);
//                 size[u] += size[vertex];
//             }
//             idx++;
//         }
//     };

//     function<void(long long, long long)> dfs2 = [&](long long u, long long parent) {
//         if (u != 0 && maxDistance[u] > v[u]) {
//             answer += size[u];
//         } else {
//             long long idx = 0;
//             while (idx < adjacencyList[u].size()) {
//                 long long vertex = adjacencyList[u][idx][0];
//                 if (vertex != parent) {
//                     dfs2(vertex, u);
//                 }
//                 idx++;
//             }
//         }
//     };

//     dfs1(0, -1);
//     dfs2(0, -1);

//     return answer;
// }

// int main() {
//     // Example usage
//     int n = 4;
//     vector<int> f = {1,2,3};
//     vector<int> t = {2, 3, 4};
//     vector<int> w = {1, -10, -5};
//     vector<int> v = {0, -1, -2, -3};

//     cout << getMinServers(n, f, t, w, v) << endl;

//     return 0;
// }

#include <iostream>
#include <vector>
#include <functional>
#include <array>

using namespace std;


long long max_value(long long x, long long y) {
    return (x > y) ? x : y;
}

int getMinServers(int server_nodes, vector<int> server_from, vector<int> server_to, vector<int> server_weight, vector<int> minActivity) {
    vector<long long> subtreeSize(server_nodes), maxReach(server_nodes);
    vector<vector<array<long long, 2>>> server_graphh(server_nodes);

    long long result = 0;

    for (long long i = 0; i < server_from.size(); i++) {
        server_to[i]--;
        server_from[i]--;
        
        server_graphh[server_from[i]].push_back({server_to[i], server_weight[i]});
        server_graphh[server_to[i]].push_back({server_from[i], server_weight[i]});
    }

    

    function<void(long long, long long)> depthFirstSearch1 = [&](long long node, long long parent) {
        long long j = 0;
        
        subtreeSize[node] = 1;
        
        while (j < server_graphh[node].size()) {
            long long adjacent = server_graphh[node][j][0];
            long long edgeWeight = server_graphh[node][j][1];
            if (adjacent != parent) {
                maxReach[adjacent] = max_value(maxReach[node] + edgeWeight, edgeWeight);
                depthFirstSearch1(adjacent, node);
                subtreeSize[node] += subtreeSize[adjacent];
            }
            j++;
        }
    };

    function<void(long long, long long)> depthFirstSearch2 = [&](long long node, long long parent) {
        if (node != 0 && maxReach[node] > minActivity[node]) {
            result += subtreeSize[node];
        } else {
            long long j = 0;
            while (j < server_graphh[node].size()) {
                long long adjacent = server_graphh[node][j][0];
                if (adjacent != parent) {
                    depthFirstSearch2(adjacent, node);
                }
                j++;
            }
        }
    };

    depthFirstSearch1(0, -1);
    depthFirstSearch2(0, -1);

    return result;
}

int main() {

    int server_nodes = 4;
    vector<int> server_from = {1, 2, 3};
    vector<int> server_to = {2, 3, 4};
    vector<int> server_weight = {1, -10, -5};
    vector<int> minActivity = {0, -1, -2, -3};

    cout << getMinServers(server_nodes, server_from, server_to, server_weight, minActivity) << endl;

    return 0;
}
