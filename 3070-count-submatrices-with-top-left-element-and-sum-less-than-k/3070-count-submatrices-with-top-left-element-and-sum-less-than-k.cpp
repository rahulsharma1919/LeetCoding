class Solution {
public:
    int countSubmatrices(vector<vector<int>>& grid, int k) {
        int m = grid.size(), n = grid[0].size(), ans = 0;

        for (int r = 0; r < m; r++)
            for (int c = 0; c < n; c++) {
                if (r)
                    grid[r][c] += grid[r - 1][c];
                if (c)
                    grid[r][c] += grid[r][c - 1];
                if (r && c)
                    grid[r][c] -= grid[r - 1][c - 1];
                if (grid[r][c] <= k)
                    ans++;
            }

        return ans;
    }
};