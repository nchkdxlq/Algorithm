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
    string str = "12345678";
//    vector<int> test =
    LinkedList<char> list = LinkedList<char>();
    assert(list.isEmpty());
    assert(list.length() == 0);
    
    for (int i = 0; i < str.size(); i++) {
        list.append(str[i]);
    }
    assert(list.length() == str.length());
    
    list.reverseBetween(5, 8);
//    list.reverseKGroup(2);
//    list.swapPairs();
//    list.partition('3');
//    list.removeNthFromEnd(2);
    list.description();
    
    
    vector<int> iv{1, 2, 3, 4, 5, 6};
    cout << "size() = " << iv.size() << endl;
    cout << "capacity() = " << iv.capacity() << endl;
    iv.resize(10);
    cout << "size() = " << iv.size() << endl;
    cout << "capacity() = " << iv.capacity() << endl;
    iv.reserve(20);
    cout << "size() = " << iv.size() << endl;
    cout << "capacity() = " << iv.capacity() << endl;
    iv.push_back(7);
    iv.pop_back();
    
    for (int i = 0; i < str.size(); i++) {
        char data;
        bool status = list.elementAtIndex(i, &data);
        assert(status && data == str[i]);
    }
    
    list.description();
    list.reverse();
    list.description();
}

