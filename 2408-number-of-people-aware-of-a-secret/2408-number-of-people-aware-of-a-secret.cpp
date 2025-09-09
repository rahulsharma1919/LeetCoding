class Solution {
public:
    int peopleAwareOfSecret(int n, int delay, int forget) {
        const int MOD = 1e9 + 7;
        vector<long long> dp(n + 1, 0); 
        dp[1] = 1; // Day 1: one person knows the secret
        
        long long share = 0; 
        
        for (int day = 2; day <= n; day++) {
            // People who start sharing today
            if (day - delay >= 1) {
                share = (share + dp[day - delay]) % MOD;
            }
            // People who forget today stop contributing
            if (day - forget >= 1) {
                share = (share - dp[day - forget] + MOD) % MOD;
            }
            dp[day] = share; 
        }
        
        long long ans = 0;
        // Sum of people who still remember the secret on day n
        for (int i = n - forget + 1; i <= n; i++) {
            if (i >= 1) ans = (ans + dp[i]) % MOD;
        }
        return ans;
    }
};
