//
//  UnionFind1.cpp
//  Algorithm
//
//  Created by nchkdxlq on 2017/9/10.
//  Copyright © 2017年 nchkdxlq. All rights reserved.
//

#include "UnionFind1.hpp"
#include <cassert>

namespace UF1 {
    
    UnionFind::UnionFind(int count) {
        m_id = new int[count];
        m_count = count;
        
        for (int i = 0; i < count; i++) {
            m_id[i] = i;
        }
    }
    
    UnionFind::~UnionFind() {
        delete [] m_id;
    }
    
    int UnionFind::find(int p) {
        assert(p >= 0 && p < m_count);
        return m_id[p];
    }
    
    bool UnionFind::isConnected(int p, int q) {
        return find(p) == find(q);
    }
    
    void UnionFind::unionElements(int p, int q) {
        int pId = find(p);
        int qId = find(q);
        
        if (pId == qId)
            return;
        
        for (int i = 0; i < m_count; i++) {
            if (m_id[i] == qId)
                m_id[i] = pId;
        }
    }
    
    
}
