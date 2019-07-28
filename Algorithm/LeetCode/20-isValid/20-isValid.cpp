//
//  20-isValid.cpp
//  LeetCode
//
//  Created by Knox on 2019/7/6.
//  Copyright © 2019 nchkdxlq. All rights reserved.
//

#include "20-isValid.hpp"
#include "STLHelper.hpp"


namespace isValid_20 {
    
    class Solution {
    public:
        bool isValid(string s) {
            
            unordered_map<char, char> mp = { {')','('}, {']','['}, {'}','{'} };
            stack<char> tmp;
            
            for (auto item : s) {
                if (mp.find(item) != mp.end()) { // 右括号
                    
                    if (mp.empty()) return false;
                    
                    if (tmp.top() == mp[item]) {
                        tmp.pop();
                    } else {
                        return false;
                    }
                } else { // 左括号，放入栈中
                    tmp.push(item);
                }
            }
            
            return tmp.empty();
        }

    };
}





void __20_entry() {
    
    string s1 = "()";
    isValid_20::Solution().isValid(s1);
}
