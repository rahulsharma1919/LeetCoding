class Solution {
public:
    long long minimumTotalDistance(vector<int>& robot,
                                   vector<vector<int>>& factory) {
        sort(robot.begin(), robot.end());
        sort(factory.begin(), factory.end());
        vector<int> fpos;
        for (auto& f : factory)
            for (int i = 0; i < f[1]; i++)
                fpos.push_back(f[0]);

        int n = robot.size(), m = fpos.size();
        vector<vector<long long>> dp(n + 1, vector<long long>(m + 1, 0));

        for (int i = 0; i < n; i++)
            dp[i][m] = 1e18;

        for (int j = m - 1; j >= 0; j--) {
            for (int i = n - 1; i >= 0; i--) {
                long long skip = dp[i][j + 1];
                long long take =
                    abs((long long)robot[i] - fpos[j]) + dp[i + 1][j + 1];
                dp[i][j] = min(skip, take);
            }
        }

        return dp[0][0];
    }
};