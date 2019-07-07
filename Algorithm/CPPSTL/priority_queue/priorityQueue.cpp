//
//  priorityQueue.cpp
//  STLDemo
//
//  Created by nchkdxlq on 2019/6/11.
//  Copyright © 2019 luoquan. All rights reserved.
//

#include "priorityQueue.hpp"
#include<queue>
#include <vector>
#include <iostream>

using namespace std;


/**
 https://zh.cppreference.com/w/cpp/container/priority_queue
 
 class T,
 class Container = std::vector<T>,
 class Compare = std::less<typename Container::value_type>
 > class priority_queue;
 
 ## 时间复杂度
 查找最值: queue.top(): O(1)
 插入元素: queue.push(1): O( log(n) )
 删除堆顶元素: queue.pop() O( log(n) )
 
 
 priority_queue默认情况下是大顶堆，top是priority_queue中最大的值。
 
 如果想要实现小顶堆，需要在初始化的时候指定比较函数。
 
 
 ## 常用方法
 
 访问元素
 q.top(); //访问堆顶元素
 
 容量
 q.size();
 q.empty();
 
 修改器
 q.push(1); // 插入元素，并对底层容器排序
 q.pop(); // 删除堆顶元素
 
 */

// 自定义比较函数

struct MyCompare {
    bool operator()(const int &l, int &r) const
    {
        return l > r;
    }
};


template<typename T> void print_queue(T& q) {
    while(!q.empty()) {
        std::cout << q.top() << " ";
        q.pop();
    }
    std::cout << '\n';
}

void priority_queue_entry() {
    
    vector<int> iv = {1, 8, 5, 6, 3, 4, 0, 9, 7, 2};
    
    // 默认是 大顶堆
    priority_queue<int> q1;
    for (auto i : iv) {
        q1.push(i);
    }
    cout << "size = " << q1.size() << endl;
    print_queue(q1);
    // print 9 8 7 6 5 4 3 2 1 0
    
    
    // 创建 小顶堆
    priority_queue<int, vector<int>, MyCompare> q2;
    for (auto i : iv) {
        q2.push(i);
    }
    print_queue(q2);
    // print 0 1 2 3 4 5 6 7 8 9
}






