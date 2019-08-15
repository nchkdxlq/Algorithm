//
//  230-kthSmallest.cpp
//  LeetCode
//
//  Created by Knox on 2019/8/15.
//  Copyright © 2019 nchkdxlq. All rights reserved.
//

#include "230-kthSmallest.hpp"
#include "TreeHelper.hpp"
#include "STLHelper.hpp"
/*
    230. 二叉搜索树中第K小的元素
    https://leetcode-cn.com/problems/kth-smallest-element-in-a-bst/submissions/
 */


namespace kthSmallest_230 {
    class Solution {
    public:
        int kthSmallest(TreeNode* root, int k) {
//            return v1_kthSmallest(root, k);
            return v2_kthSmallest(root, k);
        }
        
    private:
        
        // 迭代中序遍历到第k个结点
        int v1_kthSmallest(TreeNode* root, int k) {
            stack<TreeNode *> __stack;
            int index = 1;
            int ret = -1;
            
            auto node = root;
            while (node || !__stack.empty()) {
                while (node) {
                    __stack.push(node);
                    node = node->left;
                }
                
                node = __stack.top();
                __stack.pop();
                if (index == k) {
                    ret = node->val;
                    break;
                }
                index++;
                
                node = node->right;
            }
            
            return ret;
        }
        
        
        int v2_kthSmallest(TreeNode* root, int k) {
            int ret = 0;
            int index = 0;
            v2_helper(root, k, index, ret);
            return ret;
        }
        
        void v2_helper(TreeNode *node, int k, int &index, int &result) {
            if (node == nullptr) return;
            v2_helper(node->left, k, index, result);
            // 细节处理
            index++;
            if (index == k) {
                result = node->val;
                return;
            }
            
            v2_helper(node->right, k, index, result);
        }
        
        
        // 自己写的一个递归版本，虽然能解决问题，但是不够v2写法优雅
        int m_k;
        int m_result;
        
        int v3_kthSmallest(TreeNode* root, int k) {
            m_k = k;
            helper(root);
            return m_result;
        }
        
        void helper(TreeNode *node) {
            if (node == nullptr) return;
            
            helper(node->left);
            if (m_k == 1) {
                m_result = node->val;
                m_k--;
                return;
            }
            m_k--;
            helper(node->right);
        }
        
    };
}



void __230_entry() {
    
    // ret = 1
    vector<int> nums = {3,1,4,INT_MAX,2};
    int k = 1;
    
    // ret = 3
    nums = {5,3,6,2,4,INT_MAX,INT_MAX,1};
    k = 3;
    
    TreeNode *root = create_binaryTree(nums);
    int ret = kthSmallest_230::Solution().kthSmallest(root, k);
    
    cout << "==== 230-kthSmallest ====" << endl;
    cout << "ret = " << ret << endl;
    
}
