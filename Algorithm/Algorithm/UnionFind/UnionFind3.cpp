//
//  UnionFind3.cpp
//  Algorithm
//
//  Created by nchkdxlq on 2017/9/10.
//  Copyright © 2017年 nchkdxlq. All rights reserved.
//

#include "UnionFind3.hpp"

namespace UF3 {
    
    UnionFind::UnionFind(int n) {
        m_count = n;
        m_parent = new int[n];
        m_sz = new int[n];
        for (int i = 0; i < n; i++) {
            // 初始化的时候，每个节点的指针都指向它本身
            m_parent[i] = i;
            m_sz[i] = 1;
        }
    }
    
    UnionFind::~UnionFind() {
        delete [] m_parent;
        delete [] m_sz;
    }
    
    int UnionFind::find(int p) {
        while (p != m_parent[p]) {
            p = m_parent[p];
        }
        return p;
    }
    
    bool UnionFind::isConnected(int p, int q) {
        return find(p) == find(q);
    }
    
    
    void UnionFind::unionElements(int p, int q) {
        int pRoot = find(p);
        int qRoot = find(q);
        
        if (pRoot == qRoot)
            return;
        
        /*
         把元素少的集合合并到元素多的集合中，这样在大多数情况下可以让生成的树层数更少，
         从而是查询的时间更短
         
         而m_parent[qRoot] = pRoot; 这种做法会使得树的层数很多
         */
        if (m_sz[pRoot] < m_sz[qRoot]) {
            m_parent[pRoot] = qRoot;
            m_sz[qRoot] += m_sz[pRoot];
        } else {
            m_parent[qRoot] = pRoot;
            m_sz[pRoot] += m_sz[qRoot];
        }
    }
    
}
