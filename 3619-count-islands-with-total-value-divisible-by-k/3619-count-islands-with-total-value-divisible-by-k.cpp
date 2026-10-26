class Solution {
public:
    int countIslands(vector<vector<int>>& grid, int k) {
        int m = grid.size(), n = grid[0].size(), cnt = 0;
        vector<pair<int, int>> st;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] <= 0)
                    continue;
                long long sum = 0;
                st.push_back({i, j});
                sum += grid[i][j];
                grid[i][j] = 0; // mark visited

                while (!st.empty()) {
                    auto [x, y] = st.back();
                    st.pop_back();
                    if (x > 0 && grid[x - 1][y] > 0) {
                        sum += grid[x - 1][y];
                        grid[x - 1][y] = 0;
                        st.push_back({x - 1, y});
                    }
                    if (x + 1 < m && grid[x + 1][y] > 0) {
                        sum += grid[x + 1][y];
                        grid[x + 1][y] = 0;
                        st.push_back({x + 1, y});
                    }
                    if (y > 0 && grid[x][y - 1] > 0) {
                        sum += grid[x][y - 1];
                        grid[x][y - 1] = 0;
                        st.push_back({x, y - 1});
                    }
                    if (y + 1 < n && grid[x][y + 1] > 0) {
                        sum += grid[x][y + 1];
                        grid[x][y + 1] = 0;
                        st.push_back({x, y + 1});
                    }
                }

                if (sum % k == 0)
                    cnt++;
            }
        }
        return cnt;
    }
};