//
//  437-PathSumIII.cpp
//  LeetCode
//
//  Created by Knox on 2019/7/22.
//  Copyright © 2019 nchkdxlq. All rights reserved.
//

#include "437-PathSumIII.hpp"
#include "TreeHelper.hpp"
#include "STLHelper.hpp"


/**
 
 给定一个二叉树，它的每个结点都存放着一个整数值。
 
 找出路径和等于给定数值的路径总数。
 
 路径不需要从根节点开始，也不需要在叶子节点结束，但是路径方向必须是向下的（只能从父节点到子节点）。
 
 二叉树不超过1000个节点，且节点数值范围是 [-1000000,1000000] 的整数。
 
 来源：力扣（LeetCode）
 链接：https://leetcode-cn.com/problems/path-sum-iii
 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 
 */

namespace PathSumIII_437 {
    
    class Solution {
    public:
        // 在以root为根节点的二叉树中，寻找和为sum的路径，返回这样路径的个数
        int pathSum(TreeNode *root, int sum) {
            return v1_pathSum(root, sum);
            return v2_pathSum(root, sum);
        }
        
    private:
        
        int v1_pathSum(TreeNode *root, int sum) {
            if (root == nullptr) return 0;
            
            int count = findPath(root, sum);
            count += v1_pathSum(root->left, sum);
            count += v1_pathSum(root->right, sum);
            
            return count;
        }
        // 在以node为根节点的二叉树中，寻找包含node的和为sum的路径，返回这样路径的个数
        int findPath(TreeNode *node, int sum) {
            if (node == nullptr) return 0;
            
            int ret = 0;
            if (node->val == sum) {
                ret += 1;
            }
            
            ret += findPath(node->left, sum - node->val);
            ret += findPath(node->right, sum - node->val);
            
            return ret;
        }
        
        /*
         执行用时 :64 ms, 在所有 C++ 提交中击败了13.51%的用户
         内存消耗 :14.5 MB, 在所有 C++ 提交中击败了93.50%的用户
         */
        // 以所有结点为根结点的子树中寻找和为sum的路径个数总和
        int v2_pathSum(TreeNode* root, int sum) {
            if (root == nullptr) return 0;
            
            queue<TreeNode *> q;
            q.push(root);
            int ret = 0;
            while (!q.empty()) {
                TreeNode *node = q.front();
                q.pop();
                
                if (node->left) {
                    q.push(node->left);
                }
                
                if (node->right) {
                    q.push(node->right);
                }
                
                // 以node为根节点的子树中，和为sum的路径个数
                ret += findPath(node, sum);
            }
            
            return ret;
        }
        
#if 0
        int v2_pathSum(TreeNode* root, int sum) {
            if (root == nullptr) return 0;
            
            int count = 0;
            
            if (root->val == sum) {
                count = 1;
            }
            
            int left = v2_pathSum(root->left, sum) + v2_pathSum(root->left, sum - root->val);
            int right = v2_pathSum(root->right, sum) + v2_pathSum(root->right, sum - root->val);
            
            return left + right + count;
        }
#endif
    };
}


void __437_entry() {
    
    vector<int> nums = {10,5,-3,3,2,INT_MAX,11,3,-2,INT_MAX,1};
    
    TreeNode *root = create_binaryTree(nums);
    int sum = 8;
    int ret = PathSumIII_437::Solution().pathSum(root, sum);
    
    cout << "==== 437-PathSumIII ====" << endl;
    
    cout << ret << endl;
}
