// #include <iostream>
// #include <vector>
// #include <map>
// #include <algorithm>
// using namespace std;

// void display(vector<int> v)
// {
//     for (auto it : v)
//     {
//         cout << it << " ";
//     }
//     cout << endl;
// }

// void solve(int targ, vector<int> &candi, vector<int> &ans, vector<vector<int>> &v, map<int, int> mp)
// {
//     // if(ind==candi.size()){
//     //      return;
//     // }
//     if (targ == 0)
//     {
//         v.push_back(ans);
//         mp.clear();
//         return;
//     }
//     // map<int, int> mp;
//     for (int i = 0; i < candi.size(); i++)
//     {
//         if (candi[i] > targ)
//         {
//             break;
//         }
//         else if (candi[i] <= targ && mp[candi[i]] == 0)
//         {
//             mp[candi[i]]++;
//             ans.push_back(candi[i]);
//             solve(targ - candi[i], candi, ans, v, mp);
//             ans.pop_back();
//             mp[candi[i]]--;
//         }
//     }
// }

// vector<vector<int>> combinationSum2(vector<int> &candi, int targ)
// {
//     vector<vector<int>> v, v2;
//     vector<int> ans;
//     map<int, int> mp;
//     int ind = 0;
//     sort(candi.begin(), candi.end());
//     solve(targ, candi, ans, v, mp);

//     return v;
// }

// int main()
// {
//     vector<int> arr{1, 2, 3, 4, 5, 6, 7};
//     int target = 14;
//     vector<vector<int>> v;
//     v = combinationSum2(arr, target);
//     for (int i = 0; i < v.size(); i++)
//     {
//         display(v[i]);
//     }
// }