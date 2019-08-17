//
//  784-letterCasePermutation.cpp
//  LeetCode
//
//  Created by Knox on 2019/8/17.
//  Copyright © 2019 nchkdxlq. All rights reserved.
//

#include "784-letterCasePermutation.hpp"
#include "STLHelper.hpp"


namespace letterCasePermutation_784 {
    class Solution {
    public:
        vector<string> letterCasePermutation(string S) {
            vector<string> res;
            backTrack(S, 0, res);
            return res;
        }
        
    private:
        void backTrack(string &S, int index, vector<string> &res) {
            if (S.length() == index) {
                res.push_back(S);
                return;
            }
            
            char c = S[index];
            if (c > '0' && c < '9') {
                backTrack(S, index+1, res);
            } else {
                backTrack(S, index+1, res);
                /* 同一个字母，大小写ASIIC的值相差32, 并且小写值更大。
                 转大小写问题，一般先判断是大写还是小写，加减32或者调用库函数. 但差值相差32比较特殊，是2^5, 可以使用异或实现，
                 只要异或32就能大写转小写，小写转大写，不需要先判断大小写问题。
                */
                S[index] = c ^ (1 << 5);
                backTrack(S, index+1, res);
                // 回溯
                S[index] = c;
            }
        }
    };
}



void __784_entry() {
    string S = "a1b2"; // [a1b2, a1B2, A1b2, A1B2]
    S = "3z4"; // [3z4, 3Z4]
    S = "12345"; // [12345]
    
    auto res = letterCasePermutation_784::Solution().letterCasePermutation(S);
    
    cout << "==== 784-letterCasePermutation ====" << endl;
    print_vector(res);
    cout << endl << endl;
}
