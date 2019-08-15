//
//  145-postorderTraversal.cpp
//  LeetCode
//
//  Created by Knox on 2019/8/1.
//  Copyright © 2019 nchkdxlq. All rights reserved.
//

#include "145-postorderTraversal.hpp"
#include "STLHelper.hpp"
#include "TreeHelper.hpp"


/*
 给定一个二叉树，返回它的 后序 遍历。
 
 https://leetcode-cn.com/problems/binary-tree-postorder-traversal/
 */

namespace postorderTraversal_145 {
    
    class Solution {
    public:
        vector<int> postorderTraversal(TreeNode* root) {
//            return v1_postorderTraversal(root);
//            return v2_postorderTraversal(root);
            return v3_postorderTraversal(root);
        }
        
    private:
        
        vector<int> v1_postorderTraversal(TreeNode* root) {
            vector<int> ret;
            helper(root, ret);
            return ret;
        }
        
        //
        void helper(TreeNode *node, vector<int> &result) {
            if (node == nullptr) return;
            
            helper(node->left, result);
            helper(node->right, result);
            
            result.push_back(node->val);
        }
        
        
        vector<int> v2_postorderTraversal(TreeNode* root) {
            stack<TreeNode *> s1, s2;
            vector<int> ret;
            if (root) s1.push(root);
            
            while (!s1.empty()) {
                TreeNode *node = s1.top();
                s1.pop();
                
                s2.push(node);
                
                if (node->left) s1.push(node->left);
                if (node->right) s1.push(node->right);
            }
            
            while(!s2.empty()) {
                TreeNode *node = s2.top();
                s2.pop();
                ret.push_back(node->val);
            }
            
            return ret;
        }
        
        
        /*
         执行用时 :0 ms, 在所有 C++ 提交中击败了100.00%的用户
         内存消耗 :9.2 MB, 在所有 C++ 提交中击败了46.58%的用户
         
         - 时间复杂度：O(n)
         - 空间复杂度：O(n) 最好情况，当树为完成二叉树时，path中最多存在log(n)个结点，空间复杂度为log(n)
         最坏情况，左右子树退还为链表时，path中最多存在n/2个结点,空间复杂度为n/2;
         最好情况，最坏情况mark中最多会有n的结点，所以空间复杂度为O(n)
         
         */
        vector<int> v3_postorderTraversal(TreeNode* root) {
            vector<int> ret;
            
            stack<TreeNode *> path;
            unordered_set<TreeNode *> mark;
            
            if (root) path.push(root);
            
            while (!path.empty()) {
                auto node = path.top();
                
                bool leftVisited = true, rightVisited = true;
                
                // 左右结点判断先后顺序不能互换，因为需要先把右结点放进 stack 中
                if (node->right && mark.find(node->right) == mark.end()) {
                    rightVisited = false;
                    path.push(node->right);
                }
                
                if (node->left && mark.find(node->left) == mark.end()) {
                    leftVisited = false;
                    path.push(node->left);
                }
                
                if (leftVisited && rightVisited) { // 左右结点已经访问过了，才可以访问当前结点
                    ret.push_back(node->val);
                    mark.insert(node);
                    path.pop(); // 访问过了，从path中移除
                }
            }
            
            return ret;
        }
        
    };
    
}




void __145_entry() {
    vector<int> nums = {1,INT_MAX,2,3}; // [3, 2, 1]
    
    TreeNode *root = create_binaryTree(nums);
    
    vector<int> ret = postorderTraversal_145::Solution().postorderTraversal(root);
    
    cout << "==== 145-postorderTraversal ====" << endl;
    
    print_vector(ret);
    
    cout << endl;
}
