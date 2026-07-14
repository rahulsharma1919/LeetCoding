class Solution {
public:
    int subsequencePairCount(vector<int>& nums) {
        const int MOD = 1e9 + 7;
        int M = 201;
        vector<vector<long long>> dp(M, vector<long long>(M, 0));
        dp[0][0] = 1;

        for (int x : nums) {
            vector<vector<long long>> ndp(M, vector<long long>(M, 0));
            for (int g1 = 0; g1 < M; g1++) {
                for (int g2 = 0; g2 < M; g2++) {
                    if (!dp[g1][g2])
                        continue;
                    long long v = dp[g1][g2];
                    // skip x
                    ndp[g1][g2] = (ndp[g1][g2] + v) % MOD;
                    // add x to seq1
                    int ng1 = g1 == 0 ? x : __gcd(g1, x);
                    ndp[ng1][g2] = (ndp[ng1][g2] + v) % MOD;
                    // add x to seq2
                    int ng2 = g2 == 0 ? x : __gcd(g2, x);
                    ndp[g1][ng2] = (ndp[g1][ng2] + v) % MOD;
                }
            }
            dp = move(ndp);
        }

        long long ans = 0;
        for (int g = 1; g < M; g++)
            ans = (ans + dp[g][g]) % MOD;
        return (int)ans;
    }
};