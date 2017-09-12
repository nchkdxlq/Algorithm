//
//  SequenceST.hpp
//  Algorithm
//
//  Created by nchkdxlq on 2017/9/3.
//  Copyright © 2017年 nchkdxlq. All rights reserved.
//

#ifndef SequenceST_hpp
#define SequenceST_hpp

#include <iostream>
#include <cassert>

using namespace std;


template<typename Key, typename Value>
class SequenceST {
    
private:
    struct Node {
        Key key;
        Value value;
        Node *next;
        
        Node(Key key, Value value){
            this->key = key;
            this->value = value;
            this->next = nullptr;
        }
    };
    
    Node* head;
    int count;
    
public:
    SequenceST() {
        head = nullptr;
        count = 0;
    }
    
    ~SequenceST() {
        
        while (head != nullptr) {
            Node *node = head;
            head = head->next;
            delete node;
            count--;
        }
        
        assert(head == nullptr && count == 0);
    }
    
    int size(){
        return count;
    }
    
    bool isEmpty() {
        return count == 0;
    };
    
    void insert(Key key, Value value) {
        Node *node = head;
        while (node != nullptr) {
            if (key == node->key) {
                node->value = value;
                return;
            }
            node = node->next;
        }
        
        Node *newNode = new Node(key, value);
        newNode->next = head;
        head = newNode;
        count++;
    }
    
    bool contain(Key key) {
        
        Node *node = head;
        while (node != nullptr) {
            if (key == node->key) {
                return true;
            }
            node = node->next;
        }
        
        return false;
    }
    
    Value* search(Key key) {
        
        Node *node = head;
        while (node != nullptr) {
            if(key == node->key) {
                return &(node->value);
            }
            node = node->next;
        }
        
        return nullptr;
    }
    
    void remove(Key key) {
        
        if(key == head->key) {
            Node* delNode = head;
            head = head->next;
            delete delNode;
            count--;
            return;
        }
        
        Node *node = head;
        while (node->next != nullptr && node->next->key != key)
            node = node->next;
        
        if (node->next != nullptr) {
            Node* delNode = node->next;
            node->next = delNode->next;
            delete delNode;
            count--;
            return;
        }
    }
};

#endif /* SequenceST_hpp */
