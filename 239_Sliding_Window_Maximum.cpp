/*
https://leetcode.com/problems/sliding-window-maximum/
You are given an array of integers nums, there is a sliding window of size k which is moving from the very left of the array to the very right. You can only see the k numbers in the window. Each time the sliding window moves right by one position.
Return the max sliding window.
Example 1:
Input: nums = [1,3,-1,-3,5,3,6,7], k = 3
Output: [3,3,5,5,6,7]
Explanation:
Window position                Max
---------------               -----
[1  3  -1] -3  5  3  6  7       3
 1 [3  -1  -3] 5  3  6  7       3
 1  3 [-1  -3  5] 3  6  7       5
 1  3  -1 [-3  5  3] 6  7       5
 1  3  -1  -3 [5  3  6] 7       6
 1  3  -1  -3  5 [3  6  7]      7
Example 2:
Input: nums = [1], k = 1
Output: [1]
Constraints:
1 <= nums.length <= 105
-104 <= nums[i] <= 104
1 <= k <= nums.length
*/

#include <bits/stdc++.h>
using namespace std;

// Time Complexity: O(n), Space Complexity: O(k)
vector<int> maxSlidingWindow(vector<int> &nums, int k)
{
    deque<int> dq;
    int l = 0, r = 0, n = nums.size();
    vector<int> res;
    while (r < n)
    {
        // maintain decreasing order
        while (!dq.empty() && nums[dq.back()] < nums[r])
        {
            dq.pop_back();
        }
        // insert elements to dq
        dq.push_back(r);
        // remove indices out of window
        if (l > dq.front())
        {
            dq.pop_front();
        }
        // valid window size -> generate res
        if (r - l + 1 == k)
        {
            res.push_back(nums[dq.front()]);
            l++;
        }
        r++;
    }
    return res;
}

int main()
{
    vector<int> nums = {1, 3, -1, -3, 5, 3, 6, 7};
    int k = 3;
    vector<int> result = maxSlidingWindow(nums, k);
    for (int num : result)
    {
        cout << num << " ";
    }
    cout << endl; // Output: 3 3 5 5 6 7
    nums = {1};
    k = 1;
    result = maxSlidingWindow(nums, k);
    for (int num : result)
    {
        cout << num << " ";
    }
    cout << endl; // Output: 1
    return 0;
}