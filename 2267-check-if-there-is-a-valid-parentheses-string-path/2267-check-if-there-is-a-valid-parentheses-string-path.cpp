class Solution {
public:
    bool hasValidPath(vector<vector<char>>& grid) {
        int m = grid.size(), n = grid[0].size();

        // quick rejections: odd length, bad start, or bad end
        if ((m + n - 1) % 2 == 1)
            return false;
        if (grid[0][0] == ')' || grid[m - 1][n - 1] == '(')
            return false;

        // dp[j] = bitset of achievable balances at cell (i, j); bit b set =>
        // balance b reachable max useful balance is (m+n)/2 <= 100
        vector<bitset<128>> dp(n);

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                bitset<128> in;
                if (i == 0 && j == 0)
                    in[0] = 1; // empty prefix, balance 0
                else {
                    if (i > 0)
                        in |= dp[j]; // from above (previous row value)
                    if (j > 0)
                        in |= dp[j - 1]; // from left (current row value)
                }

                if (grid[i][j] == '(')
                    dp[j] = in << 1; // balance + 1
                else
                    dp[j] = in >> 1; // balance - 1 (bit 0 falls off = invalid)
            }
        }

        return dp[n - 1][0];
    }
};