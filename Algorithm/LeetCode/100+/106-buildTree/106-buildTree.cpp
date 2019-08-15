//
//  106-buildTree.cpp
//  LeetCode
//
//  Created by Knox on 2019/8/4.
//  Copyright © 2019 nchkdxlq. All rights reserved.
//

#include "106-buildTree.hpp"
#include "STLHelper.hpp"
#include "TreeHelper.hpp"


/*
 根据一棵树的中序遍历与后序遍历构造二叉树。
 
 注意:
 你可以假设树中没有重复的元素。
 
 例如，给出
 中序遍历 inorder = [9,3,15,20,7]
 后序遍历 postorder = [9,15,7,20,3]
 
 链接：https://leetcode-cn.com/problems/construct-binary-tree-from-inorder-and-postorder-traversal
 
 解题思路：
 
 中序遍历特点，左子树|根结点|右子树；后序遍历特点, 左子树|右子树|根结点.
 postorder数组中，最后一个元素为树的根结点，然后再在inorder中找到根结点的索引，从而知道左、右子树的区间。
 知道左右子树的区间，就知道左右子树的结点个数，从而在postorder找到左右子树的根节点。
 
 */

namespace buildTree_106 {
    
    class Solution {
    public:
        TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
            if (inorder.empty() || postorder.empty()) return nullptr;
            if (inorder.size() != postorder.size()) return nullptr;
            
            unordered_map<int, int> hash;
            for (int i = 0; i < inorder.size(); i++) {
                hash[inorder[i]] = i;
            }
            
            return helper(inorder, 0, (int)inorder.size()-1, hash, postorder, (int)postorder.size()-1);
        }
        
        
    private:
        TreeNode* helper(vector<int> &inorder, int left, int right,
                         unordered_map<int, int> &hash,
                         vector<int> &postorder, int index) {
            if (left > right) return nullptr;
            if (index < 0 || index > postorder.size()) return nullptr;
            
            int value = postorder[index];
            int rootIndex = hash[value];
            
            // 不在合法区间
            if (rootIndex < left || rootIndex > right) return nullptr;
            
            TreeNode *node = new TreeNode(value);
            
            // 右子树结点个数
            int len = right-rootIndex;
            
            // 在后序遍历中  左子树 | 右子树 | 根结点, 所以 index-len-1 就是左子树的根结点
            node->left = helper(inorder, left, rootIndex-1, hash, postorder, index-len-1);
            // 右子树的根结点为 index-1
            node->right = helper(inorder, rootIndex+1, right, hash, postorder, index-1);
            
            return node;
        }
    };
    
}


void __106_entry()  {
    vector<int> inorder = {9,3,15,20,7};
    vector<int> postorder = {9,15,7,20,3};
    
    TreeNode *root = buildTree_106::Solution().buildTree(inorder, postorder);
    
    vector<int> nums = inorderTraverse(root);
    
    cout << "==== 106-buildTree ====" << endl;
    print_vector(nums);
    cout << endl;
}
