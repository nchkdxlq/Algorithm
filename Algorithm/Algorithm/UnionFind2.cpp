//
//  UnionFind2.cpp
//  Algorithm
//
//  Created by nchkdxlq on 2017/9/10.
//  Copyright © 2017年 nchkdxlq. All rights reserved.
//

#include "UnionFind2.hpp"


namespace UF2 {
    
    UnionFind::UnionFind(int n) {
        m_count = n;
        m_parent = new int[n];
        for (int i = 0; i < n; i++) {
            // 初始化的时候，每个节点的指针都指向它本身
            m_parent[i] = i;
        }
    }
    
    UnionFind::~UnionFind() {
        delete [] m_parent;
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
    
    
    /**
     把两个集合合并为一个集合, 通常把p作为新集合的根
     */
    void UnionFind::unionElements(int p, int q) {
        int pRoot = find(p);
        int qRoot = find(q);
        
        if (pRoot == qRoot)
            return;
    
        m_parent[qRoot] = pRoot;
    }
    
}
