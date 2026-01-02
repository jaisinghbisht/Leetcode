/*
https://leetcode.com/problems/house-robber-ii/description/
213. House Robber II
You are a professional robber planning to rob houses along a street. Each house has a certain amount of money stashed. All houses at this place are arranged in a circle. That means the first house is the neighbor of the last one. Meanwhile, adjacent houses have a security system connected, and it will automatically contact the police if two adjacent houses were broken into on the same night.
Given an integer array nums representing the amount of money of each house, return the maximum amount of money you can rob tonight without alerting the police.
Example 1:
Input: nums = [2,3,2]
Output: 3
Explanation: You cannot rob house 1 (money = 2) and then rob house 3 (money = 2), because they are adjacent houses.
Example 2:
Input: nums = [1,2,3,1]
Output: 4
Explanation: Rob house 1 (money = 1) and then rob house 3 (money = 3).
Total amount you can rob = 1 + 3 = 4.
Example 3:
Input: nums = [1,2,3]
Output: 3
Constraints:
1 <= nums.length <= 100
0 <= nums[i] <= 1000
*/

#include <bits/stdc++.h>
using namespace std;

int robHelper(vector<int> &nums, int l, int r)
{
    int prev1 = 0, prev2 = 0;
    for (int i = l; i <= r; i++)
    {
        int curr = max(prev1, nums[i] + prev2);
        prev2 = prev1;
        prev1 = curr;
    }
    return prev1;
}

// Time Complexity: O(n)
// Space Complexity: O(1)
int rob(vector<int> &nums)
{
    int n = nums.size();
    if (n == 1)
        return nums[0];
    int case1 = robHelper(nums, 0, n - 2);
    int case2 = robHelper(nums, 1, n - 1);
    return max(case1, case2);
}

int main()
{
    vector<int> nums = {2, 3, 2};
    cout << rob(nums) << endl; // Output: 3
    nums = {1, 2, 3, 1};
    cout << rob(nums) << endl; // Output: 4
    nums = {1, 2, 3};
    cout << rob(nums) << endl; // Output: 3
    return 0;
}