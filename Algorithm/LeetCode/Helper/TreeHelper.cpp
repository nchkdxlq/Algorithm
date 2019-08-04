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
    
    TreeNode* create_binaryTree(vector<int> &nums) {
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
    
#pragma mark - 前序遍历
   
    void recursive_preorder_traverse_helper(TreeNode *node, vector<int> &result) {
        if (node == nullptr) return;
        
        result.push_back(node->val);
        recursive_preorder_traverse_helper(node->left, result);
        recursive_preorder_traverse_helper(node->right, result);
    }
    // 前序遍历-递归方式
    vector<int> recursive_preorder_traverse(TreeNode *root) {
        vector<int> ret;
        recursive_preorder_traverse_helper(root, ret);
        return ret;
    }
    
    // 前序遍历-迭代方式
    vector<int> iterator_preorder_traverse(TreeNode *root) {
        vector<int> ret;
        stack<TreeNode *> path;
        
        if (root) path.push(root);
        
        while (!path.empty()) {
            TreeNode *node = path.top();
            path.pop();
            
            ret.push_back(node->val);
            
            // 先push右结点 再 左结点
            if (node->right) path.push(node->right);
            if (node->left) path.push(node->left);
        }
        
        return ret;
    }

#pragma mark - 中序遍历
    
    void recursive_inorder_traverse_helper(TreeNode *node, vector<int> &result) {
        if (node == nullptr) return;
        
        recursive_inorder_traverse_helper(node->left, result);
        result.push_back(node->val);
        recursive_inorder_traverse_helper(node->right, result);
    }
    // 前序遍历-递归方式
    vector<int> recursive_inorder_traverse(TreeNode *node) {
        vector<int> ret;
        recursive_inorder_traverse_helper(node, ret);
        return ret;
    }
    
    // 中序遍历-迭代方式
    vector<int> iterator_inorder_traverse(TreeNode *node) {
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
    
    vector<int> preorderTraverse(TreeNode *root) {
        return recursive_preorder_traverse(root);
//        return iterator_preorder_traverse(root);
    }
    
    vector<int> inorderTraverse(TreeNode *root) {
        return recursive_inorder_traverse(root);
//        return iterator_inorder_traverse(root);
    }
    
    vector<int> postorderTraverse(TreeNode *root) {
        return {};
    }
    
    vector<int> levelTraverse(TreeNode *root) {
        return {};
    }
    


}




class Solution {
public:
    vector<int> rightSideView(TreeNode* root) {
        vector<int>res;
        TreeNode *cur;
        queue<pair<TreeNode *,int> >q;
        if(root) q.push(make_pair(root,0));
        while(!q.empty()) {
            cur=q.front().first;
            int depth=q.front().second;
            q.pop();
            
            if(res.size()==depth)
                res.push_back(cur->val);
            else res[depth]=cur->val;
            if(cur->left)
                q.push(make_pair(cur->left,depth+1));
            if(cur->right)
                q.push(make_pair(cur->right,depth+1));
            
        }
        return res;
    }
};
