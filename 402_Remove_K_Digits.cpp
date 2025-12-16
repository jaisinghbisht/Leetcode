/*
https://leetcode.com/problems/remove-k-digits/
402. Remove K Digits
Given string num representing a non-negative integer num, and an integer k, return the smallest possible integer after removing k digits from num.
Example 1:
Input: num = "1432219", k = 3
Output: "1219"
Explanation: Remove the three digits 4, 3, and 2 to form the new number 1219 which is the smallest.
Example 2:
Input: num = "10200", k = 1
Output: "200"
Explanation: Remove the leading 1 and the number is 200. Note that the output must not contain leading zeroes.
Example 3:
Input: num = "10", k = 2
Output: "0"
Explanation: Remove all the digits from the number and it is left with nothing which is 0.
Constraints:
1 <= k <= num.length <= 105
num consists of only digits.
num does not have any leading zeros except for the zero itself.
*/

#include <bits/stdc++.h>
using namespace std;

// Time Complexity: O(N), Space Complexity: O(N)
string removeKdigits(string num, int k)
{
    stack<char> st;
    for (char ch : num)
    {
        while (!st.empty() && st.top() > ch && k > 0)
        {
            st.pop();
            k--;
        }
        st.push(ch);
    }

    // remove remaining k digits, in case num = "12345" and k = 2
    while (k > 0 && !st.empty())
    {
        st.pop();
        k--;
    }

    // build result
    string res;
    while (!st.empty())
    {
        res.push_back(st.top());
        st.pop();
    }
    reverse(res.begin(), res.end());

    // remove leading zeros
    int i = 0;
    while (i < res.size() && res[i] == '0')
    {
        i++;
    }
    res = res.substr(i);
    return res.empty() ? "0" : res;
}

int main()
{
    string num = "1432219";
    int k = 3;
    cout << removeKdigits(num, k) << endl; // Output: "1219"
    num = "10200";
    k = 1;
    cout << removeKdigits(num, k) << endl; // Output: "200"
    num = "10";
    k = 2;
    cout << removeKdigits(num, k) << endl; // Output: "0"
    return 0;
}