//
//  UnionTestHelper.hpp
//  Algorithm
//
//  Created by nchkdxlq on 2017/9/10.
//  Copyright © 2017年 nchkdxlq. All rights reserved.
//

#ifndef UnionTestHelper_hpp
#define UnionTestHelper_hpp

#include <stdio.h>
#include <ctime>
#include <iostream>
#include "UnionFind1.hpp"

namespace UnionFindTestHelper {
    
    using namespace UF1;
    using namespace std;
    
    
    void uf1(int n) {
        
        clock_t start = clock();
        
        srand((unsigned)time(NULL));

        UnionFind uf = UnionFind(n);
        
        for (int i = 0; i < n; i++) {
            int a = rand() % n;
            int b = rand() % n;
            uf.unionElements(a, b);
        }
        
        for (int i = 0; i < n; i++) {
            int a = rand() % n;
            int b = rand() % n;
            uf.isConnected(a, b);
        }
        
        clock_t end = clock();
        
        
        cout << 2*n << " uf1 : " << double(end-start)/CLOCKS_PER_SEC << " s" << endl;
    }
    
    void run() {
        
        int n = 100000;
        
        uf1(n);
    }
}


#endif /* UnionTestHelper_hpp */
