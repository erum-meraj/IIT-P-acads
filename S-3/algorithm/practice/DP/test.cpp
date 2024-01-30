#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Structure to represent a ball
struct Ball
{
    int weight;
    int price;
};

// Function to find the maximum total price and selected balls
pair<int, vector<int>> maxTotalPriceAndSelectedBalls(vector<Ball> &balls, int maxWeight)
{
    int n = balls.size();
    vector<vector<int>> dp(n + 1, vector<int>(maxWeight + 1, 0));
    vector<vector<bool>> selected(n + 1, vector<bool>(maxWeight + 1, false));

    for (int i = 1; i <= n; i++)
    {
        for (int w = 0; w <= maxWeight; w++)
        {
            if (balls[i - 1].weight > w)
            {
                dp[i][w] = dp[i - 1][w];
            }
            else
            {
                int take = dp[i - 1][w - balls[i - 1].weight] + balls[i - 1].price;
                int skip = dp[i - 1][w];
                if (take >= skip)
                {
                    dp[i][w] = take;
                    selected[i][w] = true;
                }
                else
                {
                    dp[i][w] = skip;
                    selected[i][w] = false;
                }
            }
        }
    }

    int maxPrice = dp[n][maxWeight];
    vector<int> chosenBalls;

    int i = n, w = maxWeight;
    while (i > 0 && w > 0)
    {
        if (selected[i][w])
        {
            chosenBalls.push_back(i - 1);
            w -= balls[i - 1].weight;
        }
        i--;
    }

    reverse(chosenBalls.begin(), chosenBalls.end());

    return make_pair(maxPrice, chosenBalls);
}

int main()
{
    int n, maxWeight;
    cout << "Enter the number of balls: ";
    cin >> n;
    cout << "Enter the maximum weight capacity of the basket: ";
    cin >> maxWeight;

    vector<Ball> balls(n);

    cout << "Enter the weight and price of each ball:" << endl;
    for (int i = 0; i < n; i++)
    {
        cin >> balls[i].weight >> balls[i].price;
    }

    pair<int, vector<int>> result = maxTotalPriceAndSelectedBalls(balls, maxWeight);

    cout << "Maximum total price: " << result.first << endl;
    cout << "Selected balls: ";
    for (int i = 0; i < result.second.size(); i++)
    {
        cout << result.second[i] << " ";
    }
    cout << endl;

    return 0;
}