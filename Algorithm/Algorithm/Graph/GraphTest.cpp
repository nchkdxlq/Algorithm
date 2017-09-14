//
//  GraphTest.cpp
//  Algorithm
//
//  Created by nchkdxlq on 2017/9/13.
//  Copyright © 2017年 nchkdxlq. All rights reserved.
//

#include "GraphTest.hpp"
#include <ctime>
#include <iostream>
#include "SparseGraph.hpp"
#include "DenseGraph.hpp"


using namespace std;


void sparseGraphTest(int n, int m)
{
    cout << ">>>>>>>>>>>>>> Sparse Graph Test <<<<<<<<<<<<<<" << endl;
    
    SparseGraph graph(n, false);
    srand((unsigned int)(time(nullptr)));
    
    for (int i = 0; i < m; i++) {
        int a = rand() % n;
        int b = rand() % n;
        graph.addEdge(a, b);
    }
    
    cout << "Edge :" << graph.E() << endl;
    cout << endl;
    
    for (int i = 0; i < n; i++) {
        cout << i << " : ";
        SparseGraph::Iterator iterator(graph, i);
        for (int w = iterator.begin(); !iterator.end(); w = iterator.next()) {
            cout << w << " ";
        }
        cout << endl;
    }
    
    cout << endl;
}

void denseGraphTest(int n, int m)
{
    cout << ">>>>>>>>>>>>>> Dense Graph Test <<<<<<<<<<<<<<" << endl;
    
    DenseGraph graph(n, false);
    srand((unsigned int)(time(nullptr)));
    
    for (int i = 0; i < m; i++) {
        int a = rand() % n;
        int b = rand() % n;
        graph.addEdge(a, b);
    }
    
    cout << "Edge :" << graph.E() << endl;
    cout << endl;
    
    for (int i = 0; i < n; i++) {
        cout << i << " : ";
        DenseGraph::Iterator iterator(graph, i);
        for (int w = iterator.begin(); !iterator.end(); w = iterator.next()) {
            cout << w << " ";
        }
        cout << endl;
    }
    
    cout << endl;
}


void graphTest()
{
    int n = 20, m = 100;
    sparseGraphTest(n, m);
    denseGraphTest(n, m);
}
