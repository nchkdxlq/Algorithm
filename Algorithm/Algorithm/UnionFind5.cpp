//
//  UnionFind5.cpp
//  Algorithm
//
//  Created by nchkdxlq on 2017/9/10.
//  Copyright © 2017年 nchkdxlq. All rights reserved.
//

#include "UnionFind5.hpp"


namespace UF5 {
    
    UnionFind::UnionFind(int n) {
        m_count = n;
        m_parent = new int[n];
        m_rank = new int[n];
        for (int i = 0; i < n; i++) {
            // 初始化的时候，每个节点的指针都指向它本身
            m_parent[i] = i;
            m_rank[i] = 1;
        }
    }
    
    UnionFind::~UnionFind() {
        delete [] m_parent;
        delete [] m_rank;
    }
    
    int UnionFind::find(int p) {
#if 1
        // 效率更高
        while (p != m_parent[p]) {
            m_parent[p] = m_parent[m_parent[p]];
            p = m_parent[p];
        }
        return m_parent[p];
#else
        /*
         递归的方式进行路径压缩，使得所有的节点都指向同一个节点，使得数的层数为1
         p节点的父亲等于其父亲节点的根节点，一直递归，直到根节点为止。
         */
        if (m_parent[p] != p)
            m_parent[p] = find(m_parent[p]);
        
        return m_parent[p];
#endif
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
         问题：在UnionFind3中，合并集合时能够保证在大多数情况下可以让生成的树层数更低，
         但是在有些情况下，会使得树的层数很高
         
         优化: 把层数低的树合并到层数高的树中，尽可能保持树的层数最低
         */
        
        if (m_rank[pRoot] < m_rank[qRoot]) {
            m_parent[pRoot] = qRoot;
        } else if (m_rank[pRoot] > m_rank[qRoot]) {
            m_parent[qRoot] = pRoot;
        } else {
            m_parent[qRoot] = pRoot;
            m_rank[pRoot] += 1;
        }
    }
    
}
