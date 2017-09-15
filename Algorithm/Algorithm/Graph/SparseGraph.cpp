//
//  SparseGraph.cpp
//  Algorithm
//
//  Created by nchkdxlq on 2017/9/13.
//  Copyright © 2017年 nchkdxlq. All rights reserved.
//

#include "SparseGraph.hpp"
#include <cassert>
#include <iostream>

using namespace std;

SparseGraph::SparseGraph(int n, bool directed) {
    
    m_directed = directed;
    m_v = n;
    m_e = 0;
    
    for (int i = 0; i < n; i++) {
        m_graph.push_back(vector<int>());
    }
}

SparseGraph::~SparseGraph() {
    
}


int SparseGraph::V() {
    return m_v;
}

int SparseGraph::E() {
    return m_e;
}



/**
 两个顶点是否相连

 时间复杂度为 O(n)
 
 @param v 顶点v
 @param w 顶点w
 */
bool SparseGraph::hasEdge(int v, int w) {
    assert(v >= 0 && v < m_v);
    assert(w >= 0 && v < m_v);
    
    vector<int> v_vector = m_graph[v];
    int size = (int)v_vector.size();
    for (int i = 0; i < size; i++) {
        if (v_vector[i] == w)
            return true;
    }
    return false;
}

void SparseGraph::addEdge(int v, int w) {
    assert(v >= 0 && v < m_v);
    assert(w >= 0 && w < m_v);
    
    if (hasEdge(v, w))
        return;
    
    m_graph[v].push_back(w);
    if (!m_directed)
        m_graph[w].push_back(v);
    
    m_e++;
}

void SparseGraph::show()
{
    cout << ">>>>>>>>>>>>> SparseGraph Show <<<<<<<<<<<<" << endl;
    for (int i = 0; i < m_v; i++) {
        cout << "Vertex " << i << " :  ";
        Iterator iter(*this, i);
        for (int w = iter.begin(); !iter.end(); w = iter.next()) {
            cout << w << "  ";
        }
        cout << endl;
    }
}







