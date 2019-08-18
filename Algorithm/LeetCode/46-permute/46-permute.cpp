//
//  46-permute.cpp
//  LeetCode
//
//  Created by Knox on 2019/8/16.
//  Copyright © 2019 nchkdxlq. All rights reserved.
//

#include "46-permute.hpp"
#include "STLHelper.hpp"

/*
 46. 全排列
 给定一个没有重复数字的序列，返回其所有可能的全排列。
 
 回溯算法详解案例：https://leetcode-cn.com/problems/permutations/solution/permutations-di-gui-hui-su-by-jyd/
 
 https://leetcode-cn.com/problems/permutations/
 */


namespace permute_46 {
    class Solution {
    public:
        vector<vector<int>> permute(vector<int>& nums) {
//            return v1_permute(nums);
//            return v2_permute(nums);
            return v3_permute(nums);
        }
        
    private:
        vector<vector<int>> res;
        vector<bool> used;
        
        /*
         执行用时 :24 ms, 39.23%
         内存消耗 :9.4 MB, 57.00%
         */
        
        vector<vector<int>> v1_permute(vector<int>& nums) {
            res.clear();
            if (nums.empty()) return res;
            used = vector<bool>(nums.size(), false);
            vector<int> p;
            v1_premute_helper(nums, 0, p);
            return res;
        }
        
        void v1_premute_helper(vector<int>& nums, int index, vector<int>& p) {
            if (index == nums.size()) {
                res.push_back(p);
                return;
            }
            
            for (int i = 0; i < nums.size(); i++) {
                if (used[i]) continue;
                
                p.push_back(nums[i]);
                used[i] = true;
                v1_premute_helper(nums, index+1, p);
                p.pop_back();
                used[i] = false;
            }
        }
        
        
        
        /*
         执行用时 :36 ms, 8.59%
         内存消耗 :9.4 MB, 51.39%
         */
        
        vector<vector<int>> v2_permute(vector<int>& nums) {
            res.clear();
            if (nums.empty()) return res;
            vector<int> p;
            v2_premute_helper(nums, 0, p);
            return res;
        }
        
        void v2_premute_helper(vector<int>& nums, int index, vector<int>& p) {
            if (nums.size() == index) {
                res.push_back(p);
                return;
            }
            
            for (int i = index; i < nums.size() ; i++) {
                p.push_back(nums[i]);
                swap(nums[index], nums[i]);
                v2_premute_helper(nums, index+1, p);
                swap(nums[index], nums[i]);
                p.pop_back();
            }
        }
        
        vector<vector<int>> v3_permute(vector<int>& nums) {
            res.clear();
            v3_premute_helper(nums, 0);
            return res;
        }
        
        void v3_premute_helper(vector<int>& nums, int index) {
            if (nums.size() == index) {
                res.push_back(nums);
                return;
            }
            
            for (int i = index; i < nums.size() ; i++) {
                swap(nums[index], nums[i]);
                v3_premute_helper(nums, index+1);
                swap(nums[index], nums[i]);
            }
        }
        
    };
}



void __46_entry() {
    vector<int> nums = {1,2,3};
    auto ret = permute_46::Solution().permute(nums);
    
    cout << "==== 46-permute ====" << endl;
    for (auto &item : ret) {
        print_vector(item);
        cout << endl;
    }
    
    cout << endl;
}
