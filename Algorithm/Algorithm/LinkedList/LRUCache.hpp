//
//  LRUCache.hpp
//  Algorithm
//
//  Created by nchkdxlq on 2019/5/26.
//  Copyright © 2019 nchkdxlq. All rights reserved.
//

#ifndef LRUCache_hpp
#define LRUCache_hpp

#include <stdio.h>



void lruCache_entry();




template<typename Key, typename Value>
class Node {
private:
    Key m_key;
    Value m_data;
    
public:
    Node *next;
    
    Node(Key key, Value data) {
        m_key = key;
        m_data = data;
        next = nullptr;
    }
    
    Key key() {
        return m_key;
    }
    
    Value data() {
        return m_data;
    }
};



template<typename Key, typename Value>
class URLCache {
private:
    int m_capacity;
    int m_used;
    Node<Key, Value> *m_linkedList;
    
    void removeTailNode() {
        // 没有结点
        if (m_linkedList == nullptr) return;
        
        // 只有一个结点
        if (m_linkedList->next == nullptr) {
            delete m_linkedList;
            m_linkedList = nullptr;
            m_used--;
            return;
        }
        
        Node<Key, Value> *prev = m_linkedList;
        Node<Key, Value> *cur = prev->next;
        // next 为空时e为链表的尾结点
        while (cur->next) {
            prev = cur;
            cur = cur->next;
        }
        prev->next = nullptr;
        delete cur;
        m_used--;
    }
    
public:
    URLCache(int capacity) {
        m_capacity = capacity;
        m_used = 0;
        m_linkedList = nullptr;
    }
    
    int capacity() {
        return m_capacity;
    }
    
    int used() {
        return m_used;
    }
    
    void cacheDataWithKey(Key key, Value data) {
        Node<Key, Value> *node = new Node<Key, Value>(key, data);
        // 当缓存满时，删除最后一个结点
        if (m_used == m_capacity) {
            removeTailNode();
        }
        // 新缓存的元素放在第一个结点
        node->next = m_linkedList;
        m_linkedList = node;
        m_used++;
    }
    
    void removeDataForKey(Key key) {
        Node<Key, Value> *prev = nullptr;
        Node<Key, Value> *cur = m_linkedList;
        while (cur) {
            if (cur->key() == key) {
                if (prev == nullptr) { // 头结点命中
                    m_linkedList = cur->next;
                } else {
                    prev->next = cur->next;
                }
                m_used--;
                delete cur;
                break;
            }
            prev = cur;
            cur = cur->next;
        }
    }
    
    bool dataForKey(Key key, Value *data) {
        Node<Key, Value> *pre = nullptr;
        Node<Key, Value> *cur = m_linkedList;
        Node<Key, Value> *target = nullptr;
        
        while (cur) {
            if (cur->key() == key) {
                target = cur;
                break;
            }
            pre = cur;
            cur = cur->next;
        }
        
        if (target == nullptr) { // 没有命中
            return false;
        } else {
            // 把target放到第一个节点
            if (pre) {
                // 1.前驱结点next指向target的下一个结点
                pre->next = target->next;
                // 2. target的next指向第一个节点
                target->next = m_linkedList;
                // 3. 头指针指向target
                m_linkedList = target;
            } else {
                // 命中的第一个结点，不需要做任何操作
            }
            *data = target->data();
            return true;
        }
    }
    
};







#endif /* LRUCache_hpp */
