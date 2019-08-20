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
//            return v3_permuteUnique(nums);
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
                
                used.insert(nums[i]); // 记录已经使用过的值
            }
        }
        
        
        vector<vector<int>> v2_permuteUnique(vector<int> nums) {
            if (nums.empty()) return {};
            
            vector<vector<int>> res;
            // 先排序，对数组预处理, 是后面剪枝的前提条件
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
                if (i > index && nums[i] == nums[index]) // 剪枝
                    continue;
                
                swap(nums[index], nums[i]);
                v2_backTrack(nums, index+1, res);
                swap(nums[index], nums[i]);
            }
        }
        
        
        vector<bool> used;
        
        vector<vector<int>> v3_permuteUnique(vector<int> nums) {
            if (nums.empty()) return {};
            
            // 先排序，对数组预处理, 是后面剪枝的前提条件
            sort(nums.begin(), nums.end());
            used = vector<bool>(nums.size(), false);
            
            vector<vector<int>> res;
            vector<int> cur;
            v3_backTrack(nums, cur, res);
            
            return res;
        }
        
        void v3_backTrack(vector<int>& nums, vector<int>& cur, vector<vector<int>>& res) {
            if (nums.size() == cur.size()) {
                res.push_back(cur);
                return;
            }
            
            for (int i = 0; i < nums.size(); i++) {
                if (used[i]) // 剪枝
                    continue;
                
                used[i] = true;
                cur.push_back(nums[i]);
                v3_backTrack(nums, cur, res);
                cur.pop_back();
                used[i] = false;
            }
        }
        
    };
}


void __47_entry() {
    vector<int> nums = {1,1,2};
//    nums = {0,1,0,1,0,9};
//    nums = {1,2,3};
    
    auto ret = permuteUnique_47::Solution().permuteUnique(nums);
    
    cout << "==== 47-permuteUnique ====" << endl;
    cout << "size = " << ret.size() << endl;
    
    for (auto &item : ret) {
        print_vector(item);
        cout << endl;
    }
    
    cout << endl;
}
