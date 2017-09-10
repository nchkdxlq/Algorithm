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
#include "UnionFind2.hpp"
#include "UnionFind3.hpp"

namespace UnionFindTestHelper {
    
    using namespace std;
    using namespace UF1;
    using namespace UF2;
    using namespace UF3;
    
    void testUF1(int n) {
        srand((unsigned)time(NULL));
        UF1::UnionFind uf = UF1::UnionFind(n);
        
        clock_t start = clock();
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
    
    
    
    void testUF2(int n) {
        srand((unsigned)time(NULL));
        UF2::UnionFind uf = UF2::UnionFind(n);
        
        clock_t start = clock();
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
        cout << 2*n << " uf2 : " << double(end-start)/CLOCKS_PER_SEC << " s" << endl;
    }
    
    
    void testUF3(int n) {
        srand((unsigned)time(NULL));
        UF3::UnionFind uf = UF3::UnionFind(n);
        
        clock_t start = clock();
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
        cout << 2*n << " uf3 : " << double(end-start)/CLOCKS_PER_SEC << " s" << endl;
    }
    
    
    void run() {
        
        int n = 1000000;
        
//        testUF1(n);
//        testUF2(n);
        testUF3(n);
    }
}


#endif /* UnionTestHelper_hpp */
