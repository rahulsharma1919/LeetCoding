class Solution {
public:
    int shortestPath(int n, vector<vector<int>>& edges, string labels, int k) {
        vector<vector<pair<int, int>>> adj(n);
        for (auto& e : edges)
            adj[e[0]].push_back({e[1], e[2]});

        int K = k + 1;
        vector<int> dist((size_t)n * K, INT_MAX);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;

        dist[0 * K + 1] = 0;
        pq.push({0, 0 * K + 1});

        while (!pq.empty()) {
            auto [d, st] = pq.top();
            pq.pop();
            if (d > dist[st])
                continue;
            int u = st / K, run = st % K;
            if (u == n - 1)
                return d; // first pop of the target is optimal

            for (auto& [v, w] : adj[u]) {
                int nr = (labels[v] == labels[u]) ? run + 1 : 1;
                if (nr > k)
                    continue; // would exceed k identical in a row
                int ns = v * K + nr, nd = d + w;
                if (nd < dist[ns]) {
                    dist[ns] = nd;
                    pq.push({nd, ns});
                }
            }
        }
        return -1;
    }
};