class Solution {
public:
    int maxPathScore(vector<vector<int>>& grid, int k) {
        int m = grid.size(), n = grid[0].size();
        const int NEG = -1;
        vector<vector<vector<int>>> dp(
            m, vector<vector<int>>(n, vector<int>(k + 1, NEG)));

        dp[0][0][0] = 0;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                int val = grid[i][j];
                int cost = (val > 0) ? 1 : 0;
                int score = val;

                auto tryMove = [&](int pi, int pj) {
                    for (int c = 0; c <= k; c++) {
                        if (dp[pi][pj][c] == NEG)
                            continue;
                        int nc = c + cost;
                        if (nc > k)
                            continue;
                        dp[i][j][nc] = max(dp[i][j][nc], dp[pi][pj][c] + score);
                    }
                };

                if (i == 0 && j == 0)
                    continue;
                if (i > 0)
                    tryMove(i - 1, j);
                if (j > 0)
                    tryMove(i, j - 1);
            }
        }

        int ans = NEG;
        for (int c = 0; c <= k; c++)
            ans = max(ans, dp[m - 1][n - 1][c]);
        return ans;
    }
};