//
//  UnionFind2.hpp
//  Algorithm
//
//  Created by nchkdxlq on 2017/9/10.
//  Copyright © 2017年 nchkdxlq. All rights reserved.
//

#ifndef UnionFind2_hpp
#define UnionFind2_hpp

#include <stdio.h>




/*
 
 将每一个元素,看做是一个节点
 每个节点有一个指针，指针指向它的父亲节点，
 当节点没有父节点时，则指针指向节点自身。
 
 
 */

namespace UF2 {
    
    class UnionFind {
        
    private:
        int* m_parent;
        int m_count;
        
    public:
        UnionFind(int n);
        ~UnionFind();
        int find(int p);
        bool isConnected(int p, int q);
        void unionElements(int p, int q);
        
    };
    
}


#endif /* UnionFind2_hpp */
