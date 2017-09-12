//
//  UnionFind4.hpp
//  Algorithm
//
//  Created by nchkdxlq on 2017/9/10.
//  Copyright © 2017年 nchkdxlq. All rights reserved.
//

#ifndef UnionFind4_hpp
#define UnionFind4_hpp

#include <stdio.h>

namespace UF4 {
    
    /*
     基于rank的优化
     rank[i]表示根节点为i的树的层数
     
     
     */
    class UnionFind {
        
    private:
        int* m_parent;
        int* m_rank; // m_rank[i]表示以i为根的集合所表示的树的层数
        int m_count;
        
    public:
        UnionFind(int n);
        ~UnionFind();
        int find(int p);
        bool isConnected(int p, int q);
        void unionElements(int p, int q);
        
    };
    
}



#endif /* UnionFind4_hpp */
