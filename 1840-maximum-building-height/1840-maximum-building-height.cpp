class Solution {
public:
    int maxBuilding(int n, vector<vector<int>>& restrictions) {
        restrictions.push_back({1, 0});
        restrictions.push_back({n, n - 1}); // unconstrained: can go up to n-1
        sort(restrictions.begin(), restrictions.end());

        int m = restrictions.size();

        // Left pass: each building can't exceed prev + gap
        for (int i = 1; i < m; i++) {
            int gap = restrictions[i][0] - restrictions[i - 1][0];
            restrictions[i][1] =
                min(restrictions[i][1], restrictions[i - 1][1] + gap);
        }

        // Right pass: each building can't exceed next + gap
        for (int i = m - 2; i >= 0; i--) {
            int gap = restrictions[i + 1][0] - restrictions[i][0];
            restrictions[i][1] =
                min(restrictions[i][1], restrictions[i + 1][1] + gap);
        }

        // For each adjacent pair, find the peak height between them
        int ans = 0;
        for (int i = 1; i < m; i++) {
            int p1 = restrictions[i - 1][0], h1 = restrictions[i - 1][1];
            int p2 = restrictions[i][0], h2 = restrictions[i][1];
            // Peak = (h1 + h2 + gap) / 2
            int peak = (h1 + h2 + (p2 - p1)) / 2;
            ans = max(ans, peak);
        }

        return ans;
    }
};