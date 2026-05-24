class Solution {
public:
    int maxJumps(vector<int>& arr, int d) {
        int n = arr.size();
        vector<int> dp(n, -1);

        function<int(int)> dfs = [&](int i) -> int {
            if (dp[i] != -1)
                return dp[i];
            dp[i] = 1;
            for (int x = 1; x <= d; x++) {
                int j = i + x;
                if (j >= n || arr[j] >= arr[i])
                    break;
                dp[i] = max(dp[i], 1 + dfs(j));
            }
            for (int x = 1; x <= d; x++) {
                int j = i - x;
                if (j < 0 || arr[j] >= arr[i])
                    break;
                dp[i] = max(dp[i], 1 + dfs(j));
            }
            return dp[i];
        };

        int ans = 1;
        for (int i = 0; i < n; i++)
            ans = max(ans, dfs(i));
        return ans;
    }
};