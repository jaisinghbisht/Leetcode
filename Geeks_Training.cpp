/*
https://www.geeksforgeeks.org/problems/geeks-training/1
Geek's Training
Geek is going for a training program for n days. He can perform any of these activities: Running, Fighting, and Learning Practice. Each activity has some point on each day. As Geek wants to improve all his skills, he can't do the same activity on two consecutive days. Given a 2D array arr[][] of size n where arr[i][0], arr[i][1], and arr[i][2] represent the merit points for Running, Fighting, and Learning on the i-th day, determine the maximum total merit points Geek can achieve .
Example:
Input: arr[]= [[1, 2, 5], [3, 1, 1], [3, 3, 3]]
Output: 11
Explanation: Geek will learn a new move and earn 5 point then on second day he will do running and earn 3 point and on third day he will do fighting and earn 3 points so, maximum merit point will be 11.
Input: arr[]= [[1, 1, 1], [2, 2, 2], [3, 3, 3]]
Output: 6
Explanation: Geek can perform any activity each day while adhering to the constraints, in order to maximize his total merit points as 6.
Input: arr[]= [[4, 2, 6]]
Output: 6
Explanation: Geek will learn a new move to make his merit points as 6.
Constraint:
1 <=  n <= 105
1 <=  arr[i][j] <= 100
*/

#include <bits/stdc++.h>
using namespace std;

int maximumPointsRecursiveHelper(int idx, int prevIdx, const int n, vector<vector<int>> &points)
{
    if (idx >= n)
    {
        return 0;
    }
    int take1 = 0, take2 = 0, take3 = 0;
    // take 1st
    if (prevIdx != 0)
        take1 = points[idx][0] + maximumPointsRecursiveHelper(idx + 1, 0, n, points);
    // take 2nd
    if (prevIdx != 1)
        take2 = points[idx][1] + maximumPointsRecursiveHelper(idx + 1, 1, n, points);
    // take 3rd
    if (prevIdx != 2)
        take3 = points[idx][2] + maximumPointsRecursiveHelper(idx + 1, 2, n, points);
    // choose best
    return max(take1, max(take2, take3));
}

// Recursive
// Time Complexity: O(3^N), where N is the number of days.
// Space Complexity: O(N), for the recursion stack.
int maximumPointsRecursive(vector<vector<int>> &arr)
{
    return maximumPointsRecursiveHelper(0, -1, arr.size(), arr);
}

int maximumPointsMemoizationHelper(int idx, int prevIdx, const int n, vector<vector<int>> &points, vector<vector<int>> &dp)
{
    if (idx >= n)
    {
        return 0;
    }
    // check if already computed, 3 is our dummy value, meaning not computed yet
    if (dp[idx][prevIdx] != -1)
        return dp[idx][prevIdx];
    int take1 = 0, take2 = 0, take3 = 0;
    // take 1st
    if (prevIdx != 0)
        take1 = points[idx][0] + maximumPointsMemoizationHelper(idx + 1, 0, n, points, dp);
    // take 2nd
    if (prevIdx != 1)
        take2 = points[idx][1] + maximumPointsMemoizationHelper(idx + 1, 1, n, points, dp);
    // take 3rd
    if (prevIdx != 2)
        take3 = points[idx][2] + maximumPointsMemoizationHelper(idx + 1, 2, n, points, dp);
    // choose best
    return dp[idx][prevIdx] = max(take1, max(take2, take3));
}

// Memoization
// Time Complexity: O(N*4*3) ~ O(N), where N is the number of days.
// Space Complexity: O(N*4) ~ O(N), for the dp array and O(N) for the recursion stack.
int maximumPoints(vector<vector<int>> &arr)
{
    int n = arr.size();
    // taking 3 as dummy previous index, since tasks are 0,1,2
    vector<vector<int>> dp(n, vector<int>(4, -1));
    // passing 3 as previous index for day 0, meaning no restriction on task choice
    return maximumPointsMemoizationHelper(0, 3, n, arr, dp);
}

// Tabulation
// Time Complexity: O(N*4*3) ~ O(N), where N is the number of days.
// Space Complexity: O(N*4) ~ O(N), for the dp array.
int maximumPointsTabulation(vector<vector<int>> &arr)
{
    // using prevIdx = 3 as a dummy state to represent no previous task
    // allowing uniform transitions across all days.
    int n = arr.size();
    vector<vector<int>> dp(n + 1, vector<int>(4, 0));
    for (int idx = n - 1; idx >= 0; idx--)
    {
        for (int prevIdx = 0; prevIdx < 4; prevIdx++)
        {
            int best = 0;
            for (int task = 0; task < 3; task++)
            {
                if (task != prevIdx)
                {
                    best = max(best, arr[idx][task] + dp[idx + 1][task]);
                }
            }
            dp[idx][prevIdx] = best;
        }
    }
    // since day 0 is the first day, there is no restriction
    // we are free to choose any of the 3 tasks
    return dp[0][3];
}

int main()
{
    vector<vector<int>> points = {{1, 2, 5}, {3, 1, 1}, {3, 3, 3}};
    cout << maximumPointsTabulation(points) << endl; // Output: 11
    points = {{1, 1, 1}, {2, 2, 2}, {3, 3, 3}};
    cout << maximumPointsTabulation(points) << endl; // Output: 6
    return 0;
}