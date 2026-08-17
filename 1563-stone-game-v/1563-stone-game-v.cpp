class Solution {
public:
    int stoneGameV(vector<int>& stoneValue) {
        int n = stoneValue.size();
        vector<long long> prefix(n + 1, 0);
        for (int i = 0; i < n; i++)
            prefix[i + 1] = prefix[i] + stoneValue[i];

        auto rangeSum = [&](int l, int r) -> long long {
            return prefix[r + 1] - prefix[l];
        };

        vector<vector<int>> dp(n, vector<int>(n, 0));

        // dp[i][j] = max score obtainable from stoneValue[i..j]
        for (int len = 2; len <= n; len++) {
            for (int i = 0; i + len - 1 < n; i++) {
                int j = i + len - 1;
                int best = 0;
                for (int k = i; k < j; k++) {
                    long long leftSum = rangeSum(i, k);
                    long long rightSum = rangeSum(k + 1, j);
                    int candidate;
                    if (leftSum < rightSum) {
                        candidate = (int)leftSum + dp[i][k];
                    } else if (leftSum > rightSum) {
                        candidate = (int)rightSum + dp[k + 1][j];
                    } else {
                        candidate = (int)leftSum + max(dp[i][k], dp[k + 1][j]);
                    }
                    best = max(best, candidate);
                }
                dp[i][j] = best;
            }
        }

        return dp[0][n - 1];
    }
};