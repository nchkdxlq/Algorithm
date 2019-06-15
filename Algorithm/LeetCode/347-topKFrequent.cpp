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


struct cmpK {
    
    bool operator ()(const pair<int, int>& l, const pair<int, int>& r) const
    {
        return l.second < r.second;// 按照value从小到大排列
    }
    
};

vector<int> topKFrequent(vector<int>& nums, int k) {
    unordered_map<int, int> counter;
    for (auto i : nums) {
        counter[i]++;
    }
    
#if 1
    priority_queue<pair<int, int>, vector<pair<int, int>>, cmpK> q(counter.begin(), counter.end());
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



void entry_347() {
    vector<int> nums{1,1,1,2,2,2,2,3,3};
    vector<int> ret = topKFrequent(nums, 2);
    
    for (auto i : ret) {
        cout << i << " ";
    }
    cout << endl;
}
