class Solution {
public:
    vector<int> assignEdgeWeights(vector<vector<int>>& edges,
                                  vector<vector<int>>& queries) {
        const int MOD = 1e9 + 7;
        int n = edges.size() + 1;
        const int LOG = 17;

        vector<vector<int>> adj(n + 1);
        for (auto& e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        vector<int> depth(n + 1, 0);
        vector<array<int, 17>> up(n + 1);
        for (auto& a : up)
            a.fill(0);

        vector<bool> visited(n + 1, false);
        queue<int> q;
        q.push(1);
        visited[1] = true;
        up[1][0] = 1;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v : adj[u]) {
                if (!visited[v]) {
                    visited[v] = true;
                    depth[v] = depth[u] + 1;
                    up[v][0] = u;
                    q.push(v);
                }
            }
        }

        for (int k = 1; k < LOG; k++)
            for (int v = 1; v <= n; v++)
                up[v][k] = up[up[v][k - 1]][k - 1];

        auto lca = [&](int u, int v) {
            if (depth[u] < depth[v])
                swap(u, v);
            int diff = depth[u] - depth[v];
            for (int k = 0; k < LOG; k++)
                if ((diff >> k) & 1)
                    u = up[u][k];
            if (u == v)
                return u;
            for (int k = LOG - 1; k >= 0; k--)
                if (up[u][k] != up[v][k]) {
                    u = up[u][k];
                    v = up[v][k];
                }
            return up[u][0];
        };

        vector<long long> pw(n + 1);
        pw[0] = 1;
        for (int i = 1; i <= n; i++)
            pw[i] = pw[i - 1] * 2 % MOD;

        vector<int> ans;
        ans.reserve(queries.size());
        for (auto& query : queries) {
            int u = query[0], v = query[1];
            int l = lca(u, v);
            int d = depth[u] + depth[v] - 2 * depth[l];
            if (d == 0)
                ans.push_back(0);
            else
                ans.push_back((int)pw[d - 1]);
        }
        return ans;
    }
};