#include <bits/stdc++.h>
/*
UserId=Moinul
Password=Moinul909
*/
const std::string USER_ID = "Moinul";
const std::string PASSWORD = "Moinul909";

// Function to validate user login
bool login() {
    std::string userId, password;
    std::cout << "Enter User ID: ";
    std::cin >> userId;
    std::cout << "Enter Password: ";
    std::cin >> password;
    return (userId == USER_ID && password == PASSWORD);
}

// Function for Longest Increasing Subsequence (LIS)
int longestIncreasingSubsequence(const std::vector<int>& nums) {
    std::vector<int> lis(nums.size(), 1);
    for (size_t i = 1; i < nums.size(); ++i) {
        for (size_t j = 0; j < i; ++j) {
            if (nums[i] > nums[j] && lis[i] < lis[j] + 1) {
                lis[i] = lis[j] + 1;
            }
        }
    }
    return *std::max_element(lis.begin(), lis.end());
}

// Function for 0/1 Knapsack Problem
int knapsack(int W, const std::vector<int>& weights, const std::vector<int>& values) {
    int n = weights.size();
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(W + 1, 0));

    for (int i = 1; i <= n; ++i) {
        for (int w = 0; w <= W; ++w) {
            if (weights[i - 1] <= w) {
                dp[i][w] = std::max(dp[i - 1][w], dp[i - 1][w - weights[i - 1]] + values[i - 1]);
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }
    return dp[n][W];
}

// Function for Coin Change Problem
int coinChange(const std::vector<int>& coins, int amount) {
    std::vector<int> dp(amount + 1, amount + 1);
    dp[0] = 0;
    for (int i = 1; i <= amount; ++i) {
        for (const auto& coin : coins) {
            if (i >= coin) {
                dp[i] = std::min(dp[i], dp[i - coin] + 1);
            }
        }
    }
    return (dp[amount] > amount) ? -1 : dp[amount];
}

// Function for Traveling Salesman Problem (TSP)
int tsp(std::vector<std::vector<int>>& graph, int pos, int visited, std::vector<std::vector<int>>& dp) {
    int n = graph.size();
    if (visited == (1 << n) - 1) {
        return graph[pos][0]; // return to starting city
    }

    if (dp[pos][visited] != -1) {
        return dp[pos][visited];
    }

    int ans = INT_MAX;
    for (int city = 0; city < n; ++city) {
        if ((visited & (1 << city)) == 0) {
            int newAns = graph[pos][city] + tsp(graph, city, visited | (1 << city), dp);
            ans = std::min(ans, newAns);
        }
    }
    return dp[pos][visited] = ans;
}

// UI to select dynamic programming problem and input parameters
void displayMenu() {
    std::cout << "\nDynamic Programming Problem Solver\n";
    std::cout << "1. Longest Increasing Subsequence (LIS)\n";
    std::cout << "2. 0/1 Knapsack Problem\n";
    std::cout << "3. Coin Change Problem\n";
    std::cout << "4. Traveling Salesman Problem (TSP)\n";
    std::cout << "5. Exit\n";
    std::cout << "Select an option: ";
}

int main() {
    // User login
    if (!login()) {
        std::cout << "Invalid credentials. Access denied.\n";
        return 1;
    }
    std::cout << "Login successful. Welcome to the Dynamic Programming Problem Solver.\n";

    while (true) {
        displayMenu();
        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1: { // Longest Increasing Subsequence (LIS)
                std::cout << "\nEnter the number of elements in the sequence: ";
                int n;
                std::cin >> n;
                std::vector<int> nums(n);
                std::cout << "Enter the elements of the sequence: ";
                for (int& num : nums) std::cin >> num;

                int lisLength = longestIncreasingSubsequence(nums);
                std::cout << "Length of the Longest Increasing Subsequence: " << lisLength << "\n";
                break;
            }
            case 2: { // 0/1 Knapsack Problem
                std::cout << "\nEnter the number of items: ";
                int n;
                std::cin >> n;
                std::vector<int> weights(n), values(n);
                std::cout << "Enter the weights of the items: ";
                for (int& w : weights) std::cin >> w;
                std::cout << "Enter the values of the items: ";
                for (int& v : values) std::cin >> v;
                std::cout << "Enter the capacity of the knapsack: ";
                int W;
                std::cin >> W;

                int maxProfit = knapsack(W, weights, values);
                std::cout << "Maximum profit that can be obtained: " << maxProfit << "\n";
                break;
            }
            case 3: { // Coin Change Problem
                std::cout << "\nEnter the number of coin denominations: ";
                int n;
                std::cin >> n;
                std::vector<int> coins(n);
                std::cout << "Enter the coin denominations: ";
                for (int& coin : coins) std::cin >> coin;
                std::cout << "Enter the amount: ";
                int amount;
                std::cin >> amount;

                int minCoins = coinChange(coins, amount);
                if (minCoins == -1) {
                    std::cout << "No solution exists for the given amount\n";
                    std::cout << "No solution exists for the given amount.\n";
                } else {
                    std::cout << "Minimum number of coins needed: " << minCoins << "\n";
                }
                break;
            }
            case 4: { // Traveling Salesman Problem (TSP)
                std::cout << "\nEnter the number of cities: ";
                int n;
                std::cin >> n;
                std::vector<std::vector<int>> graph(n, std::vector<int>(n));
                std::cout << "Enter the adjacency matrix (enter 0 for no path between cities):\n";
                for (int i = 0; i < n; ++i) {
                    for (int j = 0; j < n; ++j) {
                        std::cin >> graph[i][j];
                        if (i == j) graph[i][j] = 0; // Distance to itself is 0
                        if (graph[i][j] == 0 && i != j) graph[i][j] = INT_MAX; // Set no path as infinity
                    }
                }

                // Initialize dp array for memoization
                std::vector<std::vector<int>> dp(n, std::vector<int>((1 << n), -1));

                int minCost = tsp(graph, 0, 1, dp);
                std::cout << "Minimum cost of visiting all cities and returning to the start: " << minCost << "\n";
                break;
            }
            case 5: { // Exit the program
                std::cout << "Exiting the program. Thank you!\n";
                return 0;
            }
            default:
                std::cout << "Invalid option. Please select a valid option.\n";
                break;
        }
    }

    return 0;
}
