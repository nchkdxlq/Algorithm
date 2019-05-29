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

using namespace SingleLinkedList;
using namespace std;


void singleLinkedList_entry() {
    string str = "123456789abcdefg";
    
    LinkedList<char> list = LinkedList<char>();
    assert(list.isEmpty());
    assert(list.length() == 0);
    
    for (int i = 0; i < str.size(); i++) {
        list.insert(str[i]);
    }
    assert(list.length() == str.length());
    
    for (int i = 0; i < str.size(); i++) {
        char data;
        bool status = list.elementAtIndex(i, &data);
        assert(status && data == str[i]);
    }
    
    list.description();
    list.traverse();
    list.description();
}

