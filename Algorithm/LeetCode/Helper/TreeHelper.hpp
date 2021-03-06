//
//  TreeHelper.hpp
//  LeetCode
//
//  Created by Knox on 2019/7/15.
//  Copyright © 2019 nchkdxlq. All rights reserved.
//

#ifndef TreeHelper_hpp
#define TreeHelper_hpp

#include <stdio.h>
#include <vector>

using namespace std;

namespace BTree {
    
    
    struct TreeNode {
        TreeNode *left;
        TreeNode *right;
        int val;
        
        TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    };
    
    
    TreeNode* create_binaryTree(vector<int> &nums);
    
    vector<int> preorderTraverse(TreeNode *root);
    vector<int> inorderTraverse(TreeNode *root);
    vector<int> postorderTraverse(TreeNode *root);
    
    vector<int> levelTraverse(TreeNode *root);
    
    vector<vector<int>> allPath(TreeNode *root);
}



using namespace BTree;

#endif /* TreeHelper_hpp */
