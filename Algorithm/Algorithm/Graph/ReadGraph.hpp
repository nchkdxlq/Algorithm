//
//  ReadGraph.hpp
//  Algorithm
//
//  Created by nchkdxlq on 2017/9/15.
//  Copyright © 2017年 nchkdxlq. All rights reserved.
//

#ifndef ReadGraph_hpp
#define ReadGraph_hpp

#include <stdio.h>
#include <string>
#include <fstream>
#include <sstream>
#include <cassert>

using namespace std;

template<typename Graph>
class ReadGraph {
    Graph *m_g;
    
public:
    ReadGraph<Graph>(const string &fileName) {
        
        ifstream file(fileName);
        string line;
        int V, E;
        bool directed;
        assert(file.is_open());
        assert(getline(file, line));
        stringstream ss(line);
        ss >> V >> E >> directed;
        
        assert(V >= 0 && E >= 0);
        
        m_g = new Graph(V, directed);
        
        for (int i = 0; i < E; i++) {
            assert(getline(file, line));
            stringstream ss(line);
            int a, b;
            ss >> a >> b;
            assert(a >= 0 && a < E);
            assert(b >= 0 && b < E);
            m_g->addEdge(a, b);
        }
    }
    
    ~ReadGraph() {
        delete m_g;
    }
    
    
    Graph graph() {
        return *m_g;
    }
};



#endif /* ReadGraph_hpp */
