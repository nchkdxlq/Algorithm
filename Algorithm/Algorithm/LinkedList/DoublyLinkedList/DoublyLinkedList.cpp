//
//  DoublyLinkedList.cpp
//  Algorithm
//
//  Created by nchkdxlq on 2019/5/29.
//  Copyright © 2019 nchkdxlq. All rights reserved.
//

#include "DoublyLinkedList.hpp"
#include <cstring>
#include <cassert>

void doublyLinkedList_entry() {
    
    string str = "123456789abcdefg";
    
    DoublyLinkedList<char> linkedList = DoublyLinkedList<char>();
    assert(linkedList.isEmpty());
    
    for (int i = 0; i < str.length(); i++) {
        linkedList.insert(str[i]);
    }
    
    assert(linkedList.length() == str.length());
    linkedList.description();
    
    for (int i = (int)(str.length())-1; i >= 0 ; i--) {
        char data;
        bool ret = linkedList.deleteLast(&data);
        assert(ret);
        assert(data == str[i]);
    }
    assert(linkedList.isEmpty());
    
    linkedList.description();
}
