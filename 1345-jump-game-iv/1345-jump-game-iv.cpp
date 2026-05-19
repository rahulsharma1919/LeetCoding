class Solution {
public:
    int minJumps(vector<int>& arr) {
        int n = arr.size();
        if (n == 1)
            return 0;

        unordered_map<int, vector<int>> valIdx;
        for (int i = 0; i < n; i++)
            valIdx[arr[i]].push_back(i);

        vector<int> dist(n, -1);
        dist[0] = 0;
        queue<int> q;
        q.push(0);

        while (!q.empty()) {
            int i = q.front();
            q.pop();
            if (i == n - 1)
                return dist[i];
            int d = dist[i] + 1;

            auto tryVisit = [&](int j) {
                if (j >= 0 && j < n && dist[j] == -1) {
                    dist[j] = d;
                    q.push(j);
                }
            };

            tryVisit(i - 1);
            tryVisit(i + 1);

            auto it = valIdx.find(arr[i]);
            if (it != valIdx.end()) {
                for (int j : it->second)
                    tryVisit(j);
                it->second.clear();
            }
        }

        return -1;
    }
};