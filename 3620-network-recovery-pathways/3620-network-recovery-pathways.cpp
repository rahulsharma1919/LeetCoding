class Solution {
public:
    int findMaxPathScore(vector<vector<int>>& edges, vector<bool>& online,
                         long long k) {
        int n = online.size();
        vector<vector<pair<int, int>>> adj(n);
        vector<int> costs;

        for (auto& e : edges) {
            adj[e[0]].push_back({e[1], e[2]});
            costs.push_back(e[2]);
        }

        // Topological sort
        vector<int> indegree(n, 0);
        for (auto& e : edges)
            indegree[e[1]]++;
        queue<int> q;
        vector<int> topo;
        for (int i = 0; i < n; i++)
            if (indegree[i] == 0)
                q.push(i);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            topo.push_back(u);
            for (auto& [v, c] : adj[u])
                if (--indegree[v] == 0)
                    q.push(v);
        }

        sort(costs.begin(), costs.end());
        costs.erase(unique(costs.begin(), costs.end()), costs.end());

        // Check if there's a valid path where all edges >= minCost and total
        // cost <= k
        auto canReach = [&](int minCost) -> bool {
            const long long INF = 2e14;
            vector<long long> dp(n, INF);
            dp[0] = 0;

            for (int u : topo) {
                if (dp[u] == INF)
                    continue;
                // Intermediate nodes must be online
                if (u != 0 && u != n - 1 && !online[u])
                    continue;
                for (auto& [v, c] : adj[u]) {
                    if (c < minCost)
                        continue;
                    if (v != n - 1 && !online[v])
                        continue;
                    if (dp[u] + c < dp[v])
                        dp[v] = dp[u] + c;
                }
            }
            return dp[n - 1] <= k;
        };

        // Binary search on the minimum edge cost value
        int lo = 0, hi = (int)costs.size() - 1, ans = -1;
        while (lo <= hi) {
            int mid = (lo + hi) / 2;
            if (canReach(costs[mid])) {
                ans = costs[mid];
                lo = mid + 1;
            } else {
                hi = mid - 1;
            }
        }

        return ans;
    }
};