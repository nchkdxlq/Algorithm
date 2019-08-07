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
#include <unordered_set>

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
    
#pragma mark - 后序遍历
    
    // 递归实现
    void recursive_postorder_traverse_helper(TreeNode *node, vector<int> &result) {
        if (node == nullptr) return;
        
        recursive_postorder_traverse_helper(node->left, result);
        recursive_postorder_traverse_helper(node->right, result);
        result.push_back(node->val);
    }
    vector<int> recursive_postorder_traverse(TreeNode *root) {
        vector<int> result;
        recursive_postorder_traverse_helper(root, result);
        return result;
    }
    
    // 迭代实现
    vector<int> iterator_postorder_traverse(TreeNode *root) {
        vector<int> result;
        stack<TreeNode *> path;
        unordered_set<TreeNode *> mark; // 保存已经访问过的结点
        
        if (root) path.push(root);
        
        while (!path.empty()) {
            auto node = path.top();
            // 左右结点是否访问过标志，并且认为没有左右结点为访问过
            bool leftVisited = true, rightVisited = true;
            
            // 因为先访问左结点，在访问右结点，所有需要先把右结点入栈；左结点存在并且在marku不存在，则结点还没访问，右结点同理
            if (node->right && mark.find(node->right) == mark.end()) {
                rightVisited = false;
                path.push(node->right);
            }
            if (node->left && mark.find(node->left) == mark.end()) {
                leftVisited = false;
                path.push(node->left);
            }
            
            // 左右结点访问过了才能访问当前结点，并且把当前结点加入到mark中。
            if (leftVisited && rightVisited) {
                result.push_back(node->val);
                mark.insert(node);
                path.pop();
            }
        }
        
        return result;
    }
    
#pragma mark - 层序遍历
    
    
    vector<int> preorderTraverse(TreeNode *root) {
        return recursive_preorder_traverse(root);
//        return iterator_preorder_traverse(root);
    }
    
    vector<int> inorderTraverse(TreeNode *root) {
        return recursive_inorder_traverse(root);
//        return iterator_inorder_traverse(root);
    }
    
    vector<int> postorderTraverse(TreeNode *root) {
//        return recursive_postorder_traverse(root);
        return iterator_postorder_traverse(root);
    }
    
    vector<int> levelTraverse(TreeNode *root) {
        return {};
    }
    
#pragma mark - 所有路径
    
    vector<vector<int>> v1_allPath(TreeNode *node) {
        if (node == nullptr) return {};
        
        vector<vector<int>> leftPath = v1_allPath(node->left);
        vector<vector<int>> rightPath = v1_allPath(node->right);
        
        // merge path
        leftPath.insert(leftPath.end(), rightPath.begin(), rightPath.end());
    
        if (leftPath.empty()) {
            leftPath.push_back({node->val});
        } else {
            // 把当前结点插入到所有路径的第一个位置
            for (auto &item : leftPath) {
                item.insert(item.begin(), node->val);
            }
        }
        
        return leftPath;
    }
    

    
    void v2_allPath_helper(TreeNode *node, vector<int> &subPath, vector<vector<int>> &allPath) {
        if (node == nullptr) return;
        
        subPath.push_back(node->val);
        
        if (node->left == nullptr && node->right == nullptr) { // 到了叶子结点
            allPath.push_back(subPath);
        }
        
        v2_allPath_helper(node->left, subPath, allPath);
        v2_allPath_helper(node->right, subPath, allPath);
        
        subPath.pop_back();
    }
    
    vector<vector<int>> v2_allPath(TreeNode *root) {
        vector<vector<int>> allPath;
        vector<int> subPath;
        v2_allPath_helper(root, subPath, allPath);
        return allPath;
    }
    
    vector<vector<int>> allPath(TreeNode *root) {
//        return v1_allPath(root);
        return v2_allPath(root);
    }

}
