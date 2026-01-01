/*
https://leetcode.com/problems/non-overlapping-intervals/description/
435. Non-overlapping Intervals
Given an array of intervals intervals where intervals[i] = [starti, endi], return the minimum number of intervals you need to remove to make the rest of the intervals non-overlapping.
Note that intervals which only touch at a point are non-overlapping. For example, [1, 2] and [2, 3] are non-overlapping.
Example 1:
Input: intervals = [[1,2],[2,3],[3,4],[1,3]]
Output: 1
Explanation: [1,3] can be removed and the rest of the intervals are non-overlapping.
Example 2:
Input: intervals = [[1,2],[1,2],[1,2]]
Output: 2
Explanation: You need to remove two [1,2] to make the rest of the intervals non-overlapping.
Example 3:
Input: intervals = [[1,2],[2,3]]
Output: 0
Explanation: You don't need to remove any of the intervals since they're already non-overlapping.
Constraints:
1 <= intervals.length <= 105
intervals[i].length == 2
-5 * 104 <= starti < endi <= 5 * 104
*/

#include <bits/stdc++.h>
using namespace std;

static bool comp(const vector<int> &a, const vector<int> &b)
{
    return a[1] < b[1];
}
int eraseOverlapIntervals(vector<vector<int>> &intervals)
{
    // this is the reverse of the "N Meetings in One Room" problem.
    // instead of directly removing overlapping intervals,
    // we greedily find the maximum number of non-overlapping intervals.
    // the minimum removals = total intervals - non-overlapping intervals kept.
    int n = intervals.size();
    sort(intervals.begin(), intervals.end(), comp);
    int count = 1;
    int lastEndingTime = intervals[0][1];
    for (int i = 1; i < n; i++)
    {
        // If current interval does not overlap with the last selected one
        if (lastEndingTime <= intervals[i][0])
        {
            // Select this interval and update end time
            lastEndingTime = intervals[i][1];
            count++;
        }
        // Else: overlap exists, so we skip this interval (consider it removed)
    }
    // Minimum removals = total intervals - intervals we kept
    return n - count;
}

int main()
{
    vector<vector<int>> intervals = {{1, 2}, {2, 3}, {3, 4}, {1, 3}};
    cout << eraseOverlapIntervals(intervals) << endl; // Output: 1
    intervals = {{1, 2}, {1, 2}, {1, 2}};
    cout << eraseOverlapIntervals(intervals) << endl; // Output: 2
    intervals = {{1, 2}, {2, 3}};
    cout << eraseOverlapIntervals(intervals) << endl; // Output: 0
    return 0;
}