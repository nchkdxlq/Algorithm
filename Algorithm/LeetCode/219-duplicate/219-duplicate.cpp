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
        
        
         bool v2_containsNearbyDuplicate(vector<int>& nums, int k) {
             unordered_set<int> tmp_set;
             
             for (int i = 0; i < nums.size(); i++) {
                 if (tmp_set.find(nums[i]) != tmp_set.end()) {
                     return true;
                 } else {
                     tmp_set.insert(nums[i]);
                     if (tmp_set.size() > k) {
                         tmp_set.erase(nums[i-k]);
                     }
                 }
             }
             
             return false;
         }
        
    public:
        bool containsNearbyDuplicate(vector<int>& nums, int k) {
//            return v1_containsNearbyDuplicate(nums, k);
            return v2_containsNearbyDuplicate(nums, k);
        }
    };
}


/**
 
 # 解法一
 
 ## 思路
    使用hashMap记录不同元素出现的下标数组，然后再遍历map, 检查元素的下标数组中是否存在两个下标相差k
 
 ## 算法
    遍历数组，对每一个元素做如下操作
      - 在map中存在，把下标添加到对应的vector中
      - 在map中不存在，创建一个vector，把下标添加到vector中，建立元素与vector的映射关系
 
 ## 复杂度分析
    - 时间复杂度：O(n)遍历数组记录下标为O(n)， 遍历map也是O(n)，所以总体时间复杂度为O(n)
    - 空间复杂度：O(n) 需要开辟额外的空间存储元素和下标的关系。
 
 =================================================
 
 # 解法二
 
 ## 思路：用散列表来维护这个k大小的滑动窗口。
 
 ## 算法：
 遍历数组，对于每个元素做以下操作：
    - 在散列表中搜索当前元素，如果找到了就返回 true。
    - 在散列表中插入当前元素。
    - 如果当前散列表的大小超过了 k， 删除散列表中最旧的元素。
 返回 false。

 ## 复杂度分析
    - 时间复杂度：O(n) 我们会做 n 次 搜索，删除，插入 操作，每次操作都耗费常数时间。
    - 空间复杂度：O(min(n, k)) 开辟的额外空间取决于散列表中存储的元素的个数，也就是滑动窗口的大小 O(min(n,k))。
 
 */


void __219_entry() {
    
    // true
    vector<int> nums = {1,2,3,1};
    int k = 3;
    
    // true
    nums = {1,0,1,1};
    k = 1;
    
    // false
    nums = {1,2,3,1,2,3};
    k = 2;
    
    bool ret = duplicate_219::Solution().containsNearbyDuplicate(nums, k);
    cout << (ret ? "true" : "false") << endl;
}
