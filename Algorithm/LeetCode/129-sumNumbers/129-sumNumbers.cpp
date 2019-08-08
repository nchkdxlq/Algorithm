//
//  129-sumNumbers.cpp
//  LeetCode
//
//  Created by Knox on 2019/8/7.
//  Copyright © 2019 nchkdxlq. All rights reserved.
//

#include "129-sumNumbers.hpp"
#include "STLHelper.hpp"
#include "TreeHelper.hpp"


/*
 给定一个二叉树，它的每个结点都存放一个 0-9 的数字，每条从根到叶子节点的路径都代表一个数字。
 
 例如，从根到叶子节点路径 1->2->3 代表数字 123。
 
 计算从根到叶子节点生成的所有数字之和。
 
 说明: 叶子节点是指没有子节点的节点。
 
 来源：力扣（LeetCode）
 链接：https://leetcode-cn.com/problems/sum-root-to-leaf-numbers
 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 
 */
namespace sumNumbers_129 {
    
    class Solution {
    public:
        int sumNumbers(TreeNode* root) {
//            return v1_sumNumbers(root);
            return v2_sumNumbers(root);
//            return v3_sumNumbers(root);
        }
    private:
        /*
         
         ### 解题思路
         如果能够知道树的所有路径，然后把每条路径代表的数值相加，就能得到题目要求的结果了。现在就把问题转化为如何求一个二叉树的所有路径。
         那么，如果求一个二叉树的所有路径呢？
         方法一：
         先求出左子树的所有路径，再求出右子树的所有路径，在把当前结点插入到所有路径的第一个位置。根据描述使用递归来实现即可。
         
         方法二：
         设计一个函数，参数接收的参数为当前结点、根结点到当前结点父节点的路径，
         
         
         执行用时 :24 ms, 在所有 C++ 提交中击败了10.27%的用户
         内存消耗 :18.1 MB, 在所有 C++ 提交中击败了5.03%的用户
         */
        int v1_sumNumbers(TreeNode* root) {
            if (root == nullptr) return 0;
            
            vector<vector<int>> paths = allPath(root);
            int ret = 0;
            
            for (auto &item : paths) {
                int sum = 0;
                for (auto i : item) {
                    sum = (sum * 10 + i);
                }
                ret += sum;
            }
            
            return ret;
        }
        
        vector<vector<int>> allPath(TreeNode *node) {
            if (node == nullptr) return {};
            
            vector<vector<int>> left = allPath(node->left);
            vector<vector<int>> right = allPath(node->right);
            
            left.insert(left.begin(), right.begin(), right.end());
            
            if (left.empty()) {
                left.push_back({node->val});
            } else {
                for(auto &item : left) {
                    item.insert(item.begin(), node->val);
                }
            }
            
            return left;
        }
        
        /*
         执行用时 :4 ms, 在所有 C++ 提交中击败了89.73%的用户
         内存消耗 :12.6 MB, 在所有 C++ 提交中击败了27.36%的用户
         */
        int v2_sumNumbers(TreeNode* root) {
            int sum = 0;
            v2_sumNumbers_helper(root, 0, sum);
            return sum;
        }
        
        
        /// @param node 当前结点
        /// @param num 根节点到当前结点父结点的组成的数字
        /// @param sum 路径和数组
        void v2_sumNumbers_helper(TreeNode *node, int num, int &sum) {
            if (node == nullptr) return;
            
            num = num * 10 + node->val;
            if (node->left == nullptr && node->right == nullptr) {
                sum += num;
                return;
            }
            
            v2_sumNumbers_helper(node->left, num, sum);
            v2_sumNumbers_helper(node->right, num, sum);
        }
        
        /*
         
         
         */
        int v3_sumNumbers(TreeNode *root) {
            stack<pair<TreeNode *, int>> path;
            int ret = 0;
            if (root) {
                path.push(make_pair(root, 0));
            }
            
            while (!path.empty()) {
                auto node_sum_pair = path.top();
                path.pop();
                TreeNode *node = node_sum_pair.first;
                int sum = node_sum_pair.second;
                sum = sum * 10 + node->val;
                if (node->left == nullptr && node->right == nullptr) {
                    ret += sum;
                }
                
                if (node->left) {
                    path.push(make_pair(node->left, sum));
                }
                
                if (node->right) {
                    path.push(make_pair(node->right, sum));
                }
            }
            
            return ret;
        }
        
    };
}


void __129_entry() {
    
    vector<int> nums = {1,2,3}; // 25
    nums = {4,9,0,5,1}; // 1026
    TreeNode *root = create_binaryTree(nums);
    int sum = sumNumbers_129::Solution().sumNumbers(root);
    
    cout << "==== 129-sumNumbers ====" << endl;
    cout << "sum = " << sum << endl;
}
