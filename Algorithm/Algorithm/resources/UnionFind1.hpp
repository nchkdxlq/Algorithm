//
//  UnionFind1.hpp
//  Algorithm
//
//  Created by nchkdxlq on 2017/9/10.
//  Copyright © 2017年 nchkdxlq. All rights reserved.
//

#ifndef UnionFind1_hpp
#define UnionFind1_hpp

#include <stdio.h>


namespace UF1 {
    
    class UnionFind {
        
    private:
        int *m_id;
        int m_count;
        
    public:
        UnionFind(int count);
        ~UnionFind();
        
        int find(int p);
        bool isConnected(int p, int q);
        void unionElements(int p, int q);
    };
}



#endif /* UnionFind1_hpp */
