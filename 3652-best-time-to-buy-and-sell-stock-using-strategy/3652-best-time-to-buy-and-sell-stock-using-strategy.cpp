class Solution {
public:
    long long maxProfit(vector<int>& prices, vector<int>& strategy, int k) {
        int n = prices.size();
        int half = k / 2;

        long long baseProfit = 0;
        for (int i = 0; i < n; i++) {
            baseProfit += 1LL * strategy[i] * prices[i];
        }

        vector<long long> prefPrice(n + 1, 0), prefStr(n + 1, 0);
        for (int i = 0; i < n; i++) {
            prefPrice[i + 1] = prefPrice[i] + prices[i];
            prefStr[i + 1] = prefStr[i] + 1LL * strategy[i] * prices[i];
        }

        long long bestGain = 0;

        for (int l = 0; l + k <= n; l++) {
            int mid = l + half;
            int r = l + k;

            long long oldFirst = prefStr[mid] - prefStr[l];
            long long oldSecond = prefStr[r] - prefStr[mid];
            long long newSecond = prefPrice[r] - prefPrice[mid];

            long long gain = -oldFirst - oldSecond + newSecond;
            bestGain = max(bestGain, gain);
        }

        return baseProfit + bestGain;
    }
};
