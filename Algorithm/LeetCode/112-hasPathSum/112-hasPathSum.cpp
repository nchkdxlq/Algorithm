//
//  112-hasPathSum.cpp
//  LeetCode
//
//  Created by Knox on 2019/7/20.
//  Copyright © 2019 nchkdxlq. All rights reserved.
//

#include "112-hasPathSum.hpp"
#include "TreeHelper.hpp"
#include "stlheaders.h"

namespace hasPathSum_112 {
    
    class Solution {
    public:
        bool hasPathSum(TreeNode *root, int sum) {
//            return v1_hasPathSum(root, sum);
            return v2_hasPathSum(root, sum);
        }
        
    private:
        bool v1_hasPathSum(TreeNode *root, int sum) {
            if (root == nullptr) return false;
            
            // 递归结束条件
            if (root->left == nullptr && root->right == nullptr) {
                return root->val == sum;
            }
            
            // 递归过程
            return v1_hasPathSum(root->left, (sum - root->val)) || v1_hasPathSum(root->right, (sum - root->val));
        }
        
        
        
        bool v2_hasPathSum(TreeNode *root, int sum) {
            if (root == nullptr) return false;
            
            stack<pair<TreeNode *, int>> __stack;
            __stack.push(make_pair(root, sum));
            
            while (!__stack.empty()) {
                auto &item = __stack.top();
                auto node = item.first;
                sum = item.second;
                __stack.pop();
                
                if (node->left == nullptr && node->right == nullptr && node->val == sum) {
                    return true;
                }
                
                if (node->left) {
                    __stack.push(make_pair(node->left, sum - node->val));
                }
                
                if (node->right) {
                    __stack.push(make_pair(node->right, sum - node->val));
                }
            }
            
            return false;
        }
    };
}




void __112_entry() {
    vector<int> nums = {5, 4, 8, 11, INT_MAX, 13, 4, 7, 2, INT_MAX, INT_MAX, INT_MAX, 1};
    int sum = 22;
    
    
    TreeNode *root = create_binaryTree(nums);
    bool ret = hasPathSum_112::Solution().hasPathSum(root, sum);
    cout << "==== 112-hasPathSum ==== " << endl;
    cout << (ret ? "true" : "false") << endl;
}
