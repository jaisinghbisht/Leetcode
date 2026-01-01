/*
https://www.geeksforgeeks.org/problems/geek-jump/1
Frog Jump
Given an integer array height[] where height[i] represents the height of the i-th stair, a frog starts from the first stair and wants to reach the last stair. From any stair i, the frog has two options: it can either jump to the (i+1)th stair or the (i+2)th stair. The cost of a jump is the absolute difference in height between the two stairs. Determine the minimum total cost required for the frog to reach the last stair.
Example:
Input: heights[] = [20, 30, 40, 20]
Output: 20
Explanation:  Minimum cost is incurred when the frog jumps from stair 0 to 1 then 1 to 3:
jump from stair 0 to 1: cost = |30 - 20| = 10
jump from stair 1 to 3: cost = |20 - 30| = 10
Total Cost = 10 + 10 = 20
Input: heights[] = [30, 20, 50, 10, 40]
Output: 30
Explanation: Minimum cost will be incurred when frog jumps from stair 0 to 2 then 2 to 4:
jump from stair 0 to 2: cost = |50 - 30| = 20
jump from stair 2 to 4: cost = |40 - 50| = 10
Total Cost = 20 + 10 = 30
Constraints:
1 ≤ height.size() ≤ 105
0 ≤ height[i] ≤ 104
*/

#include <bits/stdc++.h>
using namespace std;

// Recursive Approach
// Time Complexity: O(2^n)
// Space Complexity: O(n) [Auxiliary Stack Space]
int helperRecursive(int i, vector<int> &height, const int &n)
{
    if (i == n - 1)
    {
        return 0;
    }
    int oneJump = abs(height[i] - height[i + 1]) + helperRecursive(i + 1, height, n);
    int twoJump = INT_MAX;
    if (i + 2 < n)
    {
        twoJump = abs(height[i] - height[i + 2]) + helperRecursive(i + 2, height, n);
    }
    return min(oneJump, twoJump);
}

int minCostRecursive(vector<int> &height)
{
    int n = height.size();
    return helperRecursive(0, height, n);
}

// Memoization Approach
// Time Complexity: O(n)
// Space Complexity: O(n) [Auxiliary Stack Space] + O(n) [DP Array]
int helperMemoization(int i, vector<int> &height, const int &n, vector<int> &dp)
{
    if (i == n - 1)
    {
        return 0;
    }
    if (dp[i] != -1)
        return dp[i];
    int oneJump = abs(height[i] - height[i + 1]) + helperMemoization(i + 1, height, n, dp);
    int twoJump = INT_MAX;
    if (i + 2 < n)
    {
        twoJump = abs(height[i] - height[i + 2]) + helperMemoization(i + 2, height, n, dp);
    }
    return dp[i] = min(oneJump, twoJump);
}
int minCostMemoization(vector<int> &height)
{
    int n = height.size();
    vector<int> dp(n, -1);
    return helperMemoization(0, height, n, dp);
}

// Tabulation Approach
// Time Complexity: O(n)
// Space Complexity: O(1)
int minCostTabulation(vector<int> &height)
{
    int n = height.size();
    int prev2 = 0, prev1 = 0;
    for (int i = 1; i < n; i++)
    {
        int oneJump = prev1 + abs(height[i] - height[i - 1]);
        int twoJump = INT_MAX;
        if (i > 1)
        {
            twoJump = prev2 + abs(height[i] - height[i - 2]);
        }
        int curr = min(oneJump, twoJump);
        prev2 = prev1;
        prev1 = curr;
    }
    return prev1;
}

int main()
{
    vector<int> height1 = {20, 30, 40, 20};
    cout << "Minimum Cost (Recursive): " << minCostRecursive(height1) << endl;     // Output: 20
    cout << "Minimum Cost (Memoization): " << minCostMemoization(height1) << endl; // Output: 20
    cout << "Minimum Cost (Tabulation): " << minCostTabulation(height1) << endl;   // Output: 20

    vector<int> height2 = {30, 20, 50, 10, 40};
    cout << "Minimum Cost (Recursive): " << minCostRecursive(height2) << endl;     // Output: 30
    cout << "Minimum Cost (Memoization): " << minCostMemoization(height2) << endl; // Output: 30
    cout << "Minimum Cost (Tabulation): " << minCostTabulation(height2) << endl;   // Output: 30

    return 0;
}