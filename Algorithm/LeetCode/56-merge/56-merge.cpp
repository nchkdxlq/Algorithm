//
//  56-merge.cpp
//  LeetCode
//
//  Created by Knox on 2019/7/7.
//  Copyright © 2019 nchkdxlq. All rights reserved.
//

#include "56-merge.hpp"
#include "STLHelper.hpp"



/**
 https://leetcode-cn.com/problems/merge-intervals/
 
 
 给出一个区间的集合，请合并所有重叠的区间。
 
 示例 1:
 输入: [[1,3],[2,6],[8,10],[15,18]]
 输出: [[1,6],[8,10],[15,18]]
 解释: 区间 [1,3] 和 [2,6] 重叠, 将它们合并为 [1,6].
 
 示例 2:
 输入: [[1,4],[4,5]]
 输出: [[1,5]]
 解释: 区间 [1,4] 和 [4,5] 可被视为重叠区间。
 
 */

namespace merge_56 {
    
    // 返回true, 表示l放在r的前面
    bool cmp(const vector<int> &l, vector<int> &r)
    {
        if (l[0] < r[0]) {
            return true;
        } else if (l[0] > r[0]) {
            return false;
        } else {
            if (l[1] < r[1]) {
                return true;
            } else  {
                return false;
            }
        }
    }
    
    class Solution {
    public:
        vector<vector<int>> merge(vector<vector<int>>& intervals) {
            // 特殊情况先处理
            if (intervals.size() <= 1) return intervals;
            
            // 先排序区间集合，默认使用vector的第一个元素排序
            sort(intervals.begin(), intervals.end());
            
            vector<vector<int>> ret;
            
            vector<int> pre = intervals[0];
            for (int i = 1; i < intervals.size(); i++) {
                vector<int> cur = intervals[i];
                if (pre[1] < cur[0]) { // 独立区间
                    ret.push_back(pre);
                    pre = cur;
                } else { // 合并区间，右区间取大值
                    pre[1] = max(pre[1], cur[1]);
                }
            }
            
            ret.push_back(pre);
            
            return ret;
        }
    };
}

/*
 
 时间复杂度：排序区间时间复杂度为O(nlogn), 遍历时间复杂度为O(n), 所以整体时间复杂度为O(nlogn).
 空间复杂度：需要一个vector保存合并的结果，空间复杂度为O(n)
 
 */




void __56_entry() {
    vector<vector<int>> intervals =  { {1,3}, {2,6}, {8,10}, {3,5}, {15,18} };
//    intervals =  { {1,4}, {4,5} };
//    intervals =  { {1,4}, {2,3} };
    vector<vector<int>> ret = merge_56::Solution().merge(intervals);
    
    for (auto v : ret) {
        cout << "[" << v[0] << "," << v[1] << "] ";
    }
    
    cout << endl;
}
