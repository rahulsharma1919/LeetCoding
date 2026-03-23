class Solution {
public:
    int maxProductPath(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        const int MOD = 1e9 + 7;

        vector<vector<long long>> dpMax(m, vector<long long>(n, 0));
        vector<vector<long long>> dpMin(m, vector<long long>(n, 0));

        dpMax[0][0] = dpMin[0][0] = grid[0][0];

        for (int i = 1; i < m; i++)
            dpMax[i][0] = dpMin[i][0] = dpMax[i - 1][0] * grid[i][0];

        for (int j = 1; j < n; j++)
            dpMax[0][j] = dpMin[0][j] = dpMax[0][j - 1] * grid[0][j];

        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                int val = grid[i][j];

                if (val >= 0) {
                    dpMax[i][j] = max(dpMax[i - 1][j], dpMax[i][j - 1]) * val;
                    dpMin[i][j] = min(dpMin[i - 1][j], dpMin[i][j - 1]) * val;
                } else {
                    dpMax[i][j] = min(dpMin[i - 1][j], dpMin[i][j - 1]) * val;
                    dpMin[i][j] = max(dpMax[i - 1][j], dpMax[i][j - 1]) * val;
                }
            }
        }

        long long result = dpMax[m - 1][n - 1];
        if (result < 0)
            return -1;

        return result % MOD;
    }
};