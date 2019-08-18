//
//  47-permuteUnique.cpp
//  LeetCode
//
//  Created by Knox on 2019/8/17.
//  Copyright © 2019 nchkdxlq. All rights reserved.
//

#include "47-permuteUnique.hpp"
#include "STLHelper.hpp"


/**
 47. 全排列 II
 给定一个可包含重复数字的序列，返回所有不重复的全排列。
 
 https://leetcode-cn.com/problems/permutations-ii/
 */

namespace permuteUnique_47 {
    class Solution {
    public:
        vector<vector<int>> permuteUnique(vector<int> nums) {
//            return v1_permuteUnique(nums);
            return v2_permuteUnique(nums);
        }
        
    private:
        
        vector<vector<int>> v1_permuteUnique(vector<int> nums) {
            if (nums.empty()) return {};
            
            vector<vector<int>> res;
            v1_backTrack(nums, 0, res);
            
            return res;
        }
        
        void v1_backTrack(vector<int>& nums, int index, vector<vector<int>>& res) {
            if (nums.size() == index) {
                res.push_back(nums);
                return;
            }
            
            unordered_set<int> used;
            for (int i = index; i < nums.size(); i++) {
                if (used.find(nums[i]) != used.end()) // 已经使用过 nums[i] 元素， 剪枝
                    continue;
                
                swap(nums[i], nums[index]);
                v1_backTrack(nums, index+1, res);
                swap(nums[i], nums[index]); // 回溯
            }
        }
        
        
        vector<vector<int>> v2_permuteUnique(vector<int> nums) {
            if (nums.empty()) return {};
            
            vector<vector<int>> res;
            // 先排序，对数组预处理
            sort(nums.begin(), nums.end());
            v2_backTrack(nums, 0, res);
            
            return res;
        }
        
        void v2_backTrack(vector<int>& nums, int index, vector<vector<int>>& res) {
            if (nums.size() == index) {
                res.push_back(nums);
                return;
            }
            
            for (int i = index; i < nums.size(); i++) {
                if (i == index || nums[i-1] != nums[i]) { // 剪枝
                    swap(nums[index], nums[i]);
                    v2_backTrack(nums, index+1, res);
                    swap(nums[index], nums[i]);
                }
            }
        }
        
    };
}


void __47_entry() {
    vector<int> nums = {1,1,2};
    auto ret = permuteUnique_47::Solution().permuteUnique(nums);
    
    cout << "==== 47-permuteUnique ====" << endl;
    for (auto &item : ret) {
        print_vector(item);
        cout << endl;
    }
    
    cout << endl;
}
