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
    
};


#endif /* DenseGraph_hpp */
