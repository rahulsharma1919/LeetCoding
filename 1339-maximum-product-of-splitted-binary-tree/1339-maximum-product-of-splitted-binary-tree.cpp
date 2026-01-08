/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left),
 * right(right) {}
 * };
 */
class Solution {
public:
    static const int MOD = 1e9 + 7;
    long long totalSum = 0;
    long long best = 0;
    long long dfsSum(TreeNode* root) {
        if (!root)
            return 0;
        return root->val + dfsSum(root->left) + dfsSum(root->right);
    }
    long long dfs(TreeNode* root) {
        if (!root)
            return 0;
        long long left = dfs(root->left);
        long long right = dfs(root->right);

        long long sub = root->val + left + right;
        best = max(best, sub * (totalSum - sub));

        return sub;
    }
    int maxProduct(TreeNode* root) {
        totalSum = dfsSum(root);
        dfs(root);
        return best % MOD;
    }
};
