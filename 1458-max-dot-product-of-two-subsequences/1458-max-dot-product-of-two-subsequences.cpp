class Solution {
public:
    int maxDotProduct(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size(), m = nums2.size();
        const int NEG_INF = -1e9;

        vector<vector<int>> dp(n + 1, vector<int>(m + 1, NEG_INF));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                int prod = nums1[i] * nums2[j];
                dp[i + 1][j + 1] =
                    max({prod, dp[i][j] + prod, dp[i][j + 1], dp[i + 1][j]});
            }
        }
        return dp[n][m];
    }
};
