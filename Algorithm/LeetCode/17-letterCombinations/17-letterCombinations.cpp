//
//  17-letterCombinations.cpp
//  LeetCode
//
//  Created by Knox on 2019/8/17.
//  Copyright © 2019 nchkdxlq. All rights reserved.
//

#include "17-letterCombinations.hpp"
#include "STLHelper.hpp"

/**
 17. 电话号码的字母组合
 
 给定一个仅包含数字 2-9 的字符串，返回所有它能表示的字母组合。
 {1:""}, {2:abc}, {3:def}, {4:ghi}, {5:jkl}, {6:mno}, {7:pqrs}, {tuv}, {9:wxyz}
 https://leetcode-cn.com/problems/letter-combinations-of-a-phone-number/

 
 */

namespace letterCombinations_17 {
    class Solution {
    public:
        vector<string> letterCombinations(string digits) {
            // 对输入的字符串判空处理
            if (digits.empty()) return {};
            string p;
            letterCombinations_helper(digits, 0, p);
            return res;
        }
        
    private:
        vector<string> letersMap = {
            "",
            "",
            "abc",
            "def",
            "ghi",
            "jkl",
            "mno",
            "pqrs",
            "tuv",
            "wxyz"
        };
        
        vector<string> res;
        
        void letterCombinations_helper(string &digits, int index, string &subStr) {
            if (digits.length() == index) {
                res.push_back(subStr);
                return;
            }
            char c = digits[index];
            string letters = letersMap[c - '0'];
            for (int i = 0; i < letters.length() ; i++) {
                subStr.push_back(letters[i]);
                letterCombinations_helper(digits, index+1, subStr);
                subStr.pop_back();
            }
        }
    };
}



void __17_entry() {
    string digits = "23";
    
    vector<string> res = letterCombinations_17::Solution().letterCombinations(digits);
    cout << "==== 17-letterCombinations ====" << endl;
    print_vector(res);
    cout << endl << endl;
}
