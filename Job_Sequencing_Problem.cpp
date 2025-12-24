/*
https://www.geeksforgeeks.org/problems/job-sequencing-problem-1587115620/1
Job Sequencing Problem
You are given two arrays: deadline[], and profit[], which represent a set of jobs, where each job is associated with a deadline, and a profit. Each job takes 1 unit of time to complete, and only one job can be scheduled at a time. You will earn the profit associated with a job only if it is completed by its deadline.
Your task is to find:
The maximum number of jobs that can be completed within their deadlines.
The total maximum profit earned by completing those jobs.
Examples :
Input: deadline[] = [4, 1, 1, 1], profit[] = [20, 10, 40, 30]
Output: [2, 60]
Explanation: Job1 and Job3 can be done with maximum profit of 60 (20+40).
Input: deadline[] = [2, 1, 2, 1, 1], profit[] = [100, 19, 27, 25, 15]
Output: [2, 127]
Explanation: Job1 and Job3 can be done with maximum profit of 127 (100+27).
Input: deadline[] = [3, 1, 2, 2], profit[] = [50, 10, 20, 30]
Output: [3, 100]
Explanation: Job1, Job3 and Job4 can be completed with a maximum profit of 100 (50 + 20 + 30).
Constraints:
1 ≤ deadline.size() = profit.size() ≤ 105
1 ≤ deadline[i] ≤ deadline.size()
1 ≤ profit[i] ≤ 500
*/

#include <bits/stdc++.h>
using namespace std;

static bool comp(pair<int, int> &a, pair<int, int> &b)
{
    return a.second > b.second; // desc order of profit
}

// Time Complexity: O(n log n + n * d), Space Complexity: O(d)
// where n is the number of jobs and d is the maximum deadline
vector<int> jobSequencingGreedy(vector<int> &deadline, vector<int> &profit)
{
    int n = deadline.size();
    // {deadline, profit}
    vector<pair<int, int>> jobs;
    int maxDeadline = 0;
    for (int i = 0; i < n; i++)
    {
        jobs.push_back({deadline[i], profit[i]});
        maxDeadline = max(maxDeadline, deadline[i]);
    }
    sort(jobs.begin(), jobs.end(), comp);
    vector<int> workArr(maxDeadline + 1, -1);
    int totalJobs = 0, totalProfit = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = jobs[i].first; j > 0; j--)
        {
            if (workArr[j] == -1)
            {
                workArr[j] = jobs[i].second;
                totalJobs++;
                totalProfit += jobs[i].second;
                break;
            }
        }
    }
    return {totalJobs, totalProfit};
}

class DisjointSet
{
public:
    vector<int> parent;
    int findUltimateParent(int node)
    {
        if (node == parent[node])
        {
            return node;
        }
        return parent[node] = findUltimateParent(parent[node]);
    }
};

// Time Complexity: O(n log n), Space Complexity: O(d)
// where n is the number of jobs and d is the maximum deadline
vector<int> jobSequencingGreedyWithDSU(vector<int> &deadline, vector<int> &profit)
{
    int n = deadline.size();
    // {deadline, profit}
    vector<pair<int, int>> jobs;
    int maxDeadline = 0;
    for (int i = 0; i < n; i++)
    {
        jobs.push_back({deadline[i], profit[i]});
        maxDeadline = max(maxDeadline, deadline[i]);
    }
    sort(jobs.begin(), jobs.end(), comp);
    // with DSU, we can find the ultimate parent of a node in O(1) time.
    // parent[i] will represent the latest available slot for a job with deadline i.
    // initially, each slot is its own parent.
    // if a job is assigned to slot 's', we union 's' with 's-1' to indicate that the next available slot is now 's-1'.
    // hence, path compression is used to optimize the find operation.
    DisjointSet dsu;
    dsu.parent.resize(maxDeadline + 1);
    for (int i = 0; i <= maxDeadline; i++)
        dsu.parent[i] = i;
    int totalJobs = 0, totalProfit = 0;
    for (auto &job : jobs)
    {
        int d = job.first;
        int p = job.second;
        int slot = dsu.findUltimateParent(d);
        if (slot > 0)
        {
            totalJobs++;
            totalProfit += p;
            dsu.parent[slot] = dsu.findUltimateParent(slot - 1); // union
        }
    }
    return {totalJobs, totalProfit};
}

int main()
{
    vector<int> deadline = {4, 1, 1, 1};
    vector<int> profit = {20, 10, 40, 30};
    vector<int> result = jobSequencingGreedy(deadline, profit);
    cout << "[" << result[0] << ", " << result[1] << "]" << endl; // Output: [2, 60]
    result = jobSequencingGreedyWithDSU(deadline, profit);
    cout << "[" << result[0] << ", " << result[1] << "]" << endl; // Output: [2, 60]
    deadline = {2, 1, 2, 1, 1};
    profit = {100, 19, 27, 25, 15};
    result = jobSequencingGreedy(deadline, profit);
    cout << "[" << result[0] << ", " << result[1] << "]" << endl; // Output: [2, 127]
    result = jobSequencingGreedyWithDSU(deadline, profit);
    cout << "[" << result[0] << ", " << result[1] << "]" << endl; // Output: [2, 127]
    deadline = {3, 1, 2, 2};
    profit = {50, 10, 20, 30};
    result = jobSequencingGreedy(deadline, profit);
    cout << "[" << result[0] << ", " << result[1] << "]" << endl; // Output: [3, 100]
    result = jobSequencingGreedyWithDSU(deadline, profit);
    cout << "[" << result[0] << ", " << result[1] << "]" << endl; // Output: [3, 100]
    return 0;
}