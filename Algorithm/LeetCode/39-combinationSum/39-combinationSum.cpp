//
//  39-combinationSum.cpp
//  LeetCode
//
//  Created by Knox on 2019/8/18.
//  Copyright © 2019 nchkdxlq. All rights reserved.
//

#include "39-combinationSum.hpp"
#include "STLHelper.hpp"



/*
 39. 组合总和
 给定一个无重复元素的数组 candidates 和一个目标数 target ，找出 candidates 中所有可以使数字和为 target 的组合。
 candidates 中的数字可以无限制重复被选取。
 
 链接：https://leetcode-cn.com/problems/combination-sum
 
 */
namespace combinationSum_39 {
    class Solution {
    public:
        vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
//            return v1_combinationSum(candidates, target);
            return v2_combinationSum(candidates, target);
        }
        
    private:
        vector<vector<int>> res;
        unordered_set<string> usedIndexSet;
        
        /*
         执行用时 : 328 ms, 5.00%
         内存消耗 : 22.2 MB, 21.02%
         */
        vector<vector<int>> v1_combinationSum(vector<int>& candidates, int target) {
            if (candidates.empty()) return {};
            res.clear();
            
            vector<int> cur;
            v1_combinationSum_helper(candidates, target, 0, cur);
            
            return res;
        }
        
        void v1_combinationSum_helper(vector<int>& candidates, int target, int sum, vector<int>& cur) {
            if (sum == target) {
                // 这个地方被坑了很久
                vector<int> tmp_c = cur; // cur 不能在这排序，否者在回溯的时候，push、pop的元素不一致，所以需要复制一份数组
                
                sort(tmp_c.begin(), tmp_c.end());
                vector<int> tmp;
                string key;
                for (auto i : tmp_c) {
                    tmp.push_back(candidates[i]);
                    key += to_string(i);
                }
                
                if (usedIndexSet.find(key) == usedIndexSet.end()) {
                    res.push_back(tmp);
                    usedIndexSet.insert(key);
                }
                return;
            } else if (sum > target) {
                return;
            }
            
            for (int i = 0; i < candidates.size(); i++) {
                cur.push_back(i);
                v1_combinationSum_helper(candidates, target, sum + candidates[i], cur);
                cur.pop_back();
            }
        }
        
        
        /*
         执行用时 : 20 ms,80.15%
         内存消耗 : 9.7 MB, 86.66%
         */
        vector<vector<int>> v2_combinationSum(vector<int>& candidates, int target) {
            if (candidates.empty()) return {};
            vector<int> cur;
            v2_combinationSum_helper(candidates, target, 0, cur);
            return res;
        }
        
        void v2_combinationSum_helper(vector<int>& candidates, int target, int index, vector<int>& cur) {
            if (target == 0) {
                res.push_back(cur);
                return;
            } else if (target < 0) {
                return;
            }
            
            for (int i = index; i < candidates.size(); i++) {
                cur.push_back(candidates[i]);
                v2_combinationSum_helper(candidates, target - candidates[i], i, cur);
                cur.pop_back();
            }
        }
        
    };
}


void __39_entry() {
    vector<int> candidates = {2,3,5}; int target = 8;
    
    candidates = {8,7,4,3}; target = 11;
    
    auto res = combinationSum_39::Solution().combinationSum(candidates, target);
    
    cout << "==== 39-candidates ====" << endl;
    cout << "[" << endl;
    for (auto &item : res) {
        cout << "   ";
        print_vector(item);
        cout << endl;
    }
    cout << "]" << endl;
    cout << endl;
}

