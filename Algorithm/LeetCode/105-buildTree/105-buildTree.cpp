//
//  105-buildTree.cpp
//  LeetCode
//
//  Created by Knox on 2019/8/4.
//  Copyright © 2019 nchkdxlq. All rights reserved.
//

#include "105-buildTree.hpp"
#include "STLHelper.hpp"
#include "TreeHelper.hpp"

/*
 
 根据一棵树的前序遍历与中序遍历构造二叉树。
 注意:
 你可以假设树中没有重复的元素。
 
 例如，给出
 前序遍历 preorder = [3,9,20,15,7]
 中序遍历 inorder = [9,3,15,20,7]
 
 https://leetcode-cn.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/
 
 */

namespace buildTree_105 {
    class Solution {
    public:
        TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
            if (preorder.empty() || inorder.empty()) return nullptr;
            if (preorder.size() != inorder.size()) return nullptr;
        
            // 记录inorder中值对应的下标
            unordered_map<int, int> inorder_map;
            int index = 0;
            
            for (int i = 0; i < inorder.size(); i++) {
                inorder_map[inorder[i]] = i;
            }
            
            return helper(inorder, 0, (int)inorder.size()-1, inorder_map, preorder, index);
        }
        
    private:
        
        // 在inorder[left...right]子数组中，查找值等于preorder[index]下标，
        TreeNode *helper(vector<int> &inorder, int left, int right, unordered_map<int, int> &index_map,
                            vector<int> &preorder, int index) {
            if (index >= preorder.size()) return nullptr;
            
            int rootIndex = index_map[preorder[index]];
            
            if (rootIndex < left || rootIndex > right) return nullptr;
            
            TreeNode *node = new TreeNode(inorder[rootIndex]);
            
            // 左子树的根节点为 preorder[index+1]
            node->left = helper(inorder, left, rootIndex-1, index_map, preorder, index+1);
            
            // len为左子树的结点个数, 所以index+len+1为右子树的根节点在preorder的下标
            int len = rootIndex - left;
            node->right = helper(inorder, rootIndex+1, right, index_map, preorder, index+len+1);
            
            return node;
        }
    };
}

void __105_entry() {
    vector<int> preorder = {1, 2};
    vector<int> inorder = {1, 2};
    
    preorder = {3,9,20,15,7};
    inorder = {9,3,15,20,7};
    
    TreeNode *root = buildTree_105::Solution().buildTree(preorder, inorder);
    
    vector<int> nums = preorderTraverse(root);
    
    cout << "==== 105-buildTree ====" << endl;
    print_vector(nums);
    cout << endl;
}
