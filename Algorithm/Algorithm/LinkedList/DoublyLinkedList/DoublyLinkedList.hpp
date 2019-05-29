//
//  DoublyLinkedList.hpp
//  Algorithm
//
//  Created by nchkdxlq on 2019/5/29.
//  Copyright © 2019 nchkdxlq. All rights reserved.
//

#ifndef DoublyLinkedList_hpp
#define DoublyLinkedList_hpp

#include <stdio.h>


void doublyLinkedList_entry();



template <typename T>
class DoublyLinkedList {

    class Node {
    public:
        T data;
        Node *prev;
        Node *next;
        
        Node(T data) {
            this->data = data;
            prev = nullptr;
            next = nullptr;
        }
    };

private:
    Node *m_head;

public:
    
    DoublyLinkedList() {
        m_head = nullptr;
    }
    
    ~DoublyLinkedList() {
        m_head = nullptr;
    }
    
    
    bool intsert(T element) {
        Node *newNode = new Node(element);
        
        return true;
    }
    
};



#endif /* DoublyLinkedList_hpp */
