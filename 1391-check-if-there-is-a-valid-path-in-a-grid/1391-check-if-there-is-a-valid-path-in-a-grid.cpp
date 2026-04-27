class Solution {
public:
    bool hasValidPath(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();

        vector<vector<int>> connects = {
            {}, {0, 1}, {2, 3}, {0, 3}, {1, 3}, {0, 2}, {1, 2},
        };

        int dr[] = {0, 0, -1, 1};
        int dc[] = {-1, 1, 0, 0};
        int opp[] = {1, 0, 3, 2};

        vector<vector<bool>> visited(m, vector<bool>(n, false));
        queue<pair<int, int>> q;
        q.push({0, 0});
        visited[0][0] = true;

        while (!q.empty()) {
            auto [r, c] = q.front();
            q.pop();

            if (r == m - 1 && c == n - 1)
                return true;

            int street = grid[r][c];
            for (int dir : connects[street]) {
                int nr = r + dr[dir], nc = c + dc[dir];
                if (nr < 0 || nr >= m || nc < 0 || nc >= n)
                    continue;
                if (visited[nr][nc])
                    continue;
                int needed = opp[dir];
                auto& nb = connects[grid[nr][nc]];
                if (find(nb.begin(), nb.end(), needed) == nb.end())
                    continue;
                visited[nr][nc] = true;
                q.push({nr, nc});
            }
        }

        return false;
    }
};