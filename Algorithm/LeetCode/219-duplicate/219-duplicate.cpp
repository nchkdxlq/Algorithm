//
//  219-duplicate.cpp
//  LeetCode
//
//  Created by Knox on 2019/7/12.
//  Copyright © 2019 nchkdxlq. All rights reserved.
//

#include "219-duplicate.hpp"
#include "stlheaders.h"


/**
 
 给定一个整数数组和一个整数 k，判断数组中是否存在两个不同的索引 i 和 j，使得 nums [i] = nums [j]，
 并且 i 和 j 的差的绝对值最大值**不超过**k。也就是绝对值小于等于k。
 
 示例 1:
 输入: nums = [1,2,3,1], k = 3
 输出: true
 
 示例 2:
 输入: nums = [1,0,1,1], k = 1
 输出: true
 
 示例 3:
 输入: nums = [1,2,3,1,2,3], k = 2
 输出: false
 
 来源：力扣（LeetCode）
 链接：https://leetcode-cn.com/problems/contains-duplicate-ii
 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 */

namespace duplicate_219 {
    
    class Solution {
        
    private:
        bool v1_containsNearbyDuplicate(vector<int>& nums, int k) {
            
            unordered_map<int, vector<int>> mp;
            for (int i = 0; i < nums.size(); i++) {
                if (mp.find(nums[i]) != mp.end()) {
                    auto &idx = mp[nums[i]];
                    idx.push_back(i);
                } else {
                    vector<int> idx{i};
                    mp[nums[i]] = idx;
                }
            }
            
            for (auto &item : mp) {
                vector<int> idx = item.second;
                if (idx.size() > 1) {
                    for (int i = 1; i < idx.size(); i++) {
                        if (idx[i] - idx[i-1] <= k) {
                            return true;
                        }
                    }
                }
            }
            
            return false;
        }
        
    public:
        bool containsNearbyDuplicate(vector<int>& nums, int k) {
            return v1_containsNearbyDuplicate(nums, k);
        }
    };
}




void __219_entry() {
    
    vector<int> nums = {1,2,3,1};
    int k = 3;
    
    nums = {1,0,1,1};
    k = 1;

    nums = {1,2,3,1,2,3};
    k = 2;
    
    bool ret = duplicate_219::Solution().containsNearbyDuplicate(nums, k);
    cout << (ret ? "true" : "false") << endl;
}
