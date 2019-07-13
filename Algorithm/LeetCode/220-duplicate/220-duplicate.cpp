//
//  220-duplicate.cpp
//  LeetCode
//
//  Created by Knox on 2019/7/13.
//  Copyright © 2019 nchkdxlq. All rights reserved.
//

#include "220-duplicate.hpp"
#include "stlheaders.h"


/**
 
 给定一个整数数组，判断数组中是否有两个不同的索引 i 和 j，使得 nums [i] 和 nums [j] 的差的绝对值最大为 t，并且 i 和 j 之间的差的绝对值最大为 ķ。
 
 示例 1:
 输入: nums = [1,2,3,1], k = 3, t = 0
 输出: true
 
 示例 2:
 输入: nums = [1,0,1,1], k = 1, t = 2
 输出: true
 
 示例 3:
 输入: nums = [1,5,9,1,5,9], k = 2, t = 3
 输出: false
 
 来源：力扣（LeetCode）
 链接：https://leetcode-cn.com/problems/contains-duplicate-iii
 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 */

namespace duplicate_220 {
    
    class Solution {
    public:
        bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
            if (nums.size() == 0 && k == 0) return false;
            
            set<long> tmp_set;
            
            for (int i = 0; i < nums.size(); i++) {
                long max = (long)nums[i] + (long)t; // 满足条件的最大值
                long min = (long)nums[i] - (long)t; // 满足条件的最小值
                
                // 查找是否存在 >= min && <= max 元素
                auto lower_bound = tmp_set.lower_bound(min);
                if (lower_bound != tmp_set.end() && (long)(*lower_bound) <= max) {
                    return true;
                }

                tmp_set.insert(nums[i]);
                if (tmp_set.size() > k) {
                    tmp_set.erase((long)nums[std::max(0,i-k)]);
                }
            }
            
            return false;
        }
    };
}

/**
 
 # 解法一
 
 ## 思路
    维护一个k大小的滑动窗口，在滑动窗口内查看元素是否满足 nums[i] - nums[j] 绝对值满足小于 t
 
 ## 算法
    遍历数组，对每一个元素做如下操作
    1. 计算出满足条件的最值min、max
    2. 在set中查找存在满足元素 e 满足， min <= e <= max.
    3. 当set中元素多余k个时，删除最近的那个元素，以维护k大小的滑动窗口
 
 ## 复杂度分析
    - 时间复杂度 O(n)* O(log(min(n,k))) = O(nlog(min(n,k))), 遍历数组时间复杂度为O(n)，
        维护min(n,k)大小的有序set时间复杂度为O(log(min(n,k)))
 
    - 空间复杂度 O(min(n,k))
 
 */




void __220_entry() {
    vector<int> nums = {0,2147483647};
    int k = 1, t = 2147483647;
    
    // true
    nums = {1,2,3,1};
    k = 3; t = 0;
    
    // true
    nums = {1,0,1,1};
    k = 1; t = 2;
    
    // false
    nums = {1,5,9,1,5,9};
    k = 2; t = 3;
    
    // false
    nums = {1,2};
    k = 0; t = 1;

    // true
    nums = {4,1,6,3};
    k = 100; t = 1;
    
    // false
    nums = {1,5,9,1,5,9};
    k = 2; t = 3;
    
    bool ret = duplicate_220::Solution().containsNearbyAlmostDuplicate(nums, k, t);
    cout << (ret ? "true" : "false") << endl;
}
