//
//  UnionFind5.hpp
//  Algorithm
//
//  Created by nchkdxlq on 2017/9/10.
//  Copyright © 2017年 nchkdxlq. All rights reserved.
//

#ifndef UnionFind5_hpp
#define UnionFind5_hpp

#include <stdio.h>



namespace UF5 {
    
    /*
     路径压缩 （Path Compression）
     
     在UF4的基础上优化，UF3/UF4都是对union操作进行优化的，
     路径压缩是对find操作进行优化的。
     
     具体过程如下：
     在执行find操作的同时
     
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



#endif /* UnionFind5_hpp */
