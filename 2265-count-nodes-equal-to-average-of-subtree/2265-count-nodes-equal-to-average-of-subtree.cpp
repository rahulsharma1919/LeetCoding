/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    int count;
    
    // returns {sum, nodeCount} of the subtree rooted at node
    pair<int,int> dfs(TreeNode* node) {
        if (!node) return {0, 0};
        
        auto left = dfs(node->left);
        auto right = dfs(node->right);
        
        int sum = left.first + right.first + node->val;
        int nodeCount = left.second + right.second + 1;
        
        int avg = sum / nodeCount;
        if (avg == node->val) count++;
        
        return {sum, nodeCount};
    }
    
    int averageOfSubtree(TreeNode* root) {
        count = 0;
        dfs(root);
        return count;
    }
};