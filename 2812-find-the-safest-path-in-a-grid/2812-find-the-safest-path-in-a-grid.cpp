class Solution {
public:
    int maximumSafenessFactor(vector<vector<int>>& grid) {
        int n = grid.size();
        vector<vector<int>> dist(n, vector<int>(n, -1));
        queue<pair<int, int>> q;

        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (grid[i][j] == 1) {
                    dist[i][j] = 0;
                    q.push({i, j});
                }

        int dr[] = {0, 0, 1, -1}, dc[] = {1, -1, 0, 0};
        while (!q.empty()) {
            auto [r, c] = q.front();
            q.pop();
            for (int d = 0; d < 4; d++) {
                int nr = r + dr[d], nc = c + dc[d];
                if (nr >= 0 && nr < n && nc >= 0 && nc < n &&
                    dist[nr][nc] == -1) {
                    dist[nr][nc] = dist[r][c] + 1;
                    q.push({nr, nc});
                }
            }
        }

        auto canReach = [&](int k) {
            if (dist[0][0] < k || dist[n - 1][n - 1] < k)
                return false;
            vector<vector<bool>> vis(n, vector<bool>(n, false));
            queue<pair<int, int>> bq;
            bq.push({0, 0});
            vis[0][0] = true;
            while (!bq.empty()) {
                auto [r, c] = bq.front();
                bq.pop();
                if (r == n - 1 && c == n - 1)
                    return true;
                for (int d = 0; d < 4; d++) {
                    int nr = r + dr[d], nc = c + dc[d];
                    if (nr >= 0 && nr < n && nc >= 0 && nc < n &&
                        !vis[nr][nc] && dist[nr][nc] >= k) {
                        vis[nr][nc] = true;
                        bq.push({nr, nc});
                    }
                }
            }
            return false;
        };

        int lo = 0, hi = n;
        while (lo < hi) {
            int mid = (lo + hi + 1) / 2;
            if (canReach(mid))
                lo = mid;
            else
                hi = mid - 1;
        }
        return lo;
    }
};