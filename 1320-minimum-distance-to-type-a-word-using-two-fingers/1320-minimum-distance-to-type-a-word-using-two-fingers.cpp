class Solution {
public:
    int minimumDistance(string word) {
        auto dist = [](int a, int b) -> int {
            if (a == 26 || b == 26)
                return 0;
            return abs(a / 6 - b / 6) + abs(a % 6 - b % 6);
        };

        int n = word.size();

        vector<int> dp(27, INT_MAX);
        dp[26] = 0;
        for (int i = 0; i < n; i++) {
            int cur = word[i] - 'A';
            int prev = (i > 0) ? word[i - 1] - 'A' : 26;
            vector<int> ndp(27, INT_MAX);

            for (int other = 0; other <= 26; other++) {
                if (dp[other] == INT_MAX)
                    continue;
                int cost1 = dp[other] + dist(prev, cur);
                if (cost1 < ndp[other])
                    ndp[other] = cost1;
                int cost2 = dp[other] + dist(other, cur);
                if (cost2 < ndp[prev])
                    ndp[prev] = cost2;
            }
            dp = ndp;
        }

        return *min_element(dp.begin(), dp.end());
    }
};