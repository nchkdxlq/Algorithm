//
//  TreeHelper.cpp
//  LeetCode
//
//  Created by Knox on 2019/7/15.
//  Copyright © 2019 nchkdxlq. All rights reserved.
//

#include "TreeHelper.hpp"
#include <queue>
#include <stack>


namespace BTree {
    
    TreeNode* generateBSTFromVector(vector<int> &nums) {
        if (nums.empty()) return nullptr;
        
        queue<TreeNode *> q;
        
        TreeNode *root = new TreeNode(nums[0]);
        q.push(root);
        
        int i = 1;
        while (!q.empty()) {
            
            TreeNode *parent = q.front();
            q.pop();
            
            if (i < nums.size()) {
                if (nums[i] < INT_MAX) {
                    TreeNode *left = new TreeNode(nums[i]);
                    parent->left = left;
                    q.push(left);
                }
                i++;
            } else {
                break;
            }
            
            if (i < nums.size()) {
                if (nums[i] < INT_MAX) {
                    TreeNode *right = new TreeNode(nums[i]);
                    parent->right = right;
                    q.push(right);
                }
                i++;
            } else {
                break;
            }
        }
        
        return root;
    }
    
    
    
    vector<int> bst_midTraverse(TreeNode *node) {
        vector<int> nums;
        stack<TreeNode *> __stack;
        
        while (node || !__stack.empty()) {
            while (node) {
                __stack.push(node);
                node = node->left;
            }
            
            node = __stack.top();
            __stack.pop();
            
            nums.push_back(node->val);
            
            node = node->right;
        }
        
        return nums;
    }
}



