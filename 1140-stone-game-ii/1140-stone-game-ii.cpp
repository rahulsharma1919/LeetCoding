class Solution {
public:
    int stoneGameII(vector<int>& piles) {
        int n = piles.size();
        vector<int> suffixSum(n + 1, 0);
        for (int i = n - 1; i >= 0; i--) {
            suffixSum[i] = suffixSum[i + 1] + piles[i];
        }

        vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));

        for (int i = n - 1; i >= 0; i--) {
            for (int M = 1; M <= n; M++) {
                int best = 0;
                for (int X = 1; X <= 2 * M && i + X <= n; X++) {
                    int newM = max(M, X);
                    int taken = suffixSum[i] - suffixSum[i + X];
                    int opponentBest = dp[i + X][newM];
                    best = max(best, taken + (suffixSum[i + X] - opponentBest));
                }
                dp[i][M] = best;
            }
        }

        return dp[0][1];
    }
};