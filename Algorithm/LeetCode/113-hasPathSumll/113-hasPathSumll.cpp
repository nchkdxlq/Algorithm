//
//  113-hasPathSumll.cpp
//  LeetCode
//
//  Created by Knox on 2019/7/20.
//  Copyright © 2019 nchkdxlq. All rights reserved.
//

#include "113-hasPathSumll.hpp"
#include "TreeHelper.hpp"
#include "stlheaders.h"



/**
 给定一个二叉树和一个目标和，找到所有从根节点到叶子节点路径总和等于给定目标和的路径。
 
 说明: 叶子节点是指没有子节点的节点。
 
 https://leetcode-cn.com/problems/path-sum-ii/
 
 */
namespace hasPathSum_113 {
    class Solution {
    public:
        vector<vector<int>> hasPath(TreeNode *root, int sum) {
            return v1_hasPath(root, sum);
//            return v2_hasPath(root, sum);
//            return v3_hasPath(root, sum);
        }
        
    private:
        
        /**
         
         ## 思路
         遍历整个树，如果当前结点是叶子结点，并且结点的值等于sum，返回数组，如果不是叶子结点，递归调用函数 v1_hasPath，寻找在左右子树是否存在满足条件，
         其中sum为减去当前结点的值。
         
         ## 复杂度分析
         - 时间复杂度：O(n)
         - 空间复杂度：保存结果数组的空间不考虑，指考虑调用栈的复杂度。 最好情况当是一个完成二叉树时，递归的深度为`log(n)`,所以空间复杂度为`O(log(n))`;
         最坏情况，当二叉树每个结点最多只有一个结点，退化成链表时，递归的深度为`n`，空间复杂度为`O(n)`.
         */
        vector<vector<int>> v1_hasPath(TreeNode *root, int sum) {
            if (root == nullptr) return {};
            
            if (root->left == nullptr && root->right == nullptr && root->val == sum) {
                return {{root->val}};
            }
            
            vector<vector<int>> left = v1_hasPath(root->left, sum - root->val);
            vector<vector<int>> right = v1_hasPath(root->right, sum - root->val);
            left.insert(left.end(), right.begin(), right.end());
            
            for (auto &item : left) {
                item.insert(item.begin(), root->val);
            }
            
            return left;
        }
        
        
        vector<vector<int>> v2_hasPath(TreeNode *root, int sum) {
            vector<vector<int>> ret;
            
            vector<vector<int>> paths = allPath(root);
            for (auto &item : paths) {
                int tmp = 0;
                for (auto i : item) {
                    tmp += i;
                }
                
                if (tmp == sum) ret.push_back(item);
            }
            
            return ret;
        }
        
        vector<vector<int>> allPath(TreeNode *root) {
            if (root == nullptr) return {};
            
            vector<vector<int>> left = allPath(root->left);
            vector<vector<int>> right = allPath(root->right);
            
            left.insert(left.end(), right.begin(), right.end());
            
            if (left.empty()) {
                return {{root->val}};
            }
            
            for (auto &item : left) {
                item.insert(item.begin(), root->val);
            }
            return left;
        }
        
        
        vector<vector<int>> v3_hasPath(TreeNode *root, int sum) {
            vector<vector<int>>  ret;
            vector<int> subPath;
            helper(root, sum, subPath, ret);
            return ret;
        }
        
        
        void helper(TreeNode *root, int sum, vector<int> &subPath, vector<vector<int>> &path) {
            if (root == nullptr) return;
            
             subPath.push_back(root->val);
            
            if (root->left == nullptr && root->right == nullptr && root->val == sum) {
                vector<int> tmpPath = subPath;
                path.push_back(tmpPath);
            }
            
            helper(root->left, sum - root->val, subPath, path);
            helper(root->right, sum - root->val, subPath, path);
            
            subPath.pop_back();
        }
        
    };
}





void __113_entry() {
    
    vector<int> nums = {5,4,8,11,INT_MAX,13,4,7,2,INT_MAX,INT_MAX,5,1};
    int sum = 22;
    
    
    TreeNode *root = create_binaryTree(nums);
    vector<vector<int>> ret = hasPathSum_113::Solution().hasPath(root, sum);
    cout << "==== 113-hasPath ==== " << endl;
    
    for (auto &item : ret) {
        cout << "[ ";
        for (auto i : item) {
            cout << i << " ";
        }
        cout << "]" << endl;
    }
    
}
