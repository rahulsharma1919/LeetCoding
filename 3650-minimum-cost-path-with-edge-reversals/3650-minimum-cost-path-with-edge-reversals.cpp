class Solution {
public:
    int minCost(int n, vector<vector<int>>& edges) {
        vector<vector<pair<int, int>>> out(n), in(n);

        for (auto& e : edges) {
            out[e[0]].push_back({e[1], e[2]});
            in[e[1]].push_back({e[0], e[2]});
        }

        const long long INF = 1e18;
        vector<long long> dist(n, INF);
        priority_queue<pair<long long, int>, vector<pair<long long, int>>,
                       greater<>>
            pq;

        dist[0] = 0;
        pq.push({0, 0});

        while (!pq.empty()) {
            auto [cost, u] = pq.top();
            pq.pop();

            if (cost > dist[u])
                continue;

            for (auto [v, w] : out[u]) {
                if (dist[v] > cost + w) {
                    dist[v] = cost + w;
                    pq.push({dist[v], v});
                }
            }

            for (auto [v, w] : in[u]) {
                if (dist[v] > cost + 2LL * w) {
                    dist[v] = cost + 2LL * w;
                    pq.push({dist[v], v});
                }
            }
        }
        return dist[n - 1] == INF ? -1 : dist[n - 1];
    }
};
