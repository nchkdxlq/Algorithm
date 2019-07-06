//
//  set.cpp
//  STLDemo
//
//  Created by nchkdxlq on 2019/6/11.
//  Copyright © 2019 luoquan. All rights reserved.
//

#include "set.hpp"
#include <iostream>
#include <set>
#include <vector>

using namespace std;



/**
 https://zh.cppreference.com/w/cpp/container/set
 
 template<
 class Key,
 class Compare = std::less<Key>,
 class Allocator = std::allocator<Key>
 > class set;
 
 set时间时间复杂度分析
 1. 插入：nlog(n)
 2. 删除：nlog(n)
 3. 查找：nlog(n)
 
 底层实现：红黑树
 
 容量
 s.empty();
 s.size();
 s.max_size();
 
 
 修改
 s.insert(1); // 插入一个元素
 s.erase(2); // 删除指定的值
 s.clear(); // 清空set
 
 
 查找
 s.count(1); // 返回指定元素的个数，1：存在， 0：不存在
 s.find(1); // 返回指定元素的iterator， 如果不存在 返回s.end()
 
 
 
 迭代器
 s.begin(); // 指向第一个元素
 s.end(); // 指向最后一个元素的后一个位置
 
 s.rbegin(); // 指向最后一个元素
 s.rend(); // 指向第一个元素前一个位置
 
 */


int thirdMax(vector<int>& nums) {
    set<int> s;
    
    for (auto i : nums) {
        s.insert(i);
        if (s.size() > 3) {
            s.erase(s.begin());
        }
    }
    
    if (s.size() < 3) {
        return *(s.rbegin());
    } else {
        return *(s.begin());
    }
}


void set_entry() {
    
    std::set<int> s;
    
    /*
     
     默认情况下，set对元素从小到大排序
     
     s.insert(1); // 插入一个元素
     s.erase(1); // 删除一个元素
     
     s.empty(); // 判空
     s.size(); // 元素个数
     int ret = s.count(1); // 是否存在某个元素，ret 的值为 1 或者 0， 1表示存在
     
     s.clear(); // 清空整个set
     
    */
    
    s.insert(3);
    s.insert(2);
    s.insert(1);
    
    for (auto num : s) {
        cout << num << " ";
    }
    cout << endl;
    
    cout << "======== 顺序遍历 ========" << endl;
    for (auto i = s.begin(); i != s.end(); i++) {
        cout << *i << " ";
    }
    cout << endl;
    
    cout << "======== 逆序遍历 ========" << endl;
    for (auto i = s.rbegin(); i != s.rend(); i++) {
        cout << *i << " ";
    }
    cout << endl;
    
    
    cout << "size = " << s.size() << endl;
    
    // iterator 是一个指针, 例如 s.begin(), s.end()
    cout << "first  = " << *(s.begin()) << endl;
    cout << "last  = " << *(s.rbegin()) << endl;
    
    // 查找set中指定元素的个数
    int target = 1;
    auto count1 = s.count(target);
    cout << target << ((count1 == 1) ? " is" : " is not") << " in set" << endl;
    
    // 查找set中是否存在某个元素, 返回这个元素的iterator
    auto find = s.find(target);
    cout << target << (find != s.end() ? " is" : " is not") << " in set" << endl;
    
    
    // 清除某个元素
    s.erase(1);
    cout << "erase " << target << endl;
    
    count1 = s.count(1);
    cout << target << ((count1 == 1) ? " is" : " is not") << " in set" << endl;
    
    // 清空
    s.clear();
    cout << "size = " << s.size() << endl;
    
    
    vector<int> nums = {1,2,2,5,3,5};
    int ret = thirdMax(nums);
    cout << "ret = " << ret << endl;
}
