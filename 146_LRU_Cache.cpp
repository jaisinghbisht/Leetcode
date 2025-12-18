/*
https://leetcode.com/problems/lru-cache/
146. LRU Cache
Design a data structure that follows the constraints of a Least Recently Used (LRU) cache.
Implement the LRUCache class:
LRUCache(int capacity) Initialize the LRU cache with positive size capacity.
int get(int key) Return the value of the key if the key exists, otherwise return -1.
void put(int key, int value) Update the value of the key if the key exists. Otherwise, add the key-value pair to the cache. If the number of keys exceeds the capacity from this operation, evict the least recently used key.
The functions get and put must each run in O(1) average time complexity.
Example 1:
Input
["LRUCache", "put", "put", "get", "put", "get", "put", "get", "get", "get"]
[[2], [1, 1], [2, 2], [1], [3, 3], [2], [4, 4], [1], [3], [4]]
Output
[null, null, null, 1, null, -1, null, -1, 3, 4]
Explanation
LRUCache lRUCache = new LRUCache(2);
lRUCache.put(1, 1); // cache is {1=1}
lRUCache.put(2, 2); // cache is {1=1, 2=2}
lRUCache.get(1);    // return 1
lRUCache.put(3, 3); // LRU key was 2, evicts key 2, cache is {1=1, 3=3}
lRUCache.get(2);    // returns -1 (not found)
lRUCache.put(4, 4); // LRU key was 1, evicts key 1, cache is {4=4, 3=3}
lRUCache.get(1);    // return -1 (not found)
lRUCache.get(3);    // return 3
lRUCache.get(4);    // return 4
Constraints:
1 <= capacity <= 3000
0 <= key <= 104
0 <= value <= 105
At most 2 * 105 calls will be made to get and put.
*/

#include <bits/stdc++.h>
using namespace std;

// Double Linked List Node
class Node
{
public:
    Node *next;
    Node *prev;
    int key;
    int val;
    Node()
    {
        next = nullptr;
        prev = nullptr;
        key = -1;
        val = -1;
    }

    Node(int key, int val)
    {
        next = nullptr;
        prev = nullptr;
        this->key = key;
        this->val = val;
    }
};

// LRU Cache Class
// Time Complexity: O(1) for get and put operations
// Space Complexity: O(capacity)
class LRUCache
{
private:
    int capacity;
    unordered_map<int, Node *> mp; // key -> Node
    Node *head;                    // least recently used -> first for deletion
    Node *tail;                    // most recently used

public:
    // Constructor
    LRUCache(int capacity)
    {
        mp.clear();
        this->capacity = capacity;
        head = new Node();
        tail = new Node();
        head->next = tail;
        tail->prev = head;
    }

    // Time Complexity: O(1), Space Complexity: O(1)
    int get(int key)
    {
        if (mp.find(key) != mp.end())
        {
            Node *node = mp[key];
            deleteNode(node);
            addToRight(node);
            return node->val;
        }
        return -1;
    }

    // Time Complexity: O(1), Space Complexity: O(1)
    void put(int key, int value)
    {
        if (mp.find(key) != mp.end())
        {
            Node *node = mp[key];
            node->val = value;
            deleteNode(node);
            addToRight(node);
            return;
        }
        else
        {
            if (mp.size() == capacity)
            {
                Node *lru = head->next;
                mp.erase(lru->key);
                deleteNode(lru);
                delete lru;
            }
            Node *node = new Node(key, value);
            addToRight(node);
            mp[key] = node;
        }
    }

    void deleteNode(Node *node)
    {
        Node *prev = node->prev;
        Node *next = node->next;
        prev->next = next;
        next->prev = prev;
    }

    void addToRight(Node *node)
    {
        Node *prev = tail->prev;
        prev->next = node;
        node->prev = prev;
        node->next = tail;
        tail->prev = node;
    }
};

int main()
{
    LRUCache lRUCache(2);
    lRUCache.put(1, 1);              // cache is {1=1}
    lRUCache.put(2, 2);              // cache is {1=1, 2=2}
    cout << lRUCache.get(1) << endl; // return 1
    lRUCache.put(3, 3);              // LRU key was 2, evicts key 2, cache is {1=1, 3=3}
    cout << lRUCache.get(2) << endl; // returns -1 (not found)
    lRUCache.put(4, 4);              // LRU key was 1, evicts key 1, cache is {4=4, 3=3}
    cout << lRUCache.get(1) << endl; // return -1 (not found)
    cout << lRUCache.get(3) << endl; // return 3
    cout << lRUCache.get(4) << endl; // return 4
    return 0;
}