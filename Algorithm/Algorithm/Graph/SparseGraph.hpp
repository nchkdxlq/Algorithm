//
//  SparseGraph.hpp
//  Algorithm
//
//  Created by nchkdxlq on 2017/9/13.
//  Copyright © 2017年 nchkdxlq. All rights reserved.
//

#ifndef SparseGraph_hpp
#define SparseGraph_hpp

#include <stdio.h>
#include <vector>

using namespace std;

/* 
 稀疏图 邻接表
 
 缺点：
 1.
 
 */
class SparseGraph {
    
private:
    int m_v; // 顶点的个数 （vertex count）
    int m_e; // 边数 (edge count)
    bool m_directed;
    vector<vector<int>> m_graph;

public:
    SparseGraph(int n, bool directed);
    ~SparseGraph();
    
    int V();
    int E();
    
    bool hasEdge(int v, int w);
    void addEdge(int v, int w);
    void show();
    
    class Iterator {
    private:
        SparseGraph &m_G;
        int m_vertex;
        int m_index;
        
    public:
        Iterator(SparseGraph &g, int v): m_G(g) {
            m_vertex = v;
            m_index = -1;
        }
        
        ~Iterator() {
            
        }
        
        int begin() {
            m_index = 0;
            if (m_G.m_graph[m_vertex].size() > 0)
                return m_G.m_graph[m_vertex][0];
            return -1;
        }
        
        int next() {
            m_index++;
            if (m_index < m_G.m_graph[m_vertex].size())
                return m_G.m_graph[m_vertex][m_index];
            return -1;
        }
        
        bool end() {
            return m_index >= m_G.m_graph[m_vertex].size();
        }
    };
};




#endif /* SparseGraph_hpp */
