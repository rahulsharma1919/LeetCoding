class Solution {
public:
    bool findSafeWalk(vector<vector<int>>& grid, int health) {
        int m = grid.size(), n = grid[0].size();
        vector<vector<int>> best(m, vector<int>(n, 0));
        deque<tuple<int, int, int>> dq;

        int start = health - grid[0][0];
        if (start <= 0)
            return false;
        best[0][0] = start;
        dq.push_back({0, 0, start});

        int dr[] = {0, 0, 1, -1}, dc[] = {1, -1, 0, 0};

        while (!dq.empty()) {
            auto [r, c, h] = dq.front();
            dq.pop_front();
            if (r == m - 1 && c == n - 1)
                return h > 0;
            if (h < best[r][c])
                continue;

            for (int d = 0; d < 4; d++) {
                int nr = r + dr[d], nc = c + dc[d];
                if (nr < 0 || nr >= m || nc < 0 || nc >= n)
                    continue;
                int nh = h - grid[nr][nc];
                if (nh > best[nr][nc]) {
                    best[nr][nc] = nh;
                    if (grid[nr][nc] == 0)
                        dq.push_front({nr, nc, nh});
                    else
                        dq.push_back({nr, nc, nh});
                }
            }
        }

        return best[m - 1][n - 1] > 0;
    }
};