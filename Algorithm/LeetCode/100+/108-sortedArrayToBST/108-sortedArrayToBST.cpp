//
//  108-sortedArrayToBST.cpp
//  LeetCode
//
//  Created by Knox on 2019/8/10.
//  Copyright © 2019 nchkdxlq. All rights reserved.
//

#include "108-sortedArrayToBST.hpp"
#include "TreeHelper.hpp"
#include "STLHelper.hpp"


/*
 
 https://leetcode-cn.com/problems/convert-sorted-array-to-binary-search-tree/
 
 */
namespace sortedArrayToBST_108 {
    
    class Solution {
    public:
        TreeNode* sortedArrayToBST(vector<int>& nums) {
            return buildBST(nums, 0, (int)nums.size()-1);
        }
        
    private:
        
        /**
         以数组nums[left, right]区间的元素的值，递归构建一个BST
         
         @param nums 数组
         @param left 左闭区间
         @param right 右闭区间
         @return 返回树的根结点
         */
        TreeNode* buildBST(vector<int>& nums, int left, int right) {
            if (left > right) return nullptr;
            
            int mid = left + ((right -left) >> 2);
            
            TreeNode *node = new TreeNode(nums[mid]);
            node->left = buildBST(nums, left, mid-1);
            node->right = buildBST(nums, mid+1, right);
            
            return node;
        }
    };
    
}



void __108_entry() {
    vector<int> nums = {-10,-3,0,5,9};
    TreeNode *root = sortedArrayToBST_108::Solution().sortedArrayToBST(nums);
    
    auto retNums = inorderTraverse(root);
    
    cout << "==== 108-sortedArrayToBST ====" << endl;
    print_vector(retNums);
    cout << endl;
}
