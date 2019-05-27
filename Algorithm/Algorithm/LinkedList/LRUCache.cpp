//
//  LRUCache.cpp
//  Algorithm
//
//  Created by nchkdxlq on 2019/5/26.
//  Copyright © 2019 nchkdxlq. All rights reserved.
//

#include "LRUCache.hpp"
#include <cstring>
#include <iostream>

using namespace std;

void lruCache_entry() {
    URLCache<int, int> *cache = new URLCache<int, int>(10);

    for (int i = 0; i < 15; i++) {
        cache->cacheDataWithKey(i, i*100);
    }
    
    int data;
    bool ret = cache->dataForKey(10, &data);
    if (ret) {
        cout << "data = " << data << endl;
    } else {
        cout << "do not cache data" << endl;
    }
    
    delete cache;
}
