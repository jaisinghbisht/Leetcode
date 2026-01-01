/*
https://leetcode.com/problems/merge-intervals/description/
56. Merge Intervals
Given an array of intervals where intervals[i] = [starti, endi], merge all overlapping intervals, and return an array of the non-overlapping intervals that cover all the intervals in the input.
Example 1:
Input: intervals = [[1,3],[2,6],[8,10],[15,18]]
Output: [[1,6],[8,10],[15,18]]
Explanation: Since intervals [1,3] and [2,6] overlap, merge them into [1,6].
Example 2:
Input: intervals = [[1,4],[4,5]]
Output: [[1,5]]
Explanation: Intervals [1,4] and [4,5] are considered overlapping.
Example 3:
Input: intervals = [[4,7],[1,4]]
Output: [[1,7]]
Explanation: Intervals [1,4] and [4,7] are considered overlapping.
Constraints:
1 <= intervals.length <= 104
intervals[i].length == 2
0 <= starti <= endi <= 104
*/

#include <bits/stdc++.h>
using namespace std;

// Time Complexity: O(NlogN) + O(N) ~ O(NlogN), where N is the number of intervals.
// Space Complexity: O(N) for the result storage in the worst case when no intervals overlap
vector<vector<int>> merge(vector<vector<int>> &intervals)
{
    sort(intervals.begin(), intervals.end());
    int n = intervals.size();
    vector<vector<int>> res;
    res.push_back(intervals[0]);
    for (int i = 1; i < n; i++)
    {
        if (res.back()[1] >= intervals[i][0])
        {
            res.back()[1] = max(res.back()[1], intervals[i][1]);
        }
        else
        {
            res.push_back(intervals[i]);
        }
    }
    return res;
}

int main()
{
    vector<vector<int>> intervals = {{1, 3}, {2, 6}, {8, 10}, {15, 18}};
    vector<vector<int>> mergedIntervals = merge(intervals);
    cout << "Merged Intervals: ";
    for (const auto &interval : mergedIntervals)
    {
        cout << "[" << interval[0] << ", " << interval[1] << "] "; // Expected output: [1, 6] [8, 10] [15, 18]
    }
    cout << endl;
    intervals = {{1, 4}, {4, 5}};
    mergedIntervals = merge(intervals);
    cout << "Merged Intervals: ";
    for (const auto &interval : mergedIntervals)
    {
        cout << "[" << interval[0] << ", " << interval[1] << "] "; // Expected output: [1, 5]
    }
    cout << endl;
    intervals = {{4, 7}, {1, 4}};
    mergedIntervals = merge(intervals);
    cout << "Merged Intervals: ";
    for (const auto &interval : mergedIntervals)
    {
        cout << "[" << interval[0] << ", " << interval[1] << "] "; // Expected output: [1, 7]
    }
    cout << endl;
    return 0;
}