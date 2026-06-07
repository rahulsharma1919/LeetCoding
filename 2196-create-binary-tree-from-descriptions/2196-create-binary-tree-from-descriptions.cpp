class Solution {
public:
    TreeNode* createBinaryTree(vector<vector<int>>& descriptions) {
        unordered_map<int, TreeNode*> nodes;
        unordered_set<int> children;

        auto get = [&](int v) {
            if (!nodes.count(v))
                nodes[v] = new TreeNode(v);
            return nodes[v];
        };

        for (auto& d : descriptions) {
            TreeNode* p = get(d[0]);
            TreeNode* c = get(d[1]);
            if (d[2])
                p->left = c;
            else
                p->right = c;
            children.insert(d[1]);
        }

        for (auto& [val, node] : nodes)
            if (!children.count(val))
                return node;

        return nullptr;
    }
};