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
    
    cout << ">>>>>>>>>>>>> DoublyLinkedList begin <<<<<<<<<<<<<<<<" << endl;
    cout << endl;
    
    string str = "123456789abcdefg";
    
    DoublyLinkedList<char> linkedList = DoublyLinkedList<char>();
    assert(linkedList.isEmpty());
    
    for (int i = 0; i < str.length(); i++) {
        linkedList.append(str[i]);
    }
    
    assert(linkedList.length() == str.length());
    linkedList.description();
    
    char data = 0;
    bool ret = linkedList.lastElement(&data);
    assert(ret);
    assert(data == str[str.length()-1]);
    
    data = 0;
    ret = linkedList.firstElement(&data);
    assert(ret);
    assert(data == str[0]);
    
    assert(linkedList.elementAtIndex(nullptr, 100) == false);
    
    for (int i = 0; i < str.length(); i++) {
        char data;
        bool ret = linkedList.elementAtIndex(&data, i);
        assert(ret);
        assert(data == str[i]);
    }
    
    
    for (int i = (int)(str.length())-1; i >= 0 ; i--) {
        char data;
        bool ret = linkedList.deleteLast(&data);
        assert(ret);
        assert(data == str[i]);
    }
    assert(linkedList.isEmpty());
    
    linkedList.description();
    
    cout << endl;
    cout << ">>>>>>>>>>>>> DoublyLinkedList end <<<<<<<<<<<<<<<<" << endl;
}
