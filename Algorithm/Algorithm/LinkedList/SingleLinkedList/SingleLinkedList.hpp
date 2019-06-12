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
#include <vector>
#include "Utils.h"


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
    int m_length;
    
    
public:
    
    LinkedList() {
        m_head = nullptr;
        m_length = 0;
    }
    
    ~LinkedList() {
        destroy();
    }
    
    
    bool isEmpty() {
        return m_head == nullptr;
    }
    
    int length() {
        return m_length;
    }
    
    bool append(T data) {
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
        m_length++;
        return true;
    }
    
    // index从0开始
    bool insertAtIndex(T data, int index) {
        if (index < 0 || index > m_length) return false;
        
        // 处理插入index == 0 的情况
        if (index == 0) {
            Node *newNode = new Node(data);
            newNode->next = m_head;
            m_head = newNode;
            m_length++;
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
                m_length++;
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
            PointSafeAssign(element, m_head->data);
            delete m_head;
            m_head = nullptr;
            m_length--;
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
        m_length--;
        delete cur;
        
        return true;
    }
    
    // index从0开始
    bool deleteElementAtIndex(int index, T *element) {
        // 非法输入
        if (index < 0 || index > m_length-1) return false;
        
        // 删除第0个节点
        if (index == 0) {
            Node *next = m_head->next;
            PointSafeAssign(element, m_head->data);
            delete m_head;
            m_head = next;
            m_length--;
            return true;
        }
        
        // 找到第index的前一个结点
        Node *cur = m_head;
        int pos = -1; // pos为cur结点的下标
        
        while (cur) {
            pos++;
            if (pos == index - 1 && cur->next) { // 第index-1个节点
                Node *target = cur->next;
                PointSafeAssign(element, target->data);
                cur->next = target->next;
                delete target;
                m_length--;
                return true;
            }
            cur = cur->next;
        }
        
        return false;
    }
    
    
    bool firstElement(T *element) {
        if (m_head == nullptr) return false;
        PointSafeAssign(element, m_head->data);
        return true;
    }
    
    
    bool lastElement(T *element) {
        if (m_head == nullptr) return false;
        
        Node *cur = m_head;
        while (cur->next) {
            cur = cur->next;
        }
        PointSafeAssign(element, cur->data);
        
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
            PointSafeAssign(element, target->data);
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
            cur = tmp;
        }
        m_head = nullptr;
        m_length = 0;
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
    
    void reverseBetween(int m, int n) {
        
        __reverseBetween_v3(m, n);
        
    }
    
    
    void __reverseBetween_v3(int m, int n) {
        if (m == n) return;
        
        Node dummy = Node(-1);
        Node *tail = &dummy;
        
        Node *cur = m_head;
        int pos = 1;
        
        while (pos < m) {
            tail->next = cur;
            tail = cur;
            cur = cur->next;
            pos++;
        }
        // while循环后，pos == m, cur在m的位置
        
        Node *tmpHead = nullptr;
        Node *tmpTail = cur; // 第m个节点翻转后会变成子链表的最后一个节点，先记录下来
        while (pos <= n) {
            Node *next = cur->next;
            cur->next = tmpHead;
            tmpHead = cur;
            cur = next;
            pos++;
        }
        // while循环后，pos == n+1, cur在n+1的位置
        
        tail->next = tmpHead;
        tail = tmpTail;
        
        
        // n+1以及后面的结点
        while (cur) {
            tail->next = cur;
            tail = cur;
            cur = cur->next;
        }
        
        m_head = dummy.next;
    }
    
    void __reverseBetween_v2(int m, int n) {
        if (m == n) return;
        
        Node *m_node = nullptr;
        Node *m_prev = nullptr;
        Node *cur = m_head;
        int pos = 1;
        while (pos < m) {
            m_prev = cur;
            cur = cur->next;
            pos++;
        }
        m_node = cur; // 1. 找到第m的结点
        
        // 2. 把 m~n 结点翻转
        Node *tmpHead = cur;
        cur = cur->next;
        pos++;
        while (pos <= n) {
            Node *tmpNext = cur->next;
            cur->next = tmpHead;
            tmpHead = cur;
            cur = tmpNext;
            pos++;
        }
        
        // 4. 翻转后，下标m结点到了第n个位置，让新n的结点指向n+1结点
        m_node->next = cur;
        
        // 5. m-1指向新的m结点
        if (m_prev) {
            m_prev->next = tmpHead;
        } else {
            m_head = tmpHead;
        }
    }
    
    void __reverseBetween_v1(int m, int n) {
        Node *cur = m_head;
        Node *prev = nullptr;
        Node *node_m = nullptr;
        Node *m_prev = nullptr;
        int pos = 0;
        while (cur) {
            pos++;
            if (pos <= m) {
                if (pos < m) {
                    m_prev = cur;
                } else {
                    node_m = cur;
                }
                prev = cur;
                cur = cur->next;
            } else if (pos > m && pos <= n) {
                Node *tmpNext = cur->next;
                
                cur->next = node_m;
                if (m == 1) {
                    m_head = cur;
                } else {
                    m_prev->next = cur;
                }
                node_m = cur;
                
//                node_m->next = tmpNext;
//                prev->next = node_m;
                prev->next =tmpNext;
                
                cur = tmpNext;
                continue;
            } else {
                break;
            }
        }
        
    }
    
    void reverseKGroup(int k) {
        m_head = __reverseKGroup_v2(m_head, k);
    }
    
    void __reverseKGroup_v1(int k) {
        if (m_head == nullptr || k < 2) return;
        
        Node *newHead = nullptr; // 新链表头指针
        Node *newTail = nullptr; // 新链表尾指针
        Node *cur = m_head;
        int count = 0;
        
        Node *tmpHead = nullptr;
        Node *tmpTail = nullptr;
        
        while (cur) {
            Node *tmpNext = cur->next;
            cur->next = tmpHead;
            tmpHead = cur;
            count++;
            if (tmpTail == nullptr) tmpTail = cur;
            
            if (count == k) {
                if (newTail == nullptr) {
                    newHead = tmpHead;
                } else {
                    newTail->next = tmpHead;
                }
                newTail = tmpTail;
                
                tmpHead = nullptr;
                tmpTail = nullptr;
                count = 0;
            }
            cur = tmpNext;
        }
        
        if (tmpHead) { // 说明最后一组的结点书少于k, 不需要翻转，把它翻转回来
            tmpTail = tmpHead;
            cur = tmpHead->next;
            while (cur) {
                Node *next = cur->next;
                cur->next = tmpHead;
                tmpHead = cur;
                cur = next;
            }
            
            if (newTail) {
                newTail->next = tmpHead;
            } else {
                newHead = tmpHead;
            }
            
            newTail = tmpTail;
        }
        
        if (newTail) newTail->next = nullptr;
        
        
        m_head = newHead;
    }
    
    
    // 递归解法
    Node* __reverseKGroup_v2(Node *head, int k) {
        if (head == nullptr || head->next == nullptr || k < 2) {
            return head;
        }
        
        Node *newHead = nullptr;
        int count = 0;
        Node *cur = head;
        Node *next = nullptr;
        while (cur) {
            next = cur->next;
            cur->next = newHead;
            newHead = cur;
            
            count++;
            if (count == k) {
                break;
            } else {
                cur = next;
            }
        }
        
        if (count < k) {
            Node *tmpHead = nullptr;
            cur = newHead;
            while (cur) {
                Node *next = cur->next;
                cur->next = tmpHead;
                tmpHead = cur;
                cur = next;
            }
            return tmpHead;
        } else {
            head->next = __reverseKGroup_v2(next, k);
            return newHead;
        }
    }
    
    
    
    void swapPairs() {
        __swapPairs_v2();
    }
    
    void __swapPairs_v2() {
        if (length() < 2) return;
        
        Node *dummy = new Node(-1);
        Node *pre = dummy;
        Node *cur = m_head;
        
        while (cur) {
            Node *next = cur->next;
            if (next) {
                Node *nextNext = next->next;
                pre->next = next;
                pre = next;
                next = nextNext;
            }
            pre->next = cur;
            pre = cur;
            
            cur = next;
        }
        pre->next = nullptr;
        
        m_head = dummy->next;
        delete dummy;
    }
    
    void __swapPairs_v1() {
        if (length() < 2) return;
        
        Node *newHead = nullptr;
        Node *tail = nullptr;
        Node *cur = m_head;
        
        while (cur) {
            Node *next = cur->next;
            Node *tmp = cur; // 临时存储cur和next放在前面的结点，统一后面代码操作
            if (next) {
                tmp = next;
                Node *nextNext = next->next;
                next->next = cur;
                next = nextNext;
            }
            
            if (newHead) {
                tail->next = tmp;
            } else {
                newHead = tmp;
            }
            tail = cur;
            
            cur = next;
        }
        
        if (tail) tail->next = nullptr;
        
        m_head = newHead;
    }
    
    void partition(T x) {
     
        Node *lessDummy = new Node(-1);
        Node *lessPre = lessDummy;
        Node *dummy = new Node(-1);
        Node *pre = dummy;
        

        Node *cur = m_head;
        while (cur) {
            if (cur->data < x) {
                lessPre->next = cur;
                lessPre = cur;
            } else {
                pre->next = cur;
                pre = cur;
            }
            cur = cur->next;
        }
        
        lessPre->next = nullptr;
        pre->next = nullptr;
        
        if (lessDummy->next) {
            lessPre->next = dummy->next;
            m_head = lessDummy->next;
        } else {
            m_head = dummy->next;
        }
        
        delete lessDummy;
        delete dummy;
    }
    
    void removeNthFromEnd(int n) {
        __removeNthFromEnd_v2(n);
    }
    
    void __removeNthFromEnd_v2(int n) {
        if (m_head == nullptr) return;
        
        int count = 0;
        vector<Node *>ptrV;
        Node *cur = m_head;
        while (cur) {
            count++;
            ptrV.push_back(cur);
            cur = cur->next;
        }
        
        int targetIndex = count - n;
        if (targetIndex == 0) {
            Node *next = m_head->next;
            delete m_head;
            m_head = next;
        } else {
            Node *pre = ptrV[targetIndex-1];
            Node *target = pre->next;
            Node *next = target->next;
            delete target;
            pre->next = next;
        }
        
        
    }
    
    void __removeNthFromEnd_v1(int n) {
        if (m_head == nullptr) return;
        
        Node *slow = nullptr;
        Node *fast = nullptr;
        int slowIndex = -1;
        int fastIndex = -1;
        int count = 0;
        
        Node *cur = m_head;
        
        while (cur) {
            Node *next = cur->next;
            if (next) {
                Node *nextNext = next->next;
                if (slow) {
                    slow = slow->next;
                } else {
                    slow = cur;
                }
                slowIndex++;
                
                fast = next;
                fastIndex += 2;
                
                count += 2;
                cur = nextNext;
            } else {
                count += 1;
                cur = next;
            }
        }
        
        int targetIndex = count - n;
        if (targetIndex == 0) { // 删除的第0个结点
            Node *next = m_head->next;
            delete m_head;
            m_head = next;
        }
        
        Node *pre = nullptr;
        int index = -1;
        if (targetIndex > slowIndex) {
            pre = slow;
            index = slowIndex;
        } else {
            pre = m_head;
            index = 0;
        }
        
        cur = pre->next;
        while (cur) {
            index++;
            if (index == targetIndex) {
                Node *next = cur->next;
                delete cur;
                pre->next = next;
                break;
            }
            pre = cur;
            cur = cur->next;
        }
    }
    
};




#endif /* SingleLinkedList_hpp */
