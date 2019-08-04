//
//  199-rightSideView.cpp
//  LeetCode
//
//  Created by Knox on 2019/8/4.
//  Copyright © 2019 nchkdxlq. All rights reserved.
//

#include "199-rightSideView.hpp"
#include "STLHelper.hpp"
#include "TreeHelper.hpp"

/*
 给定一棵二叉树，想象自己站在它的右侧，按照从顶部到底部的顺序，返回从右侧所能看到的节点值。
 
 输入: [1,2,3,null,5,null,4]
 输出: [1, 3, 4]
 
 */

namespace rightSideView_199 {
    class Solution {
    public:
        vector<int> rightSideView(TreeNode* root) {
            return v1_rightSideView(root);
        }
        
    private:
        
        /*
         BFS广度优先遍历,层次遍历，根按层返回数组类似，只不过是返回每一个层最后一个元素
         
         ## 复杂度分析
         - 时间复杂度: O(n), 每个结点被访问一次
         - 空间复杂度: 当树的每个结点只有一个结点时，ret需要的空间为O(n), q中最多只有一个结点，所以空间复杂度为O(n)
         当树是完全二叉树时，ret需要的空间为树的层数O(log(n))，当遍历到最后一层时，q中最多右n/2个结点，所以空间复杂度为O(n/2)+O(log(n))
         
         */
        vector<int> v1_rightSideView(TreeNode* root) {
            vector<int> ret;
            queue<TreeNode *> q;
            if (root) q.push(root);
            
            while(!q.empty()) {
                auto size = q.size();
                TreeNode *node = nullptr;
                for (int i = 0; i < size; i++) {
                    node = q.front();
                    q.pop();
                    if(node->left) q.push(node->left);
                    if (node->right) q.push(node->right);
                }
                ret.push_back(node->val);
            }
            
            return ret;
        }
        
        //  递归解法, DFS深度优先遍历
        vector<int> v2_rightSideView(TreeNode* root) {
            vector<int> ret;
            helper(root, ret, 0);
            return ret;
        }
        
        void helper(TreeNode *node, vector<int> &result, int level) {
            if (node == nullptr) return;
            
            if (level == result.size()) {
                result.push_back(node->val);
            }
            
            // 先遍历右结点，再遍历左结点
            helper(node->right, result, level+1);
            helper(node->left, result, level+1);
        }
        
        // leetcode 时间复杂度最好做法
        vector<int> v3_rightSideView(TreeNode* root) {
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
}



void __119_entry() {
    vector<int> nums = {1,2,3,INT_MAX,5,INT_MAX,4}; // [1, 3, 4]
    
    TreeNode *root = create_binaryTree(nums);
    auto ret = rightSideView_199::Solution().rightSideView(root);
    
    cout << "==== 199-rightSideView ====" << endl;
    print_vector(ret);
    
    cout << endl;
}
