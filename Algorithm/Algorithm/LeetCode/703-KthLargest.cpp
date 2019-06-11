//
//  703-KthLargest.cpp
//  Algorithm
//
//  Created by nchkdxlq on 2019/6/11.
//  Copyright © 2019 nchkdxlq. All rights reserved.
//

#include "703-KthLargest.hpp"
#include <vector>
#include <queue>
#include "iostream"

using namespace std;

class KthLargest {
    
private:
    int k;
    priority_queue<int, vector<int>, greater<int>> q;
    
    void __add(int val) {
        if (q.size() < k) {
            q.push(val);
        } else if (q.top() < val) {
            q.pop();
            q.push(val);
        }
    }
    
public:
    KthLargest(int k,  vector<int> &nums) {
        this->k = k;
        
        for (auto i : nums) {
            __add(i);
        }
    }
    
    
    int add(int val) {
        __add(val);
        return q.top();
    }
};


void entry_703() {
    
    vector<int> nums = {1,8,5,6,3,4,0,9,7,2};
    int k = 4;
    
    KthLargest kth(k, nums);
    
    cout << kth.add(9) << endl;
    cout << kth.add(29) << endl;
    cout << kth.add(30) << endl;
}


