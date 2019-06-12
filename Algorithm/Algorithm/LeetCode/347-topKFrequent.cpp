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

using namespace std;

bool cmpK(const pair<int, int>& l, const pair<int, int>& r) {
    return l.second < r.second;
}

vector<int> topKFrequent(vector<int>& nums, int k) {
    unordered_map<int, int> counter;
    for (auto i : nums) {
        counter[i]++;
    }

//    priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmpK)> q(counter.begin(), counter.end());
    
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q(counter.begin(), counter.end());
    
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
    topKFrequent(nums, 2);
}
