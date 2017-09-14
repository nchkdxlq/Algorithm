//
//  DenseGraph.hpp
//  Algorithm
//
//  Created by nchkdxlq on 2017/9/12.
//  Copyright © 2017年 nchkdxlq. All rights reserved.
//

#ifndef DenseGraph_hpp
#define DenseGraph_hpp

#include <stdio.h>
#include <vector>

using namespace std;


// 稠密图 - 邻接矩阵
class DenseGraph {

private:
    int m_v; // 顶点的个数 （vertex count）
    int m_e; // 边数 (edge count)
    bool m_directed;
    vector<vector<bool>> m_graph;
    
    
public:
    DenseGraph(int v, bool directed);
    ~DenseGraph();
    
    int V();
    int E();
    
    bool hasEdge(int v, int w);
    void addEdge(int v, int w);
    
    
    class Iterator {
        
    private:
        DenseGraph &m_G;
        int m_vertext;
        int m_index;
        
    public:
        Iterator(DenseGraph &g, int vertext):m_G(g) {
            m_vertext = vertext;
            m_index = -1;
        }
        
        ~Iterator() {
            
        }
        
        int begin() {
            m_index = -1;
            return next();
        }
        
        int next() {
            m_index++;
            vector<bool> edge = m_G.m_graph[m_vertext];
            
            for (m_index += 1; m_index < edge.size(); m_index++) {
                if (edge[m_index])
                    return m_index;
            }
            return -1;
        }
        
        bool end() {
            return m_index >= m_G.m_graph[m_vertext].size();
        }
    };
    
};


#endif /* DenseGraph_hpp */
