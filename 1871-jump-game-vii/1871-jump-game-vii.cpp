class Solution {
public:
    bool canReach(string s, int minJump, int maxJump) {
        int n = s.size(), prefix = 0;
        vector<bool> dp(n, false);
        dp[0] = true;

        for (int i = 1; i < n; i++) {
            if (i >= minJump)
                prefix += dp[i - minJump];
            if (i > maxJump)
                prefix -= dp[i - maxJump - 1];
            if (s[i] == '0' && prefix > 0)
                dp[i] = true;
        }

        return dp[n - 1];
    }
};