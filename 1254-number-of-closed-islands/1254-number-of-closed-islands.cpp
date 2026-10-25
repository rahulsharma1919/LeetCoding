class Solution {
public:
    int n, m;

    void fill(vector<vector<int>>& g, int r, int c) {
        vector<pair<int, int>> st;
        st.push_back({r, c});
        g[r][c] = 1;
        while (!st.empty()) {
            auto [x, y] = st.back();
            st.pop_back();
            if (x > 0 && !g[x - 1][y]) {
                g[x - 1][y] = 1;
                st.push_back({x - 1, y});
            }
            if (x + 1 < n && !g[x + 1][y]) {
                g[x + 1][y] = 1;
                st.push_back({x + 1, y});
            }
            if (y > 0 && !g[x][y - 1]) {
                g[x][y - 1] = 1;
                st.push_back({x, y - 1});
            }
            if (y + 1 < m && !g[x][y + 1]) {
                g[x][y + 1] = 1;
                st.push_back({x, y + 1});
            }
        }
    }

    int closedIsland(vector<vector<int>>& grid) {
        n = grid.size();
        m = grid[0].size();

        for (int i = 0; i < n; i++) {
            if (!grid[i][0])
                fill(grid, i, 0);
            if (!grid[i][m - 1])
                fill(grid, i, m - 1);
        }
        for (int j = 0; j < m; j++) {
            if (!grid[0][j])
                fill(grid, 0, j);
            if (!grid[n - 1][j])
                fill(grid, n - 1, j);
        }

        int cnt = 0;
        for (int i = 1; i < n - 1; i++)
            for (int j = 1; j < m - 1; j++)
                if (!grid[i][j]) {
                    cnt++;
                    fill(grid, i, j);
                }

        return cnt;
    }
};