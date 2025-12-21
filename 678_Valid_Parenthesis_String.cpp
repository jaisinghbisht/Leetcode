/*
https://leetcode.com/problems/valid-parenthesis-string/
678. Valid Parenthesis String
Given a string s containing only three types of characters: '(', ')' and '*', return true if s is valid.
The following rules define a valid string:
Any left parenthesis '(' must have a corresponding right parenthesis ')'.
Any right parenthesis ')' must have a corresponding left parenthesis '('.
Left parenthesis '(' must go before the corresponding right parenthesis ')'.
'*' could be treated as a single right parenthesis ')' or a single left parenthesis '(' or an empty string "".
Example 1:
Input: s = "()"
Output: true
Example 2:
Input: s = "(*)"
Output: true
Example 3:
Input: s = "(*))"
Output: true
Constraints:
1 <= s.length <= 100
s[i] is '(', ')' or '*'.
*/

#include <bits/stdc++.h>
using namespace std;

// Time Complexity: O(n), Space Complexity: O(n)
// where n is the size of the string s
bool checkValidStringWithStack(string s)
{
    stack<int> openStack; // stores indices of '(' that still need to be matched
    stack<int> starStack; // stores indices of '*' that can act as '(' or ')'
    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] == '(')
        {
            openStack.push(i); // '(' must be matched later
        }
        else if (s[i] == '*')
        {
            starStack.push(i); // '*' is flexible, decision deferred
        }
        else
        { // ')'
            // Prefer matching ')' with '(' to preserve '*' for future flexibility
            if (!openStack.empty())
            {
                openStack.pop();
            }
            else if (!starStack.empty())
            {
                // Use '*' as '(' if no '(' is available
                starStack.pop();
            }
            else
            {
                // No '(' or '*' before this ')'
                return false;
            }
        }
    }
    // Match remaining '(' with '*' acting as ')'
    // Order matters: '*' must come after '(' to close it
    while (!openStack.empty() && !starStack.empty())
    {
        if (openStack.top() > starStack.top())
            return false;
        openStack.pop();
        starStack.pop();
    }
    // Valid only if all '(' are matched
    return openStack.empty();
}

// Time Complexity: O(n), Space Complexity: O(1)
// where n is the size of the string s
bool checkValidStringOptimal(string s)
{
    // low -> minimum possible number of unmatched '('
    // high -> maximum possible number of unmatched '('
    int low = 0, high = 0;
    for (char &ch : s)
    {
        if (ch == '(')
        {
            low++;
            high++;
        }
        else if (ch == ')')
        {
            low--;
            high--;
        }
        else
        {
            low--;
            high++;
        }
        if (high < 0)
            return false; // even if we turn every '*' into '(', we still have more ')' than '('.
        if (low < 0)
            low = 0; // we cannot have negative unmatched '(', we can choose some '*' as empty or '(' instead
    }
    return low == 0; // There exists at least one assignment of '*' such that all '(' are matched
    // If low > 0 : Even in the best case, some '(' remain unmatched, therefore : Invalid string
}

int main()
{
    string s = "(*))";
    cout << checkValidStringWithStack(s) << endl; // Output: 1 (true)
    cout << checkValidStringOptimal(s) << endl;   // Output: 1 (true)
    s = "(*()";
    cout << checkValidStringWithStack(s) << endl; // Output: 1 (true)
    cout << checkValidStringOptimal(s) << endl;   // Output: 1 (true)
    s = ")*(";
    cout << checkValidStringWithStack(s) << endl; // Output: 0 (false)
    cout << checkValidStringOptimal(s) << endl;   // Output: 0 (false)
    return 0;
}