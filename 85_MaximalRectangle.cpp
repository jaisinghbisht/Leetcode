/*
https://leetcode.com/problems/maximal-rectangle/
Given a rows x cols binary matrix filled with 0's and 1's, find the largest rectangle containing only 1's and return its area.
Example 1:
Input: matrix = [["1","0","1","0","0"],["1","0","1","1","1"],["1","1","1","1","1"],["1","0","0","1","0"]]
Output: 6
Explanation: The maximal rectangle is shown in the above picture.
Example 2:
Input: matrix = [["0"]]
Output: 0
Example 3:
Input: matrix = [["1"]]
Output: 1
Constraints:
rows == matrix.length
cols == matrix[i].length
1 <= rows, cols <= 200
matrix[i][j] is '0' or '1'.
*/

#include <bits/stdc++.h>
using namespace std;

int findLargestHistogram(vector<int> &heights)
{
    stack<int> st;
    int n = heights.size(), area = 0;
    for (int i = 0; i < n; i++)
    {
        while (!st.empty() && heights[st.top()] > heights[i])
        {
            int currElement = heights[st.top()];
            st.pop();
            int nse = i;
            int pse = st.empty() ? -1 : st.top();
            area = max(area, currElement * (nse - pse - 1));
        }
        st.push(i);
    }
    while (!st.empty())
    {
        int currElement = heights[st.top()];
        st.pop();
        int nse = n;
        int pse = st.empty() ? -1 : st.top();
        area = max(area, currElement * (nse - pse - 1));
    }
    return area;
}

// Time Complexity: O(rows * cols), Space Complexity: O(rows * cols)
// where rows and cols are the dimensions of the matrix
int maximalRectangle(vector<vector<char>> &matrix)
{
    int n = matrix.size(), m = matrix[0].size(), maxArea = 0;
    vector<vector<int>> prefixSum(n, vector<int>(m, 0));
    for (int i = 0; i < m; i++)
    {
        // build prefix sum for each column
        // and treat each row as histogram
        int sum = 0;
        for (int j = 0; j < n; j++)
        {
            sum += (matrix[j][i] - '0');
            if (matrix[j][i] == '0')
            {
                sum = 0;
            }
            prefixSum[j][i] = sum;
        }
    }
    for (int i = 0; i < n; i++)
    {
        maxArea = max(maxArea, findLargestHistogram(prefixSum[i]));
    }
    return maxArea;
}

int main()
{
    vector<vector<char>> matrix = {
        {'1', '0', '1', '0', '0'},
        {'1', '0', '1', '1', '1'},
        {'1', '1', '1', '1', '1'},
        {'1', '0', '0', '1', '0'}};
    cout << maximalRectangle(matrix) << endl; // Output: 6
    matrix = {
        {'0'}};
    cout << maximalRectangle(matrix) << endl; // Output: 0
    matrix = {
        {'1'}};
    cout << maximalRectangle(matrix) << endl; // Output: 1
    return 0;
}