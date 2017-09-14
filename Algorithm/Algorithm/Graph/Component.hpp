//
//  Component.hpp
//  Algorithm
//
//  Created by nchkdxlq on 2017/9/14.
//  Copyright © 2017年 nchkdxlq. All rights reserved.
//

#ifndef Component_hpp
#define Component_hpp

#include <stdio.h>
#include <cassert>

/*
 计算图的联通分量
 1. 深度优先遍历（遍历过程是如何，需要弄清楚）
 
 
 */

template<typename Graph>
class Component {
    
private:
    Graph m_G;
    bool *m_visited; //记录顶点是否遍历过
    int m_ccount; //联通分量的数量
    int *m_id; // 并查集
    
    // 递归深度优先遍历
    void dfs(int v) {
        m_visited[v] = true;
        m_id[v] = m_ccount; // 顶点i属于第几个并查集
        
        typename Graph::Itetator iterator(m_G, v);
        for (int w = iterator.begin(); !iterator.end; w = iterator.next()) {
            if (!m_visited[w])
                dfs(w);
        }
    }
    
public:
    Component(Graph &g):m_G(g) {
        int count = g.V();
        m_visited = new bool[count];
        m_id = new int[count];
        m_ccount = 0;
        for (int i = 0; i < count; i++) {
            m_visited[i] = false;
            m_id[i] = -1;
        }
        
        for (int i = 0; i < count; i++) {
            if (!m_visited[i]) {
                dfs(i);
                m_ccount++;
            }
        }
    }
    
    ~Component() {
        delete [] m_visited;
        delete [] m_id;
    }
    
    
    int count() {
        return m_ccount;
    }
    
    bool isConnected(int v, int w) {
        assert(v >= 0 && v < m_G.V());
        assert(w >= 0 && w < m_G.V());
        
        return m_id[v] == m_id[w];
    }
};


#endif /* Component_hpp */
