//
//  349-intersection.cpp
//  LeetCode
//
//  Created by Knox on 2019/7/7.
//  Copyright © 2019 nchkdxlq. All rights reserved.
//

#include "349-intersection.hpp"
#include "STLHelper.hpp"

/*
 给定两个数组，编写一个函数来计算它们的交集。
 
 示例 1:
 输入: nums1 = [1,2,2,1], nums2 = [2,2]
 输出: [2]
 
 示例 2:
 输入: nums1 = [4,9,5], nums2 = [9,4,9,8,4]
 输出: [9,4]
 
 说明:
 输出结果中的每个元素一定是唯一的。
 我们可以不考虑输出结果的顺序。
 
 来源：力扣（LeetCode）
 链接：https://leetcode-cn.com/problems/intersection-of-two-arrays
 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 */
namespace intersection_349 {
    
    class Solution {
    private:
        vector<int> v1_intersection(vector<int>& nums1, vector<int>& nums2) {
            // 当一个数组为空时，没有交集
            if (nums1.size() == 0 || nums2.size() == 0) return {};
            
            unordered_set<int> nums1_set(nums1.begin(), nums1.end());
            unordered_set<int> nums2_set(nums2.begin(), nums2.end());
            vector<int> ret;
            for (auto i : nums1_set) {
                if (nums2_set.find(i) != nums2_set.end()) {
                    ret.push_back(i);
                }
            }
            
            return ret;
        }
        
        vector<int> v2_intersection(vector<int>& nums1, vector<int>& nums2) {
            // 当一个数组为空时，没有交集
            if (nums1.size() == 0 || nums2.size() == 0) return {};
            
            unordered_set<int> nums1_set(nums1.begin(), nums1.end());
            vector<int> ret;
            
            for (auto i : nums2) {
                if (nums1_set.find(i) != nums1_set.end()) {
                    ret.push_back(i);
                    nums1_set.erase(i);
                }
            }
            
            return ret;
        }
        
    public:
        vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
            return v2_intersection(nums1, nums2);
        }
    };
}

/*
 
 ## 解法一
 
 ### 解题思路
 
 分别对两个数组去重，得到两个set。
 遍历一个set，查看每个元素在另一个set中是否存在。存在则是交集元素，否者不是。
 
 ### 复杂度分析：
 
 n、m分别为两数组的长度
 
 #### 时间复杂度：
 1. 分别对两个数组去重得到set, 时间复杂度为 O(n) + O(m) = O(n+m)
 2. 在set中查找元素是否存在的复杂度为O(1), 所以整个遍历过程时间复杂度为O(k), k为遍历那个set的元素个数，最坏的情况为
    O(max(n,m))
 总结：整体时间复杂度为 O(n+m)
 
 #### 空间复杂度
 1. 两个数组去重得到两个set, 复杂度为 O(n) + O(m) = O(n+m)
 2. 保存交集元素，最坏情况需要min(n,m)个空间，所以 O(min(n,m))
 总结：整体空间复杂度为 O( n + m + min(n,m) )
 
 
 ## 解法二：
 
 ### 解题思路：
 
 对nums1去重得到一个set，遍历nums2, 查看元素在set中是否存在，如果存在把该元素添加到交集数组中去，
 同时在set中删除这个元素，避免nums2中存在重复的元素，添加到交集数组中。
 
 
 ### 复杂度分析：
 
 #### 时间复杂度
 1. 对nums1去重得到set时间复杂度为O(n)
 2. 在set中查找和删除一个元素的时间复杂度都是O(1)，所以遍历nums2时间复杂度为O(m)
 总结：整体时间复杂度为O(max(n,m))
 
 #### 空间复杂度
 1. set空间复杂度为O(n)
 2. 交集数组空间复杂度为O(min(n,m))
 综述：空间复杂度为 O(n)
 */

void __349_entry() {
    vector<int> nums1{4,9,5};
    vector<int> nums2{9,4,9,8,4};
    
    vector<int> ret = intersection_349::Solution().intersection(nums1, nums2);
    
    for (auto i : ret) {
        cout << i << " ";
    }
    
    cout << endl;
}

