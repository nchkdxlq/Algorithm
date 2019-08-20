//
//  40-combinationSum2.cpp
//  LeetCode
//
//  Created by Knox on 2019/8/18.
//  Copyright © 2019 nchkdxlq. All rights reserved.
//

#include "40-combinationSum2.hpp"
#include "STLHelper.hpp"


/*
 40. 组合总和 II
 给定一个数组 candidates 和一个目标数 target ，找出 candidates 中所有可以使数字和为 target 的组合。
 candidates 中的每个数字在每个组合中只能使用一次。
 
 说明：
 所有数字（包括目标数）都是正整数。
 解集不能包含重复的组合。
 
 链接：https://leetcode-cn.com/problems/combination-sum-ii
 */

namespace combinationSum2_40 {
    
    class Solution {
    public:
        vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
//            return v1_combinationSum2(candidates, target);
            return v2_combinationSum2(candidates, target);
        }
        
    private:
        vector<vector<int>> res;
        unordered_set<string> used; // 已经存在的集合
        
        /*
         执行用时 : 16 ms, 83.49%
         内存消耗 : 9.5 MB, 83.30%
         */
        vector<vector<int>> v1_combinationSum2(vector<int>& candidates, int target) {
            if (candidates.empty()) return {};
            res.clear();
            sort(candidates.begin(), candidates.end());
            if (candidates[0] > target) return res; // 最小的元素都比target要大，因此没有这样的组合
            
            vector<int> cur;
            v1_combinationSum2_helper(candidates, target, 0, cur);
            return res;
        }
        
        void v1_combinationSum2_helper(vector<int>& candidates, int target, int index, vector<int>& cur) {
            if (target == 0) {
                // 因为对数组排序了，所以，cur的元素一定是升序的。
                string key = "";
                for (auto i : cur) {
                    key += to_string(i);
                }
                if (used.find(key) == used.end()) {
                    res.push_back(cur);
                    used.insert(key);
                }
                return;
            } else if (target < 0) {
                return;
            }
            
            int size = (int)candidates.size();
            for (int i = index; i < size; i++) {
                if (candidates[i] > target) break; // 剪枝 (忘记剪枝了，导致耗时多, 84 ms)
                
                cur.push_back(candidates[i]);
                // 一个元素只能使用一次，所以 i+1
                v1_combinationSum2_helper(candidates, target- candidates[i], i+1, cur);
                cur.pop_back();
            }
        }
        
        
        /*
         执行用时 : 12 ms, 89.48%
         内存消耗 : 9.2 MB, 86.54%
         */
        vector<vector<int>> v2_combinationSum2(vector<int>& candidates, int target) {
            if (candidates.empty()) return {};
            res.clear();
            
            sort(candidates.begin(), candidates.end()); // 先排序，是剪枝的前提
            if (candidates[0] > target) return res; // 最小的元素都比target要大，因此没有这样的组合
            
            vector<int> cur;
            v2_combinationSum2_helper(candidates, target, 0, cur);
            return res;
        }
        
        void v2_combinationSum2_helper(vector<int>& candidates, int target, int index, vector<int>& cur) {
            if (target == 0) {
                res.push_back(cur);
                return;
            }
            
            for (int i = index; i < candidates.size(); i++) {
                // 剪枝, 因为candidates是升序的，所以，如果candidates[i] > target, 那么后面的元素都大于target，可提前结束循环
                if (candidates[i] > target)
                    break;
                
                // 这个逻辑还没搞太明白？？？？ (说明: i>index, 能保证递归过程中，每一个元素都能使用到，
                // 而i > index && candidates[i] == candidates[i-1]), 确保了循环中相同元素只被使用一次
                if (i > index && candidates[i] == candidates[i-1])
                    continue;
                
                cur.push_back(candidates[i]);
                // 一个元素只能使用一次，所以 i+1
                v2_combinationSum2_helper(candidates, target-candidates[i], i+1, cur);
                cur.pop_back();
            }
        }
    };
    
}


void __40_entry() {
    vector<int> candidates = {10,1,2,7,6,1,5}; int target = 8;
    
    candidates = {2,5,2,1,2}; target = 5;
    
    candidates = {1, 1, 1, 1, 1, 1, 2, 2, 2, 3}; target = 4;
    
    auto res = combinationSum2_40::Solution().combinationSum2(candidates, target);
    
    cout << "==== 40-combinationSum2 ====" << endl;
    cout << "[" << endl;
    for (auto &item : res) {
        cout << "   ";
        print_vector(item);
        cout << endl;
    }
    cout << "]" << endl;
    cout << endl;
}
