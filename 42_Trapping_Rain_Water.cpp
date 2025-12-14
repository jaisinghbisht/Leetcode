/*
https://leetcode.com/problems/trapping-rain-water/
42. Trapping Rain Water
Given n non-negative integers representing an elevation map where the width of each bar is 1, compute how much water it can trap after raining.
Example 1:
Input: height = [0,1,0,2,1,0,1,3,2,1,2,1]
Output: 6
Explanation: The above elevation map (black section) is represented by array [0,1,0,2,1,0,1,3,2,1,2,1]. In this case, 6 units of rain water (blue section) are being trapped.
Example 2:
Input: height = [4,2,0,3,2,5]
Output: 9
Constraints:
n == height.length
1 <= n <= 2 * 104
0 <= height[i] <= 105
*/

#include <bits/stdc++.h>
using namespace std;

// Time Complexity: O(n), Space Complexity: O(n)
// where n is the size of the height array
// using prefix max and suffix max arrays
int trapUsingPrefixMaxAndSuffixMax(vector<int> &height)
{
    // we need to efficiently caculate the max height to the left and right of each index
    // we can do this by precomputing prefix max and suffix max arrays
    // then for each index, the water trapped is min(prefixMax[i], suffixMax[i]) - height[i]
    int n = height.size();
    vector<int> prefixMax(n, 0), suffixMax(n, 0);
    prefixMax[0] = height[0];
    suffixMax[n - 1] = height[n - 1];
    for (int i = 1; i < n; i++)
    {
        prefixMax[i] = max(prefixMax[i - 1], height[i]);
    }
    for (int i = n - 2; i >= 0; i--)
    {
        suffixMax[i] = max(suffixMax[i + 1], height[i]);
    }
    int water = 0;
    for (int i = 0; i < n; i++)
    {
        if (height[i] < prefixMax[i] && height[i] < suffixMax[i])
        {
            water += min(prefixMax[i], suffixMax[i]) - height[i];
        }
    }
    return water;
}

// Time Complexity: O(n), Space Complexity: O(1)
// where n is the size of the height array
// using two pointers and left max and right max variables
int trapUsingLeftMaxAndRightMax(vector<int> &height)
{
    int leftMax = 0, rightMax = 0, total = 0, l = 0, r = height.size() - 1;
    while (l < r)
    {
        // we process the smaller height side first since the water trapped depends on the smaller side
        if (height[l] <= height[r])
        {
            if (height[l] < leftMax)
            {
                total += leftMax - height[l];
            }
            else
            {
                leftMax = height[l];
            }
            l++;
        }
        else
        {
            if (height[r] < rightMax)
            {
                total += rightMax - height[r];
            }
            else
            {
                rightMax = height[r];
            }
            r--;
        }
    }
    return total;
}

int main()
{
    vector<int> height = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
    cout << trapUsingPrefixMaxAndSuffixMax(height) << endl; // Output: 6
    cout << trapUsingLeftMaxAndRightMax(height) << endl;    // Output: 6
    vector<int> height2 = {4, 2, 0, 3, 2, 5};
    cout << trapUsingPrefixMaxAndSuffixMax(height2) << endl; // Output: 9
    cout << trapUsingLeftMaxAndRightMax(height2) << endl;    // Output: 9
    return 0;
}