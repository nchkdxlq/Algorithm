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
    int m_v;
    int m_e;
    bool m_directed;
    vector<vector<int>> m_graph;

public:
    SparseGraph(int n, bool directed);
    ~SparseGraph();
    
    int V();
    int E();
    
    bool hasEdge(int v, int w);
    void addEdge(int v, int w);
    
};




#endif /* SparseGraph_hpp */
