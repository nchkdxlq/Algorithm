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
#include <unordered_map>

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
 
 
 
 注意事项：
 查找某个key在map中是否存在，使用itetator ret = mp.find( key )，ret == mp.end()，代表不存在。
 
 如果mp中存在key, 使用mp[key]，会返回对应的value；如果不存在，返回value类型的默认值，
 例如：int类型为0，string类型为""，并且把这个默认值存在map中，遍历map的时候会存在。
 ##但是##，使用mp.find( key )，返回的还是 mp.end()，表示不存在。
 
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
    mp[33] = 0;
    bool existed = mp.find(33) != mp.end();
    cout << "first - 33 " << (existed ? "exist" : "not exist") << " in map" << endl;
    int count = mp[33];
    cout << "second - 33 " << (existed ? "exist" : "not exist") << " in map" << endl;
    // 遍历
    mp.begin();
    mp.end();
    
    mp.rbegin();
    mp.rend();
    
    
    
    for (auto item : mp) {
        cout << "[" << item.first << ":" << item.second << "] ";
    }
    cout << endl;
}



void unordered_map_entry() {
    
    unordered_map<int,int> mp;
    mp[1] = 100;
    mp.count(1);
    
    
}
