class Solution {
public:
    int earliestFinishTime(vector<int>& landStartTime,
                           vector<int>& landDuration,
                           vector<int>& waterStartTime,
                           vector<int>& waterDuration) {
        int ans = INT_MAX;
        int n = landStartTime.size(), m = waterStartTime.size();

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                int landEnd = landStartTime[i] + landDuration[i];
                int waterEnd = waterStartTime[j] + waterDuration[j];

                int lwFinish =
                    max(landEnd, waterStartTime[j]) + waterDuration[j];
                int wlFinish =
                    max(waterEnd, landStartTime[i]) + landDuration[i];

                ans = min(ans, min(lwFinish, wlFinish));
            }
        }

        return ans;
    }
};