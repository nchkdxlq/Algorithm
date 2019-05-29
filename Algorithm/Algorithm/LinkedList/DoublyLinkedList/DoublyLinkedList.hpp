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
#include <iostream>

using namespace std;

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
        destroy();
    }
    
    bool isEmpty() {
        return m_head == nullptr;
    }
    
    int length() {
        int length = 0;
        Node *cur = m_head;
        while (cur) {
            cur = cur->next;
            length++;
        }
        return length;
    }
    
    
    bool insert(T element) {
        Node *newNode = new Node(element);
        
        if (m_head == nullptr) {
            m_head = newNode;
            return true;
        }
        
        // 找到链表的最后一个结点
        Node *cur = m_head;
        while (cur->next) {
            cur = cur->next;
        }
        
        cur->next = newNode;
        newNode->prev = cur;
        
        return true;
    }
    
    
    bool insertAtIndex(T element, int index) {
        if (index < 0) return false;
        
        if (index == 0) {
            Node *newNode = new Node(element);
            newNode->next = m_head;
            if (m_head) {
                m_head->prev = newNode;
            }
            m_head = newNode;
            return true;
        }
        
        if (m_head == nullptr) return false;
        
        Node *cur = m_head;
        int pos = -1;
        while (cur) {
            pos++;
            if (pos == index - 1) { // 找到下标第index-1的结点
                Node *next = cur->next;
                Node *newNode = new Node(element);
                newNode->prev = cur;
                newNode->next = next;
                cur->next = newNode;
                return true;
            }
        }
        
        return false;
    }
    
    bool deleteLast(T *element) {
        if (m_head == nullptr) return false;
        
        if (m_head->next == nullptr) { // 只有一个结点
            *element = m_head->data;
            delete m_head;
            m_head = nullptr;
            return true;
        }
        
        Node *cur = m_head;
        while (cur->next) {
            cur = cur->next;
        }
        *element = cur->data;
        Node *prev = cur->prev;
        prev->next = nullptr;
        delete cur;

        return true;
    }
    
    bool deleteAtIndex(T *element, int index) {
        if (index < 0) return false;
        
        if (index == 0) {
            if (m_head == nullptr) return false;
            Node *next = m_head->next;
            *element = m_head->data;
            delete m_head;
            m_head = next;
            return true;
        }
        
        Node *cur = m_head;
        int pos = -1;
        while (cur) {
            pos++;
            if (pos == index) {
                Node *prev = cur->prev;
                Node *next = cur->next;
                *element = cur->data;
                delete cur;
                prev->next = next;
                if (next) { // next结点可能没有值
                    next->prev = prev;
                }
                return true;
            }
            cur = cur->next;
        }
        
        return false;
    }
    
    
    bool elementAtIndex(T *element, int index) {
        if (index < 0) return false;
        
        
        return false;
    }
    
    bool firstElement(T *element) {
        return false;
    }
    
    bool lastElement(T *element) {
        return false;
    }
    
    
    void destroy() {
        Node *cur = m_head;
        while (cur) {
            Node *next = cur->next;
            delete cur;
            cur = next;
        }
        m_head = nullptr;
    }
    
    void description() {
        if (m_head == nullptr) {
            cout << "LinkedList is empty." << endl;
            return;
        }
        Node *cur = m_head;
        while (cur) {
            cout << cur->data;
            if (cur->next) {
                cout << ",  ";
            } else {
                cout << endl;
            }
            cur = cur->next;
        }
    }
    
    
};



#endif /* DoublyLinkedList_hpp */
