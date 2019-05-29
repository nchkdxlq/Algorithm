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
#include <iostream>

void singleLinkedList_entry();

using namespace std;

template<typename T>
class LinkedList {
    
    class Node {
    public:
        T data;
        Node *next;
        
        Node(T data) {
            this->data = data;
            next = nullptr;
        }
    };
    
private:
    Node *m_head;
    
    
public:
    
    LinkedList() {
        m_head = nullptr;
    }
    
    ~LinkedList() {
        destroy();
    }
    
    
    bool isEmpty() {
        return m_head == nullptr;
    }
    
    int length() {
        int length = 0;
        Node *cur = m_head;
        while (cur) {
            length++;
            cur = cur->next;
        }
        return length;
    }
    
    bool insert(T data) {
        Node *newNode = new Node(data);
        if (m_head == nullptr) {
            m_head = newNode;
        } else {
            Node *cur = m_head;
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
            Node *newNode = new Node(data);
            newNode->next = m_head;
            m_head = newNode;
            return true;
        }
        
        // 在index插入结点需要找到index-1位置的结点
        Node *cur = m_head;
        int pos = -1; // 表示cur结点的下标
        while (cur) {
            pos++;
            if (pos == index - 1) {
                Node *newNode =  Node(data);
                newNode->next = cur->next;
                cur->next = newNode;
                return true;
            }
            cur = cur->next;
        }
        
        return false;
    }
    
    
    bool deleteElement(T *element) {
        // 空链表
        if (m_head == nullptr) return false;
        
        // 只有一个结点
        if (m_head->next == nullptr) {
            *element = m_head->data;
            delete m_head;
            m_head = nullptr;
            return true;
        }
        
        // 大于等于两个结点的情况
        Node *cur = m_head;
        Node *prev = nullptr; // 为cur结点的前一个结点
        
        while (cur->next) {
            prev = cur;
            cur = cur->next;
        }
        
        prev->next = nullptr;
        *element = cur->data;
        delete cur;
        
        return true;
    }
    
    // index从0开始
    bool deleteElementAtIndex(int index, T *element) {
        // 非法输入
        if (index < 0 || m_head == nullptr) return false;
        
        // 删除第0个节点
        if (index == 0) {
            Node *next = m_head->next;
            *element = m_head->data;
            delete m_head;
            m_head = next;
            return true;
        }
        
        // 找到第index的前一个结点
        Node *cur = m_head;
        int pos = -1; // pos为cur结点的下标
        
        while (cur) {
            pos++;
            if (pos == index - 1 && cur->next) { // 第index-1个节点
                Node *target = cur->next;
                *element = target->data;
                cur->next = target->next;
                delete target;
                return true;
            }
            cur = cur->next;
        }
        
        return false;
    }
    
    
    bool firstElement(T *element) {
        if (m_head == nullptr) return false;
        *element = m_head->data;
        return true;
    }
    
    
    bool lastElement(T *element) {
        if (m_head == nullptr) return false;
        
        Node *cur = m_head;
        while (cur->next) {
            cur = cur->next;
        }
        *element = cur->data;
        
        return true;
    }
    
    bool elementAtIndex(int index, T *element) {
        if (index < 0 || m_head == nullptr) return false;
        
        int pos = -1;
        Node *cur = m_head;
        Node *target = nullptr;
        while (cur) {
            pos++;
            if (index == pos) {
                target = cur;
                break;
            }
            cur = cur->next;
        }
        
        if (target) {
            *element = target->data;
            return true;
        }  else {
            return false;
        }
    }
    
    /**
     翻转链表
     */
    void reverse() {
        // 没有结点或已有一个结点，不需要翻转，特殊处理
        if (m_head == nullptr || m_head->next == nullptr) return;
        
        Node *newHead = nullptr;
        Node *cur = m_head;
        
        while (cur) {
            // 1. 后面需要修改cur->next, 所以先用next保存cur->next
            Node *next = cur->next;
            // 2. 把当前结点设置为新链表的头结点
            cur->next = newHead;
            newHead = cur;
            // 3. 把下一个结点设置为当前结点
            cur = next;
        }
        
        m_head = newHead;
    }
    
    
    /**
     清空链表
     */
    void destroy() {
        Node *cur = m_head;
        while (cur) {
            Node *tmp = cur->next;
            delete cur;
            cur = tmp->next;
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
                cout << ", ";
            } else {
                cout << endl;
            }
            cur = cur->next;
        }
    }
    
};




#endif /* SingleLinkedList_hpp */
