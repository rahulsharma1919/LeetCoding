class Solution {
public:
    int maxWalls(vector<int>& robots, vector<int>& distance,
                 vector<int>& walls) {
        int n = robots.size();
        vector<int> idx(n);
        iota(idx.begin(), idx.end(), 0);
        sort(idx.begin(), idx.end(),
             [&](int a, int b) { return robots[a] < robots[b]; });

        vector<long long> pos(n), dist(n);
        for (int i = 0; i < n; i++) {
            pos[i] = robots[idx[i]];
            dist[i] = distance[idx[i]];
        }

        sort(walls.begin(), walls.end());

        auto countWalls = [&](long long lo, long long hi) -> int {
            if (lo > hi)
                return 0;
            return upper_bound(walls.begin(), walls.end(), (int)hi) -
                   lower_bound(walls.begin(), walls.end(), (int)lo);
        };

        if (n == 1) {
            return max(countWalls(pos[0] - dist[0], pos[0]),
                       countWalls(pos[0], pos[0] + dist[0]));
        }

        auto leftWalls = [&](int i) -> int {
            long long lo = (i > 0) ? pos[i - 1] + 1 : 1;
            return countWalls(max(pos[i] - dist[i], lo), pos[i]);
        };

        auto rightWalls = [&](int i) -> int {
            long long hi = (i < n - 1) ? pos[i + 1] - 1 : 2e9;
            return countWalls(pos[i], min(pos[i] + dist[i], hi));
        };

        auto overlapWalls = [&](int i) -> int {
            long long prevRight = min(pos[i - 1] + dist[i - 1], pos[i] - 1);
            long long curLeft = max(pos[i] - dist[i], pos[i - 1] + 1);
            return countWalls(curLeft, prevRight);
        };

        vector<long long> dp(2);
        dp[0] = leftWalls(0);
        dp[1] = rightWalls(0);

        for (int i = 1; i < n; i++) {
            int lw = leftWalls(i);
            int rw = rightWalls(i);
            int ov = overlapWalls(i);

            vector<long long> ndp(2);
            ndp[0] = max(dp[0] + lw, dp[1] + lw - ov);
            ndp[1] = max(dp[0], dp[1]) + rw;
            dp = ndp;
        }

        return max(dp[0], dp[1]);
    }
};