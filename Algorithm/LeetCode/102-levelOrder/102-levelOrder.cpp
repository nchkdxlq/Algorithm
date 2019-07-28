//
//  102-levelOrder.cpp
//  LeetCode
//
//  Created by Knox on 2019/7/28.
//  Copyright © 2019 nchkdxlq. All rights reserved.
//

#include "102-levelOrder.hpp"
#include "TreeHelper.hpp"
#include "stlheaders.h"


/*
 给定一个二叉树，返回其按层次遍历的节点值。 （即逐层地，从左到右访问所有节点）。
 
 
 https://leetcode-cn.com/problems/binary-tree-level-order-traversal/
 */

namespace levelOrder_102 {
    
    class Solution {
        
    public:
        vector<vector<int>> levelOrder(TreeNode* root) {
//            return v1_levelOrder(root);
            return v2_levelOrder(root);
        }
        
    private:
        /*
         执行用时 :12 ms, 在所有 C++ 提交中击败了68.14%的用户
         内存消耗 :13.8 MB, 在所有 C++ 提交中击败了59.89%的用户
         */
        vector<vector<int>> v1_levelOrder(TreeNode* root) {
            if (root == nullptr) {
                return {};
            }
            vector<vector<int>> ret;
            queue<TreeNode *> q;
            
            q.push(nullptr);
            q.push(root);
            
            vector<int> curLevel;
            while (!q.empty()) {
                TreeNode *node = q.front();
                if (node == nullptr) { // 新的一层
                    q.pop();
                    if (q.empty()) {
                        break;
                    }
                    
                    // 后面push进队列的结点是新的一层，所以需要先push一个空指针进队列
                    q.push(nullptr);
                    
                    node = q.front();
                    ret.push_back({});
                }
                
                auto &curLevel = ret.back();
                curLevel.push_back(node->val);
                
                q.pop();
                
                if (node->left) {
                    q.push(node->left);
                }
                
                if (node->right) {
                    q.push(node->right);
                }
            }
            
            return ret;
        }

        
        /*
         执行用时 :8 ms, 在所有 C++ 提交中击败了87.78%的用户
         内存消耗 :13.7 MB, 在所有 C++ 提交中击败了75.90%的用户
         */
        vector<vector<int>> v1_1_levelOrder(TreeNode* root) {
            queue<TreeNode *> q;
            vector<vector<int>> ret;
            if (root) q.push(root);
            
            while (!q.empty()) {
                auto size = q.size();
                vector<int> tmp;
                
                for (int i = 0; i < size; i++) {
                    TreeNode *node = q.front();
                    tmp.push_back(node->val);
                    q.pop();
                    
                    if (node->left) q.push(node->left);
                    if (node->right) q.push(node->right);
                }
                
                ret.push_back(tmp);
            }
            
            return ret;
        }
        
        
        /*
         执行用时 :4 ms, 在所有 C++ 提交中击败了97.70%的用户
         内存消耗 :14.7 MB, 在所有 C++ 提交中击败了14.54%的用户
         */
        vector<vector<int>> v2_levelOrder(TreeNode* root) {
            vector<vector<int>> ret;
            helper(root, 0, ret);
            return ret;
        }
        
        // 本质就是深度优先遍历，额外加上层数
        void helper(TreeNode *node, int level, vector<vector<int>> &result) {
            if (node == nullptr) return;
            
            if (result.size() == level) {
                result.push_back({});
            }
            
            result[level].push_back(node->val);
            
            if (node->left) {
                helper(node->left, level+1, result);
            }
            
            if (node->right) {
                helper(node->right, level+1, result);
            }
        }
        
    };
    
}





void __102_entry() {
    
    vector<int> nums = {3, 9, 20, INT_MAX, INT_MAX, 15, 7};
    TreeNode *root = create_binaryTree(nums);
    
    vector<vector<int>> ret = levelOrder_102::Solution().levelOrder(root);
    
    cout << "==== levelOrder ====" << endl;
    
    for (auto &level : ret) {
        cout << "[ ";
        for (auto item : level) {
            cout << item << " ";
        }
        cout << "]" << endl;
    }
}
