//
//  STLHelper.hpp
//  LeetCode
//
//  Created by Knox on 2019/7/28.
//  Copyright © 2019 nchkdxlq. All rights reserved.
//

#ifndef STLHelper_hpp
#define STLHelper_hpp

#include <stdio.h>

#include <iostream>

#include <vector>
#include <string>

#include <map>
#include <unordered_map>

#include <set>
#include <unordered_set>

#include <queue>
#include <stack>

#include <cassert>

using namespace std;


namespace STLHelper {
    
    template<class T>
    void print_vector(vector<T> &__vector) {
        cout << "[";
        int size = (int)__vector.size();
        int endIndex = size - 1;
        for (int i = 0; i < size; i++) {
            cout << __vector[i];
            if (i < endIndex) {
                cout << ", ";
            }
        }
        cout << "]";
    }
}



#endif /* STLHelper_hpp */
