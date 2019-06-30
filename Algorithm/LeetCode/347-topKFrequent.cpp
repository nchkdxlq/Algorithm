//
//  347-topKFrequent.cpp
//  Algorithm
//
//  Created by nchkdxlq on 2019/6/11.
//  Copyright © 2019 nchkdxlq. All rights reserved.
//

#include "347-topKFrequent.hpp"
#include <vector>
#include <unordered_map>
#include <utility>
#include <queue>
#include <iostream>

using namespace std;

typedef pair<int, int> IIPair;

struct lessCmp {
    
    bool operator ()(const pair<int, int>& l, const pair<int, int>& r) const
    {
        return l.second < r.second;// 按照value从小到大排列
    }
};

struct greaterCmp {
    bool operator()(const IIPair &left, const IIPair &right) const
    {
        return left.second > right.second;
    }
};


vector<int> topKFrequent_v2(vector<int>& nums, int k) {
    unordered_map<int, int> mp;
    for (auto i : nums) {
        mp[i]++;
    }
    
    priority_queue<IIPair, vector<IIPair>, greaterCmp> q; // 创建一个小顶堆
    
    for (auto item : mp) {
        if (q.size() < k) {
            q.push(item);
        } else if (item.second > q.top().second) {
            q.pop();
            q.push(item);
        }
        // 新的元素频次小于堆顶元素频次的元素不处理。
    }
    
    vector<int> ret(q.size(), 0);
    
    while (!q.empty()) {
        ret[q.size()-1] = q.top().first;
        q.pop();
    }
    
    return ret;
}



vector<int> topKFrequent_v1(vector<int>& nums, int k) {
    unordered_map<int, int> counter;
    for (auto i : nums) {
        counter[i]++;
    }
    
#if 1
    priority_queue<pair<int, int>, vector<pair<int, int>>, greaterCmp> q(counter.begin(), counter.end());
#else
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q(counter.begin(), counter.end());
#endif
    
    vector<int> ret;
    
    for (int i = 0; i < k; i++) {
        auto top = q.top();
        ret.push_back(top.first);
        q.pop();
    }
    
    return ret;
}


/**
    https://leetcode-cn.com/problems/top-k-frequent-elements/
 
 给定一个非空的整数数组，返回其中出现频率前 k 高的元素。
 
 示例 1:
 输入: nums = [1,1,1,2,2,3], k = 2
 输出: [1,2]
 
 示例 2:
 输入: nums = [1], k = 1
 输出: [1]
 
 说明：
   你可以假设给定的 k 总是合理的，且 1 ≤ k ≤ 数组中不相同的元素的个数。
   你的算法的时间复杂度必须优于 O(n log n) , n 是数组的大小。
 
 */
vector<int> topKFrequent(vector<int>& nums, int k) {
    return topKFrequent_v2(nums, k);
}



void entry_347() {
    vector<int> nums{1,1,1,2,2,2,2,3,3};
    vector<int> ret = topKFrequent(nums, 2);
    
    for (auto i : ret) {
        cout << i << " ";
    }
    cout << endl;
}
