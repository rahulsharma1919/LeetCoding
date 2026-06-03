class Solution {
public:
    int earliestFinishTime(vector<int>& ls, vector<int>& ld, vector<int>& ws,
                           vector<int>& wd) {
        int n = ls.size(), m = ws.size();
        int ans = INT_MAX;

        vector<pair<int, int>> land(n), water(m);
        for (int i = 0; i < n; i++)
            land[i] = {ls[i], ld[i]};
        for (int j = 0; j < m; j++)
            water[j] = {ws[j], wd[j]};

        sort(land.begin(), land.end());
        sort(water.begin(), water.end());

        vector<int> suffMin(m + 1, INT_MAX);
        for (int j = m - 1; j >= 0; j--)
            suffMin[j] = min(suffMin[j + 1], water[j].first + water[j].second);

        vector<int> prefMinDur(m + 1, INT_MAX);
        for (int j = 0; j < m; j++)
            prefMinDur[j + 1] = min(prefMinDur[j], water[j].second);

        for (int i = 0; i < n; i++) {
            int landEnd = land[i].first + land[i].second;
            int lo = (int)(lower_bound(water.begin(), water.end(),
                                       make_pair(landEnd, INT_MIN)) -
                           water.begin());
            if (lo < m)
                ans = min(ans, suffMin[lo]);
            if (lo > 0 && prefMinDur[lo] != INT_MAX)
                ans = min(ans, landEnd + prefMinDur[lo]);
        }

        vector<int> suffMinL(n + 1, INT_MAX);
        for (int i = n - 1; i >= 0; i--)
            suffMinL[i] = min(suffMinL[i + 1], land[i].first + land[i].second);

        vector<int> prefMinDurL(n + 1, INT_MAX);
        for (int i = 0; i < n; i++)
            prefMinDurL[i + 1] = min(prefMinDurL[i], land[i].second);

        for (int j = 0; j < m; j++) {
            int waterEnd = water[j].first + water[j].second;
            int lo = (int)(lower_bound(land.begin(), land.end(),
                                       make_pair(waterEnd, INT_MIN)) -
                           land.begin());
            if (lo < n)
                ans = min(ans, suffMinL[lo]);
            if (lo > 0 && prefMinDurL[lo] != INT_MAX)
                ans = min(ans, waterEnd + prefMinDurL[lo]);
        }

        return ans;
    }
};