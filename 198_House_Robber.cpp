/*
https://leetcode.com/problems/house-robber/description/
198. House Robber
You are a professional robber planning to rob houses along a street. Each house has a certain amount of money stashed, the only constraint stopping you from robbing each of them is that adjacent houses have security systems connected and it will automatically contact the police if two adjacent houses were broken into on the same night.
Given an integer array nums representing the amount of money of each house, return the maximum amount of money you can rob tonight without alerting the police.
Example 1:
Input: nums = [1,2,3,1]
Output: 4
Explanation: Rob house 1 (money = 1) and then rob house 3 (money = 3).
Total amount you can rob = 1 + 3 = 4.
Example 2:
Input: nums = [2,7,9,3,1]
Output: 12
Explanation: Rob house 1 (money = 2), rob house 3 (money = 9) and rob house 5 (money = 1).
Total amount you can rob = 2 + 9 + 1 = 12.
Constraints:
1 <= nums.length <= 100
0 <= nums[i] <= 400
*/

#include <bits/stdc++.h>
using namespace std;

int solveRecursive(int idx, vector<int> &nums, const int n)
{
    if (idx >= n)
    {
        return 0;
    }
    // option 1: rob current house, skip next
    int take = nums[idx] + solveRecursive(idx + 2, nums, n);
    // option 2: skip current house
    int skip = solveRecursive(idx + 1, nums, n);
    return max(take, skip);
}
// Time Complexity: O(2^n) in the worst case
// Space Complexity: O(n) for the recursion stack
int robRecursive(vector<int> &nums)
{
    return solveRecursive(0, nums, nums.size());
}

int solveMemoization(int idx, vector<int> &nums, const int n, vector<int> &dp)
{
    if (idx >= n)
        return 0;
    if (dp[idx] != -1)
        return dp[idx];
    // option 1: rob current house, skip next
    int take = nums[idx] + solveMemoization(idx + 2, nums, n, dp);
    // option 2: skip current house
    int skip = solveMemoization(idx + 1, nums, n, dp);
    return dp[idx] = max(take, skip);
}

// Time Complexity: O(n)
// Space Complexity: O(n) for the dp array and O(n) for the recursion stack
int robMemoization(vector<int> &nums)
{
    int n = nums.size();
    vector<int> dp(n, -1);
    return solveMemoization(0, nums, nums.size(), dp);
}

// Time Complexity: O(n)
// Space Complexity: O(1)
int robTabulation(vector<int> &nums)
{
    int n = nums.size();
    int prev1 = 0, prev2 = 0;
    for (int i = 0; i < n; i++)
    {
        int curr = max(prev1, nums[i] + prev2);
        prev2 = prev1;
        prev1 = curr;
    }
    return prev1;
}

int main()
{
    vector<int> nums = {1, 2, 3, 1};
    cout << robTabulation(nums) << endl; // Output: 4
    nums = {2, 7, 9, 3, 1};
    cout << robTabulation(nums) << endl; // Output: 12
    return 0;
}