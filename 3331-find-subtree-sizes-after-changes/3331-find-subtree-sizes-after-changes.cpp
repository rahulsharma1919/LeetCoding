
class Solution {
public:
    vector<int> findSubtreeSizes(vector<int>& parent, string s) {
        int n = parent.size();

        vector<vector<int>> adj(n);

        // Build original tree
        for (int i = 1; i < n; i++) {
            adj[parent[i]].push_back(i);
        }

        vector<int> newParent = parent;
        vector<int> last(26, -1);

        // Find closest matching ancestor
        function<void(int)> dfs1 = [&](int u) {
            int c = s[u] - 'a';

            int previous = last[c];

            if (u != 0 && previous != -1) {
                newParent[u] = previous;
            }

            last[c] = u;

            for (int v : adj[u]) {
                dfs1(v);
            }

            last[c] = previous;
        };

        dfs1(0);

        // Build modified tree
        vector<vector<int>> tree(n);

        for (int i = 1; i < n; i++) {
            tree[newParent[i]].push_back(i);
        }

        vector<int> ans(n, 0);

        // Calculate subtree sizes
        function<int(int)> dfs2 = [&](int u) {
            ans[u] = 1;

            for (int v : tree[u]) {
                ans[u] += dfs2(v);
            }

            return ans[u];
        };

        dfs2(0);

        return ans;
    }
};
