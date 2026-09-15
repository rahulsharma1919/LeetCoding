class Solution {
public:
    int maxPalindromes(string s, int k) {
        int n = s.size();

        // isPal[i][j] = true if s[i..j] (inclusive) is a palindrome
        vector<vector<bool>> isPal(n, vector<bool>(n, false));
        for (int i = 0; i < n; i++)
            isPal[i][i] = true;
        for (int i = 0; i + 1 < n; i++)
            isPal[i][i + 1] = (s[i] == s[i + 1]);

        for (int len = 3; len <= n; len++) {
            for (int i = 0; i + len - 1 < n; i++) {
                int j = i + len - 1;
                isPal[i][j] = (s[i] == s[j]) && isPal[i + 1][j - 1];
            }
        }

        vector<int> dp(n + 1, 0);

        for (int i = 1; i <= n; i++) {
            dp[i] = dp[i - 1];
            if (i >= k) {
                int start = i - k;
                if (isPal[start][i - 1]) {
                    dp[i] = max(dp[i], dp[start] + 1);
                }
            }

            // try substring of length exactly k+1 ending at position i-1
            if (i >= k + 1) {
                int start = i - (k + 1);
                if (isPal[start][i - 1]) {
                    dp[i] = max(dp[i], dp[start] + 1);
                }
            }
        }

        return dp[n];
    }
};