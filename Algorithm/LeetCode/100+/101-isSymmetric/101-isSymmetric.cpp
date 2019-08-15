//
//  101-isSymmetric.cpp
//  LeetCode
//
//  Created by Knox on 2019/7/30.
//  Copyright © 2019 nchkdxlq. All rights reserved.
//

#include "101-isSymmetric.hpp"
#include "STLHelper.hpp"
#include "TreeHelper.hpp"

/*
 给定一个二叉树，检查它是否是镜像对称的。
 
 https://leetcode-cn.com/problems/symmetric-tree/
 
 */
namespace Symmetric_101 {
    
    class Solution {
    public:
        bool isSymmetric(TreeNode* root) {
//            return v2_isSymmetric(root);
            return v3_isSymmetric(root);
        }
        
    private:
        
        /*
         时间复杂度：树的每一个结点遍历一次，时间复杂度为O(n)
         空间复杂度：空间复杂度为由递归的层数决定，最好情况，树为完全二叉树时，递归的深度为O(log(n));
         最坏情况，左右两个子树退化为链表时，递归深度为n/2, 空间复杂度为O(n)
         */
        bool v1_isSymmetric(TreeNode *root) {
            if (root == nullptr) return true;
            return isMirror(root->left, root->right);
        }
        
        // 递归判断以t1、t2为根节点的两个树是否为镜像树
        bool isMirror(TreeNode *t1, TreeNode *t2) {
            if (!t1 && !t2) return true;
            
            if (!t1 || !t2) return false;
            
            if (t1->val != t2->val) return false;
            // 左对右、右对左
            return isMirror(t1->left, t2->right) && isMirror(t1->right, t2->left);
        }
        
        
        /*
         时间复杂度：O(n), 每个结点遍历一次
         空间复杂度：
         - 最好情况，左右子树退化为链表，队列中最多右4个结点，空间复杂度为O(1);
         - 最坏情况，树为完全二叉树，while循环中，一次循环从队列中移除2个结点，添加4个结点，
         所有整体效果是一次循环队列中会增加2个结点，完整循环（if判断都不满足的情况）次数由树的层数决定，
         为完全二叉树时，树的层数为log(n)，所以队列中最多的时候会保存2 * log(n)个结点，所以空间复杂度为O(log(n)),
         并不是官方给出的O(n)的空间复杂度
         
         */
        bool v2_isSymmetric(TreeNode* root) {
            if (root == nullptr) return true;
            
            queue<TreeNode *> q;
            q.push(root->left);
            q.push(root->right);
            
            while (!q.empty()) {
                TreeNode *t1 = q.front();
                q.pop();
                TreeNode *t2 = q.front();
                q.pop();
                
                if (!t1 && !t2) continue;
                
                // one of then is nil
                if (!t1 || !t2) return false;
                
                if (t1->val != t2->val) return false;
                
                q.push(t1->left);
                q.push(t2->right);
                
                q.push(t1->right);
                q.push(t2->left);
            }
            
            return true;
        }
        
        
        /*
         使用栈用迭代方式完成判断
         时间复杂度：O(n)， 每个结点需要遍历一次
         空间复杂度：最好情况，当树的左右子树退还为链表时，栈中最多的时候有4个结点，空间复杂度O(1)；
                   最坏情况，当树为完全二叉树时，栈中最多有
         
         */
        bool v3_isSymmetric(TreeNode* root) {
            if (root == nullptr) return true;
            
            stack<TreeNode *> s;
            s.push(root->left);
            s.push(root->right);
            
            while (!s.empty()) {
                TreeNode *node1 = s.top();
                s.pop();
                TreeNode *node2 = s.top();
                s.pop();
                
                if (!node1 && !node2) continue;
                
                if (!node1 || !node2) return false;
                
                if (node1->val != node2->val) return false;
                
                s.push(node1->left);
                s.push(node2->right);
                
                s.push(node1->right);
                s.push(node2->left);
            }
            
            return true;
        }
    };
    
    
}



void __101_entry() {
    vector<int> nums = {1,2,2,3,4,4,3}; // true
    nums = {1, INT_MAX, 2}; // false
    nums = {9,-42,-42,INT_MAX,76,76,INT_MAX,INT_MAX,13,INT_MAX,13}; // false
    
    TreeNode *root = create_binaryTree(nums);
    bool ret = Symmetric_101::Solution().isSymmetric(root);
    cout << "==== 101-isSymmetric ====" << endl;
    
    cout << (ret ? "true" : "false") << endl;
}
