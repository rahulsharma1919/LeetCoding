class Solution {
public:
    vector<int> remainingMethods(int n, int k,
                                 vector<vector<int>>& invocations) {
        vector<vector<int>> adj(n);
        for (auto& inv : invocations) {
            adj[inv[0]].push_back(inv[1]);
        }

        vector<bool> suspicious(n, false);
        suspicious[k] = true;
        queue<int> q;
        q.push(k);

        while (!q.empty()) {
            int cur = q.front();
            q.pop();
            for (int next : adj[cur]) {
                if (!suspicious[next]) {
                    suspicious[next] = true;
                    q.push(next);
                }
            }
        }

        for (auto& inv : invocations) {
            int a = inv[0], b = inv[1];
            if (!suspicious[a] && suspicious[b]) {

                vector<int> all(n);
                iota(all.begin(), all.end(), 0);
                return all;
            }
        }

        vector<int> result;
        for (int i = 0; i < n; i++) {
            if (!suspicious[i])
                result.push_back(i);
        }

        return result;
    }
};