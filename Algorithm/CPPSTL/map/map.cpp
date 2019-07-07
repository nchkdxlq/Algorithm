//
//  map.cpp
//  CPPSTL
//
//  Created by Knox on 2019/7/6.
//  Copyright © 2019 nchkdxlq. All rights reserved.
//

#include "map.hpp"
#include <iostream>
#include <map>

using namespace std;



/**
 
 
 template<
 class Key,
 class T,
 class Compare = std::less<Key>,
 class Allocator = std::allocator<std::pair<const Key, T> >
 > class map;
 
 std:map 是有序键值对容器，它的元素的键是唯一的。用比较函数 Compare 排序键。
 
 map时间时间复杂度分析
 1. 插入：log(n)
 2. 删除：log(n)
 3. 查找：log(n)
 
底层实现：通常实现为红黑树。
 
 */


void map_entry() {

    // 初始化map
//    map<int, int> mp = {{1,1}, {2,3}};
    map<int, int> mp{{1,10}, {2,30}};
    
    mp.size();
    mp.empty();
    mp.max_size();
    
    // 插入
    mp[1] = 10;
    
    // 删除指定的键值
    mp.erase(1);
    // 清空map
    mp.clear();
    
    // 取值
    int value = mp[1];
    cout << value << endl;
    
    auto ret = mp.find(1); // 返回的是iterator, 如果不存在 mp.end();
    
    
    // 遍历
    mp.begin();
    mp.end();
    
    mp.rbegin();
    mp.rend();
    
    
    
    for (auto item : mp) {
        cout << "key = " << item.first << "value = " << item.second << endl;
    }
    
}
