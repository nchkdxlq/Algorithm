//
//  BinaryTree.cpp
//  Algorithm
//
//  Created by Knox on 2019/7/13.
//  Copyright © 2019 nchkdxlq. All rights reserved.
//

#include "BinaryTree.hpp"
#include <iostream>
#include <queue>
#include <stack>

using namespace std;

namespace BinaryTree {
    
    class TreeNode {
    public:
        TreeNode *left;
        TreeNode *right;
        int val;
        
        TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    };
    
    
    class BTree {
    private:
        int m_count;
        TreeNode *m_root;
        
        void __preTraverse(TreeNode *root) {
            if (root == nullptr) {
                return;
            }
            
            cout << root->val << " ";
            __preTraverse(root->left);
            __preTraverse(root->right);
        }
        
        void __midTraverse(TreeNode *root) {
            if (root == nullptr) return;
            
            __midTraverse(root->left);
            cout << root->val << " ";
            __midTraverse(root->right);
        }
        
        void __postTraverse(TreeNode *root) {
            if (root == nullptr) return;
            
            __postTraverse(root->left);
            __postTraverse(root->right);
            cout << root->val << " ";
        }
        
        
    public:
        BTree() {
            m_root = nullptr;
            m_count = 0;
        }
        
        BTree(BTree const &tree) {
            m_root = tree.m_root;
            m_count = tree.m_count;
        }
        
        ~BTree() {
            m_root = nullptr;
            m_count = 0;
        }
        
        void insert(int val) {
            
            
            
        }
        
        
        // 广度优先遍历(层序遍历) Breadth-First-Search (BFS)
        void BFSTraverse() {
            queue<TreeNode *> q;
            if (m_root) {
                q.push(m_root);
            }
            
            while (!q.empty()) {
                auto node = q.front();
                q.pop();
                cout << node->val << " ";
                
                if (node->left) {
                    q.push(node->left);
                }
                
                if (node->right) {
                    q.push(node->right);
                }
            }
        }
        
        
        // 深度优先遍历 Depth-First-Search (DFS)
        void iterator_preTraverse() {
            stack<TreeNode *> __stack;
            TreeNode *cur = nullptr;
            
            if (m_root) __stack.push(m_root);
            
            while (!__stack.empty()) {
                
                cur = __stack.top();
                __stack.pop();
                
                cout << cur->val << " ";
                
                if (cur->right) {
                    __stack.push(cur->right);
                }
                
                if (cur->left) {
                    __stack.push(cur->left);
                }
            }
        }
        
        
        void iterator_midTraverse() {
            stack<TreeNode *> __stack;
            
            TreeNode *cur = m_root;
            
            while (cur || !__stack.empty()) {
                while (cur) {
                    __stack.push(cur);
                    cur = cur->left;
                }
                
                cur = __stack.top();
                __stack.pop();
                cout << cur->val << " ";
                
                cur = cur->right;
            }
        }
        
        
        void iterator_postTraverse() {
            stack<TreeNode *> __stack;
            
            TreeNode *cur = m_root;
            TreeNode *right = nullptr;
            
            while (cur || !__stack.empty()) {
                
                while (cur) {
                    __stack.push(cur);
                    cur = cur->left;
                }
                
                cur = __stack.top();
                __stack.pop();
                
                while (cur->right == nullptr || cur->right == right) {
                    cout << cur->val << " ";
                    
                    right = cur;
                    
                    if (__stack.empty()) {
                        return;
                    }
                    
                    cur = __stack.top();
                    __stack.pop();
                }
                
                __stack.push(cur);
                cur = cur->right;
            }
        }
        
        
        // 对任一子树，先访问根，然后遍历其左子树，最后遍历其右子树
        void preOrderTraverse() {
            __preTraverse(m_root);
        }
        
        // 对任一子树，先遍历其左子树，然后访问根，最后遍历其右子树
        void midOrderTraverse() {
            __midTraverse(m_root);
        }
        
        // 后序遍历：对任一子树，先遍历其左子树，然后遍历其右子树，最后访问根
        void postOrderTraverse() {
            __postTraverse(m_root);
        }
        
    };
    
}




using namespace BinaryTree;


void __binaryTree_entry() {
    
    
    
}
