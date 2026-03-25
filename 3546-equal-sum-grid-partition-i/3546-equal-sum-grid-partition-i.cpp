class Solution {
public:
    bool canPartitionGrid(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        long long total = 0;
        for (auto& row : grid)
            for (int v : row)
                total += v;

        if (total % 2 != 0)
            return false;
        long long half = total / 2;

        long long prefix = 0;
        for (int r = 0; r < m - 1; r++) {
            for (int v : grid[r])
                prefix += v;
            if (prefix == half)
                return true;
        }

        prefix = 0;
        for (int c = 0; c < n - 1; c++) {
            for (int r = 0; r < m; r++)
                prefix += grid[r][c];
            if (prefix == half)
                return true;
        }

        return false;
    }
};