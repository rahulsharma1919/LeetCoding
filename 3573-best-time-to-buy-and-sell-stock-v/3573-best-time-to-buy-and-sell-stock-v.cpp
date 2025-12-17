class Solution {
public:
    long long maximumProfit(vector<int>& prices, int k) {
        int n = prices.size();
        const long long NEG = -1e18;
        vector<vector<long long>> dp(k + 1, vector<long long>(3, NEG));
        dp[0][0] = 0;

        for (int price : prices) {
            auto prev = dp;
            for (int t = 0; t <= k; t++) {
                dp[t][0] = max(dp[t][0], prev[t][0]);

                dp[t][1] = max(dp[t][1], prev[t][0] - price);

                dp[t][2] = max(dp[t][2], prev[t][0] + price);

                if (t < k) {
                    dp[t + 1][0] = max(dp[t + 1][0], prev[t][1] + price);

                    dp[t + 1][0] = max(dp[t + 1][0], prev[t][2] - price);
                }
            }
        }

        long long ans = 0;
        for (int t = 0; t <= k; t++) {
            ans = max(ans, dp[t][0]);
        }
        return ans;
    }
};
