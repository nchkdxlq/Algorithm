//
//  217-duplicate.cpp
//  LeetCode
//
//  Created by Knox on 2019/7/12.
//  Copyright © 2019 nchkdxlq. All rights reserved.
//

#include "217-duplicate.hpp"
#include "STLHelper.hpp"


/**
 
 给定一个整数数组，判断是否存在重复元素。
 
 如果任何值在数组中出现至少两次，函数返回 true。如果数组中每个元素都不相同，则返回 false。
 
 示例 1:
 输入: [1,2,3,1]
 输出: true
 
 示例 2:
 输入: [1,2,3,4]
 输出: false
 
 示例 3:
 输入: [1,1,1,3,3,4,3,2,4,2]
 输出: true
 
 来源：力扣（LeetCode）
 链接：https://leetcode-cn.com/problems/contains-duplicate
 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 
 */

namespace duplicate_217 {
    
    class Solution {
    private:
        // 利用hash_set是最容易想到的做法，利用set元素的唯一性
        bool v1_containsDuplicate(vector<int>& nums) {
            unordered_set<int> tmp_set;
            
            for (auto i : nums) {
                if (tmp_set.find(i) != tmp_set.end()) {
                    return true;
                } else {
                    tmp_set.insert(i);
                }
            }
            
            return false;
        }
        
        // 对输入先做预处理
        bool v2_containsDuplicate(vector<int>& nums) {
            sort(nums.begin(), nums.end());
            
            for (int i = 1; i < nums.size(); i++) {
                if (nums[i] == nums[i-1]) {
                    return true;
                }
            }
            
            return false;
        }

        
    public:
        bool containsDuplicate(vector<int>& nums) {
//            return v1_containsDuplicate(nums);
            return v2_containsDuplicate(nums);
        }
    };
}




void __217_entry() {
    vector<int> nums{2, 14, 18, 22, 22};
    bool ret = duplicate_217::Solution().containsDuplicate(nums);
    cout << (ret ? "contains" : "not contains") << endl;
}


/*
 复杂度分析参考：
 https://leetcode-cn.com/problems/contains-duplicate/solution/cun-zai-zhong-fu-yuan-su-by-leetcode/
 
 
 */
