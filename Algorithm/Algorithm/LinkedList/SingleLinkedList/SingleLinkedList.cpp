//
//  SingleLinkedList.cpp
//  Algorithm
//
//  Created by nchkdxlq on 2019/5/27.
//  Copyright © 2019 nchkdxlq. All rights reserved.
//

#include "SingleLinkedList.hpp"
#include <cstring>
#include <cassert>

using namespace std;


void singleLinkedList_entry() {
    string str = "123";
    
    LinkedList<char> list = LinkedList<char>();
    assert(list.isEmpty());
    assert(list.length() == 0);
    
    for (int i = 0; i < str.size(); i++) {
        list.append(str[i]);
    }
    assert(list.length() == str.length());
    
//    list.reverseBetween(1, 5);
    list.reverseKGroup(2);
//    list.swapPairs();
    list.description();
    return;
    
    for (int i = 0; i < str.size(); i++) {
        char data;
        bool status = list.elementAtIndex(i, &data);
        assert(status && data == str[i]);
    }
    
    list.description();
    list.reverse();
    list.description();
}

