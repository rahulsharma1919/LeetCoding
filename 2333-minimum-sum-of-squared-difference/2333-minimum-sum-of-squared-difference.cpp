class Solution {
public:
    long long minSumSquareDiff(vector<int>& nums1, vector<int>& nums2, int k1,
                               int k2) {
        int n = nums1.size();
        long long k = (long long)k1 + k2;

        vector<long long> cnt(100002, 0);
        long long total = 0;
        for (int i = 0; i < n; i++) {
            int d = abs(nums1[i] - nums2[i]);
            cnt[d]++;
            total += d;
        }

        if (k >= total)
            return 0;

        long long top = 0;
        for (int d = 100000; d >= 1; d--) {
            top += cnt[d];
            if (!top)
                continue;
            if (k >= top) {
                k -= top;
                cnt[d] = 0;
            } else {
                cnt[d] = top - k;
                cnt[d - 1] += k;
                break;
            }
        }

        long long ans = 0;
        for (long long d = 1; d <= 100000; d++)
            ans += cnt[d] * d * d;
        return ans;
    }
};