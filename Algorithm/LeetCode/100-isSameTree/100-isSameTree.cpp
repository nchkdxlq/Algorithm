//
//  100-isSameTree.cpp
//  LeetCode
//
//  Created by Knox on 2019/7/18.
//  Copyright © 2019 nchkdxlq. All rights reserved.
//

#include "100-isSameTree.hpp"
#include "TreeHelper.hpp"
#include "STLHelper.hpp"


/*
 
 给定两个二叉树，编写一个函数来检验它们是否相同。
 如果两个树在结构上相同，并且节点具有相同的值，则认为它们是相同的。
 
 */

namespace IsSameTree_100 {
    
    class Solution {
    private:
        /*
         
         思路：利用广度优先遍历的方法，使用两个队列，分别把根结点加入队列。每次迭代中同时取出两个队列队首结点做以下操作
            - 判断结点的值是否相等，如果不相等则不满足条件，返回false
            - 如果结点的值相同，再比较结点左右孩子的结构，
                先比较左孩子
                 1) 如果左孩子都不存在，满足条件
                 2) 如果左孩子都存在，则把左孩子加入队列
                 3) 如果只有其中各一个结点左孩子存储，不符合条件， 返回false
                用同样的方法比较右孩子
            - 直到两个队列为空
         
         ## 复杂度分析
            - 时间复杂度：O(N)，其中 N 是树的结点数，因为每个结点都访问一次
            - 空间复杂度：最好情况，当树是完全不平衡二叉树时（每个结点最多只有一个孩子），在队列中最多只有一个结点，所以空间复杂度为O(1).
                        最坏情况，当树是完成二叉树时，比较到最后一层时，队列中最多右n/2个结点。所以空间复杂度为O(n)
         
         */
        bool v1_isSameTree(TreeNode* p, TreeNode* q) {
            if (p == nullptr && q == nullptr) return true;
            // 有其中一个为空
            if (!p || !q) return false;
            
            queue<TreeNode *> p_queue;
            queue<TreeNode *> q_queue;
            
            p_queue.push(p);
            q_queue.push(q);
            while (!p_queue.empty() && !q_queue.empty()) {

                p = p_queue.front();
                q = q_queue.front();
                
                p_queue.pop();
                q_queue.pop();
                
                if (p->val != q->val) {
                    return false;
                }
                
                // 左结点都存储
                if (p->left && q->left) {
                    p_queue.push(p->left);
                    q_queue.push(q->left);
                } else if (p->left || q->left) { // 只有一个结点的左结点存储，不符合
                    return false;
                } else {
                    // do nothing
                }
                
                // 右结点都存储
                if (p->right && q->right) {
                    p_queue.push(p->right);
                    q_queue.push(q->right);
                } else if (p->right || q->right) { // 只有一个结点的右结点存储，不符合
                    return false;
                } else {
                    // do nothing
                }
            }
            
            return true;
        }
        
        /**
         ## 思路
         利用递归方法判断，先判断当前结点是否相等，如果相等，在判断左右子树是否相等。
         注意递归的结束条件。
         
         ## 复杂度分析
         - 时间复杂度：O(n) 其中n是树的结点数，因为每个结点都访问一次。
         - 空间复杂度：最好情况，树是完成二叉树，递归的深度是log(n), 最坏情况，是完全不平衡二叉树，递归的深度为n， 用于维护递归栈
         
         */
            bool v2_isSameTree(TreeNode* p, TreeNode* q) {
                // p and q both null
                if (p == nullptr && q == nullptr) return true;
                
                // one of p and q null
                if (p == nullptr || q == nullptr) return  false;
                
                if (p->val != q->val) return false;
                
                return v2_isSameTree(p->left, q->left) && v2_isSameTree(p->right, q->right);
            }
        
    public:
        bool isSameTree(TreeNode* p, TreeNode* q) {
            return v1_isSameTree(p, q);
        }
    };
    
}



void __100_entry() {
    
    // true
    vector<int> nums1 = {1,2,3};
    vector<int> nums2 = {1,2,3};
    
    // false
    nums1 = {1,2,1};
    nums2 = {1,1,2};
    
    TreeNode *p = BTree::create_binaryTree(nums1);
    TreeNode *q = BTree::create_binaryTree(nums2);
    bool ret = IsSameTree_100::Solution().isSameTree(p, q);
    cout << (ret ? "true" : "false") << endl;
}
