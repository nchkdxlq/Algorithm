//
//  SingleLinkedList.hpp
//  Algorithm
//
//  Created by nchkdxlq on 2019/5/27.
//  Copyright © 2019 nchkdxlq. All rights reserved.
//

#ifndef SingleLinkedList_hpp
#define SingleLinkedList_hpp

#include <stdio.h>


namespace SingleLinkedList {
    
    template <typename T>
    class Node {
    public:
        T data;
        Node *next;
        
        Node(T data) {
            this->data = data;
            next = nullptr;
        }
    };

    template<typename T>
    class LinkedList {
        
    private:
        Node<T> *m_head;
        
        
    public:
        
        LinkedList() {
            m_head = nullptr;
        }
        
        ~LinkedList() {
            Node<T> *cur = m_head;
            while (cur) {
                Node<T> *tmp = cur->next;
                delete cur;
                cur = tmp->next;
            }
            m_head = nullptr;
        }
        
        
        bool isEmpty() {
            return m_head == nullptr;
        }
        
        int length() {
            int length = 0;
            Node<T> *cur = m_head;
            while (cur) {
                cur = cur->next;
            }
            return length;
        }
        
        bool insert(T data) {
            Node<T> *newNode = Node<T>(data);
            if (m_head == nullptr) {
                m_head = newNode;
            } else {
                Node<T> *cur = m_head;
                while (cur->next) {
                    cur = cur->next;
                }
                cur->next = newNode;
            }
            return true;
        }
        
        // index从0开始
        bool insertAtIndex(T data, int index) {
            if (index < 0) return false;
            
            // 处理插入index == 0 的情况
            if (index == 0) {
                Node<T> *newNode =  Node<T>(data);
                newNode->next = m_head;
                m_head = newNode;
                return true;
            }
            
            // 在index插入结点需要找到index-1位置的结点
            Node<T> *cur = m_head;
            int pos = -1; // 表示cur结点的index
            while (cur) {
                pos++;
                if (pos == index - 1) {
                    break;
                }
                cur = cur->next;
            }
            
            if (pos == index - 1) {
                Node<T> *newNode =  Node<T>(data);
                newNode->next = cur->next;
                cur->next = newNode;
                return true;
            } else {
                return false;
            }
        }
        
        
        bool deleteElement(T &element) {
            
            return true;
        }
        
        // index从0开始
        bool deleteElementAtIndex(int index, T &element) {
            return true;
        }
        
        void traverse() {
            
        }
    };
    
}






#endif /* SingleLinkedList_hpp */
