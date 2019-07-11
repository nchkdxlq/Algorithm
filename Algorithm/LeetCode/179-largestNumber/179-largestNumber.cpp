//
//  179-largestNumber.cpp
//  LeetCode
//
//  Created by Knox on 2019/7/11.
//  Copyright © 2019 nchkdxlq. All rights reserved.
//

#include "179-largestNumber.hpp"
#include "stlheaders.h"

/**
 
 给定一组非负整数，重新排列它们的顺序使之组成一个最大的整数。
 
 示例 1:
 输入: [10,2]
 输出: 210
 
 示例 2:
 输入: [3,30,34,5,9]
 输出: 9534330
 
 说明: 输出结果可能非常大，所以你需要返回一个字符串而不是整数。
 
 来源：力扣（LeetCode）
 链接：https://leetcode-cn.com/problems/largest-number
 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 
 */



namespace largestNumber_179 {
    
    // 把数字转换为字符串，然后利用字符串相加比较，实在是妙
    bool compare(int &l, int &r) {
        string s1 = to_string(l);
        string s2 = to_string(r);
        return (s1+s2) > (s2+s1);
    }
    
    class Solution {
    public:
        
        string largestNumber(vector<int>& nums) {
            if (nums.size() == 0) return "0";
            
            sort(nums.begin(), nums.end(), compare);
            
            // 当第一个元素为0时，说明整个数组所有元素都是0，返回"0"
            if (nums[0] == 0) return "0";
            
            string ret = "";
            for (auto i : nums) {
                ret += to_string(i);
            }
        
            return ret;
        }
    };
}


void __179_entry() {
    vector<int> nums{3,30,34,5,9};
    cout << "9534330" << endl;
    string ret = largestNumber_179::Solution().largestNumber(nums);
    cout << ret << endl;
}
