/*
https://leetcode.com/problems/climbing-stairs/description/
70. Climbing Stairs
You are climbing a staircase. It takes n steps to reach the top.
Each time you can either climb 1 or 2 steps. In how many distinct ways can you climb to the top?
Example 1:
Input: n = 2
Output: 2
Explanation: There are two ways to climb to the top.
1. 1 step + 1 step
2. 2 steps
Example 2:
Input: n = 3
Output: 3
Explanation: There are three ways to climb to the top.
1. 1 step + 1 step + 1 step
2. 1 step + 2 steps
3. 2 steps + 1 step
Constraints:
1 <= n <= 45
*/

#include <bits/stdc++.h>
using namespace std;

// Recursive Approach
// Time Complexity: O(2^n)
// Space Complexity: O(n) [Auxiliary Stack Space]
int climbStairsRecursion(int n)
{
    if (n == 0)
    {
        return 1;
    }
    if (n < 0)
    {
        return 0;
    }
    return climbStairsRecursion(n - 1) + climbStairsRecursion(n - 2);
}

int helper(int n, vector<int> &dp)
{
    if (n == 0)
    {
        return 1;
    }
    if (n < 0)
    {
        return 0;
    }
    if (dp[n] != -1)
    {
        return dp[n];
    }
    return dp[n] = helper(n - 1, dp) + helper(n - 2, dp);
}

// Memoization Approach
// Time Complexity: O(n)
// Space Complexity: O(n) [Auxiliary Stack Space + DP Array]
int climbStairsMemoization(int n)
{
    vector<int> dp(n + 1, -1);
    return helper(n, dp);
}

// Tabulation Approach
// Time Complexity: O(n)
// Space Complexity: O(1)
int climbStairsTabulation(int n)
{
    if (n <= 1)
        return 1;
    int prev2 = 1, prev1 = 1;
    for (int i = 2; i <= n; i++)
    {
        int curr = prev1 + prev2;
        prev2 = prev1;
        prev1 = curr;
    }
    return prev1;
}

int main()
{
    int n = 2;
    cout << climbStairsRecursion(n) << endl; // Output: 2
    n = 3;
    cout << climbStairsMemoization(n) << endl; // Output: 3
    n = 5;
    cout << climbStairsTabulation(n) << endl; // Output: 8
    return 0;
}