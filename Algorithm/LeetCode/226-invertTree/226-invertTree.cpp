//
//  226-invertTree.cpp
//  LeetCode
//
//  Created by Knox on 2019/8/4.
//  Copyright © 2019 nchkdxlq. All rights reserved.
//

#include "226-invertTree.hpp"
#include "STLHelper.hpp"
#include "TreeHelper.hpp"


/*
 翻转一棵二叉树。
 
 */
namespace invertTree_226 {
    class Solution {
    public:
        TreeNode* invertTree(TreeNode* root) {
//            return v1_invertTree(root);
            return v2_invertTree(root);
//            return v3_invertTree(root);
        }
        
    private:
        TreeNode* v1_invertTree(TreeNode* root) {
            if (root == nullptr) return nullptr;

            TreeNode *left = invertTree(root->left);
            TreeNode *right = invertTree(root->right);
            root->left = right;
            root->right = left;
            
            return root;
        }
        
        TreeNode* v2_invertTree(TreeNode* root) {
            if (root == nullptr) return nullptr;
            
            swap(root->left, root->right);
            invertTree(root->left);
            invertTree(root->right);
            
            return root;
        }
        
        TreeNode* v3_invertTree(TreeNode* root) {
            if (root == nullptr) return nullptr;
            queue<TreeNode *> q;
            
            q.push(root);
            
            while (!q.empty()) {
                auto node = q.front();
                swap(node->left, node->right);
                q.pop();
                if(node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }
            
            return root;
        }
    };
}



void __226_entry() {
    vector<int> nums = {4, 2, 7, 1, 3, 6, 9};
    TreeNode *root = create_binaryTree(nums);
    
    TreeNode *ret = invertTree_226::Solution().invertTree(root);
    
    cout << "==== 226-invertTree ====" << endl;
    auto tmp = preorderTraverse(ret);
    print_vector(tmp);
    cout << endl;
}
