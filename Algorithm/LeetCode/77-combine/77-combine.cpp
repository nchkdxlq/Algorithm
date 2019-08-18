//
//  77-combine.cpp
//  LeetCode
//
//  Created by Knox on 2019/8/18.
//  Copyright © 2019 nchkdxlq. All rights reserved.
//

#include "77-combine.hpp"
#include "STLHelper.hpp"

/*
 77. 组合
 给定两个整数 n 和 k，返回 1 ... n 中所有可能的 k 个数的组合。
 
 https://leetcode-cn.com/problems/combinations/
 
 */

namespace combine_77 {
    class Solution {
    public:
        vector<vector<int>> combine(int n, int k) {
            if (n <= 0 || k <= 0 || n < k) return {};
            vector<vector<int>> res;
            vector<int> sub;
            v2_combine_helper(1, n, k, sub, res);
            return res;
        }
        
    private:
        
        // 求解C(n,k), 当前已经存在的组合存储在res中, 需要从begin开始搜索新的元素
        // 执行用时 :208 ms, 30.34%
        void v1_combine_helper(int begin, int end, int k, vector<int>& sub, vector<vector<int>>& res) {
            if (sub.size() == k) {
                res.push_back(sub);
                return;
            }
            
            // 剪枝，当从begin开始后面的元素个数少于组合需要的元素个数时，可以不遍历后面的元素了，这就是回溯剪枝，达到提高算法效率。
            int tmp = end - (k - (int)sub.size()) + 1;
            for (int i = begin; i <= tmp; i++) {
                sub.push_back(i);
                v1_combine_helper(i+1, end, k, sub, res);
                sub.pop_back();
            }
        }
        
        // 求解C(n,k), 当前已经存在的组合存储在res中, 需要从begin开始搜索新的元素
        // 执行用时 :92 ms, 93.41%
        // 内存消耗 :11.9 MB, 67.29%
        void v2_combine_helper(int begin, int end, int k, vector<int>& sub, vector<vector<int>>& res) {
            if (sub.size() == k) {
                res.push_back(sub);
                return;
            }
            
            
            int tmp = end - (k - (int)sub.size()) + 1;
            for (int i = begin; i <= tmp; i++) {
                sub.push_back(i);
                v2_combine_helper(i+1, end, k, sub, res);
                sub.pop_back();
            }
        }
    };
}



void __77_entry() {
    int n = 4, k = 2;
    
    auto res = combine_77::Solution().combine(n, k);
    
    cout << "==== 77-combine ====" << endl;
    cout << "[" << endl;
    for (auto &item : res) {
        cout << "   ";
        print_vector(item);
        cout << endl;
    }
    cout << "]" << endl;
    cout << endl;
}
