//
//  DenseGraph.cpp
//  Algorithm
//
//  Created by nchkdxlq on 2017/9/12.
//  Copyright © 2017年 nchkdxlq. All rights reserved.
//

#include "DenseGraph.hpp"
#include <cassert>

DenseGraph::DenseGraph(int v, bool directed)
{
    m_v = v;
    m_directed = directed;
    
    for (int i = 0; i < v; i++) {
        m_graph.push_back(vector<bool>(v, false));
    }
}

DenseGraph::~DenseGraph()
{
    
}


int DenseGraph::V() {
    return m_v;
}

int DenseGraph::E() {
    return m_e;
}

bool DenseGraph::hasEdge(int v, int w)
{
    assert(v >= 0 && v < m_v);
    assert(w >=0 && w < m_v);
    
    return m_graph[v][w];
}

void DenseGraph::addEdge(int v, int w)
{
    assert(v >= 0 && v < m_v);
    assert(w >= 0 && w < m_v);
    
    if (hasEdge(v, w))
        return;
    
    m_graph[v][w] = true;
    if (!m_directed)
        m_graph[w][v] = true;
        
    m_e++;
}




