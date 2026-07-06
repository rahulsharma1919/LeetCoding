class Solution {
public:
    int removeCoveredIntervals(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end(), [](auto& a, auto& b) {
            return a[0] != b[0] ? a[0] < b[0] : a[1] > b[1];
        });

        int ans = 0, maxR = 0;
        for (auto& iv : intervals) {
            if (iv[1] > maxR) {
                ans++;
                maxR = iv[1];
            }
        }
        return ans;
    }
};