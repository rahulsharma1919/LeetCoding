class Solution {
public:
    int ans = 0;
    long long K;

    long long dfs(int node, int parent, vector<vector<int>>& adj,
                  vector<int>& values) {
        long long sum = values[node];

        for (int nei : adj[node]) {
            if (nei == parent)
                continue;
            sum += dfs(nei, node, adj, values);
        }

        if (sum % K == 0) {
            ans++;
            return 0; // cut here
        }

        return sum;
    }

    int maxKDivisibleComponents(int n, vector<vector<int>>& edges,
                                vector<int>& values, int k) {
        K = k;
        vector<vector<int>> adj(n);

        for (auto& e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        dfs(0, -1, adj, values);

        return ans;
    }
};
