//
//  DenseGraph.cpp
//  Algorithm
//
//  Created by nchkdxlq on 2017/9/12.
//  Copyright © 2017年 nchkdxlq. All rights reserved.
//

#include "DenseGraph.hpp"
#include <cassert>
#include <iostream>

using namespace std;

DenseGraph::DenseGraph(int v, bool directed)
{
    m_directed = directed;
    m_v = v;
    m_e = 0;
    
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

void DenseGraph::show()
{
    cout << ">>>>>>>>>>>>> DenseGraph Show <<<<<<<<<<<<" << endl;
    for (int i = 0; i < m_v; i++) {
        vector<bool> e = m_graph[i];
        for (int w = 0; w < m_v; w++) {
            cout << e[w] << "  ";
        }
        cout << endl;
    }
}




