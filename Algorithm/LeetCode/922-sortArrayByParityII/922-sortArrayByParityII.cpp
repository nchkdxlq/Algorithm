//
//  922-sortArrayByParityII.cpp
//  LeetCode
//
//  Created by Knox on 2019/7/13.
//  Copyright © 2019 nchkdxlq. All rights reserved.
//

#include "922-sortArrayByParityII.hpp"
#include "stlheaders.h"


namespace sortArrayByParityII_922 {
    
    class Solution {
        
        vector<int> v1_sortArrayByParityII(vector<int>& A) {
            
            int i = 0;
            while (i < A.size()) {
                if ((i & 1) == (A[i] & 1)) {
                    i++;
                } else {
                    int j = i + 1;
                    while ((j & 1) != (A[i] & 1)) {
                        j++;
                    }
                    swap(A[i], A[j]);
                    i++;
                }
            }
            
            
            return A;
        }
        
        // 双指针
        vector<int> v2_sortArrayByParityII(vector<int>& A) {
            
            int i = 0, j = 1;
            while (true)  {
                while (i < A.size() && (A[i] & 1) == 0) {
                    i += 2;
                }
                while (j < A.size() && (A[j] & 1) == 1) {
                    j += 2;
                }
                
                if (i < A.size() && j < A.size()) {
                    swap(A[i], A[j]);
                    i += 2;
                    j += 2;
                } else {
                    break;
                }
            }
            
            return A;
        }
        
        // 奇数元素放到新数组的下标奇数的位置，偶数放到下标为偶数的位置
        vector<int> v3_sortArrayByParityII(vector<int>& A) {
            vector<int> ret(A.size(), 0);
            
            int i = 0, j = 1;
            for (auto item : A) {
                if ((item & 1) == 1) { // 奇数
                    ret[j] = item;
                    j += 2;
                } else { // 偶数
                    ret[i] = item;
                    i += 2;
                }
            }
            
            return ret;
        }
        
    public:
        
        vector<int> sortArrayByParityII(vector<int>& A) {
//            return v1_sortArrayByParityII(A);
//            return v2_sortArrayByParityII(A);
            return v3_sortArrayByParityII(A);
        }
    };
}


void __922_entry() {
    
    vector<int> nums = {4,2,5,7};
    
    vector<int> ret = sortArrayByParityII_922::Solution().sortArrayByParityII(nums);
    
    bool status = true;
    for (int i = 0; i < ret.size(); i++) {
        if (status == false) {
            break;
        }
        status = (i & 1) == (ret[i] & 1);
    }
    cout << (status ? "true" : "false") << endl;
}
