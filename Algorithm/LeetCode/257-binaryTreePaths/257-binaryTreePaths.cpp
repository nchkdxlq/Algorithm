//
//  257-binaryTreePaths.cpp
//  LeetCode
//
//  Created by Knox on 2019/7/20.
//  Copyright © 2019 nchkdxlq. All rights reserved.
//

#include "257-binaryTreePaths.hpp"
#include "TreeHelper.hpp"
#include "STLHelper.hpp"


/**
 
 给定一个二叉树，返回所有从根节点到叶子节点的路径。
 
 说明: 叶子节点是指没有子节点的节点。
 
 */

namespace binaryTreePaths_257 {
    
    class Solution {
    public:
        vector<string> binaryTreePaths(TreeNode* root) {
//            return v1_binaryTreePaths(root);
//            return v2_binaryTreePaths(root);
            return v3_binaryTreePaths(root);
        }
        
    private:
        
        vector<string> v1_binaryTreePaths(TreeNode* root) {
            vector<string> ret;
            v1_helper(root, "", ret);
            return ret;
        }
        
        void v1_helper(TreeNode* root, string subPath, vector<string> &paths) {
            if (root == nullptr) return;
            
            if (subPath.empty()) {
                subPath = to_string(root->val);
            } else {
                subPath += "->";
                subPath += to_string(root->val);
            }
            
            if (root->left == nullptr && root->right == nullptr) {
                paths.push_back(subPath);
            }
            
            v1_helper(root->left, subPath, paths);
            v1_helper(root->right, subPath, paths);
        }
        
        
        vector<string> v2_binaryTreePaths(TreeNode* root) {
            if (root == nullptr) return {};
            
            vector<string> left = binaryTreePaths(root->left);
            vector<string> right = binaryTreePaths(root->right);
            
            left.insert(left.end(), right.begin(), right.end());
            
            string curStr = to_string(root->val);
            
            if (left.empty()) {
                return {curStr};
            } else {
                vector<string> ret;
                for (auto &item : left) {
                    ret.push_back(curStr + "->" + item);
                }
                return ret;
            }
        }
        
        /**
         执行用时 :4 ms, 在所有 C++ 提交中击败了 94.48% 的用户
         内存消耗 :11.5 MB, 在所有 C++ 提交中击败了 89.24% 的用户
         */
        vector<string> v3_binaryTreePaths(TreeNode* root) {
            vector<vector<TreeNode *>> paths;
            vector<TreeNode *> subPath;
            
            v3_helper(root, subPath, paths);
            
            vector<string> ret;
            
            for (auto &path : paths) {
                string str = to_string(path[0]->val);
                for (int i = 1; i < path.size(); i++) {
                    str += "->";
                    str += to_string(path[i]->val);
                }
                ret.push_back(str);
            }
            
            return ret;
        }
        
        
        /**
         记录以node为根结点到叶子结点的所有路径

         @param node 树的结点
         @param subPath 树的根结点到该结点的路径
         @param paths 保存的是根节点到叶子结点的路径
         */
        void v3_helper(TreeNode *node, vector<TreeNode *> &subPath, vector<vector<TreeNode *>> &paths) {
            if (node == nullptr) return;
            
            subPath.push_back(node);
            
            if (node->left == nullptr && node->right == nullptr) {
                vector<TreeNode *> tmp = subPath;
                paths.push_back(tmp);
            }
            
            v3_helper(node->left, subPath, paths);
            v3_helper(node->right, subPath, paths);
            
            // 需要回到node的父节点，所以需要pop当前结点
            subPath.pop_back();
        }
        
    };
    
    
}



void __257_entry() {
    
    
    vector<int> nums = {1, 2, 3, 5};
    
    TreeNode *root = create_binaryTree(nums);

    vector<string> ret = binaryTreePaths_257::Solution().binaryTreePaths(root);
    
    cout << "==== 257-binaryTreePaths ====" << endl;
    cout << "[ ";
    for (auto &s : ret) {
        cout << "\"" << s << "\"" << " ";
    }
    cout << "]" << endl;
}
