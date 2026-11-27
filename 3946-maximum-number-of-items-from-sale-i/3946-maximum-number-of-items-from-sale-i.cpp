
class Solution {
public:
    int maximumSaleItems(vector<vector<int>>& items, int budget) {
        int n = items.size();
        vector<int> freeItems(n, 0);

        // Calculate free items received from buying each item type.
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i != j && items[j][0] % items[i][0] == 0) {
                    freeItems[i]++;
                }
            }
        }

        const int NEG = -1000000000;

        // dp[b] = maximum items using exactly b money.
        vector<int> dp(budget + 1, NEG);
        dp[0] = 0;

        for (int i = 0; i < n; i++) {
            int price = items[i][1];
            int bonus = freeItems[i];

            vector<int> ndp = dp;

            // Process each remainder modulo price.
            for (int r = 0; r < price && r <= budget; r++) {
                int best = NEG;

                for (int b = r + price; b <= budget; b += price) {
                    int m = (b - r) / price;

                    if (dp[b - price] != NEG) {
                        best = max(best, dp[b - price] - (m - 1));
                    }

                    if (best != NEG) {
                        ndp[b] = max(ndp[b], best + m + bonus);
                    }
                }
            }

            dp = ndp;
        }

        return *max_element(dp.begin(), dp.end());
    }
};
