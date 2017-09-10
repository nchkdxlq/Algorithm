//
//  UnionFind3.hpp
//  Algorithm
//
//  Created by nchkdxlq on 2017/9/10.
//  Copyright © 2017年 nchkdxlq. All rights reserved.
//

#ifndef UnionFind3_hpp
#define UnionFind3_hpp

#include <stdio.h>

namespace UF3 {
    
    /*
     基于size的优化
     m_sz数组是指以某个根节点为集合的元素个数
     */
    
    class UnionFind {
        
    private:
        int* m_parent;
        int* m_sz;
        int m_count;
        
    public:
        UnionFind(int n);
        ~UnionFind();
        int find(int p);
        bool isConnected(int p, int q);
        void unionElements(int p, int q);
        
    };
    
}


#endif /* UnionFind3_hpp */
