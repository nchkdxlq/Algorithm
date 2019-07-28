//
//  98-isValidBST.cpp
//  LeetCode
//
//  Created by Knox on 2019/7/15.
//  Copyright © 2019 nchkdxlq. All rights reserved.
//

#include "98-isValidBST.hpp"
#include "STLHelper.hpp"
#include "TreeHelper.hpp"

using namespace BTree;



/**
 
 给定一个二叉树，判断其是否是一个有效的二叉搜索树。
 
 假设一个二叉搜索树具有如下特征：
 
 节点的左子树只包含小于当前节点的数。
 节点的右子树只包含大于当前节点的数。
 所有左子树和右子树自身必须也是二叉搜索树。
 
 来源：力扣（LeetCode）
 链接：https://leetcode-cn.com/problems/validate-binary-search-tree
 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 
 */

namespace isValidBST_98 {
    
    class Solution {
    public:
        bool isValidBST(TreeNode* root) {
//            return v1_isValidBST(root);
            return v2_isValidBST(root);
        }
        
        
    private:
        
        /**
         
         思路: 利用BST中序遍历是升序数组的特性，判断前一个结点是否小于当前结点的值，如果不满足，则不是BST
         
         时间复杂度：O(n) 最坏的情况数据是怎样的???
         空间复杂度：O(n) stack存储结点
         
         */
        bool v1_isValidBST(TreeNode* root) {
            stack<TreeNode *> __stack;
            TreeNode *pre = nullptr;
            // 迭代的方式中序遍历
            while(root || !__stack.empty()) {
                while (root) {
                    __stack.push(root);
                    root = root->left;
                }
                
                root = __stack.top();
                __stack.pop();
                
                if (pre && pre->val >= root->val) {
                    return false;
                }
                pre = root;
                root = root->right;
            }
            
            return true;
        }
        
        
        /*
         @undo
         
         上述思路可以用递归法实现。首先将结点的值与上界和下界（如果有）比较。然后，对左子树和右子树递归进行该过程
         
         还是不很理解
         
         ## 复杂度分析
         - 时间复杂度：O(n)
         - 空间复杂度：O(n)
         */
        bool v2_isValidBST(TreeNode *root) {
            return helper(root, nullptr, nullptr);
        }
        
        bool helper(TreeNode *root, TreeNode *max, TreeNode *min) {
            if (root == nullptr) return true;
            
            if (max && max->val <= root->val) return false;
            if (min && min->val >= root->val) return false;
            
            if (!helper(root->left, root, min)) return false;
            if (!helper(root->right, max, root)) return false;
            
            return true;
        }
        
    };
    
}








void __98_entry() {
    
    vector<int> nums = {5,1,4,INT_MAX,INT_MAX,3,6}; // false
    nums = {2,1,3}; // true
//    nums = {1,1}; // false
    TreeNode *root = create_binaryTree(nums);
    bool ret = isValidBST_98::Solution().isValidBST(root);
    cout << (ret ? "true" : "false") << endl;
}
