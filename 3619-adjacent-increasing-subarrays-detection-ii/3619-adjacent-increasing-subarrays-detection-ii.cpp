class Solution {
public:
    int maxIncreasingSubarrays(vector<int>& nums) {
        int n = nums.size();
        vector<int> incEnd(n, 1);
        for (int i = 1; i < n; ++i) {
            if (nums[i] > nums[i - 1])
                incEnd[i] = incEnd[i - 1] + 1;
            else
                incEnd[i] = 1;
        }
        auto ok = [&](int k) -> bool {
            if (k == 0)
                return true;
            if (2 * k > n)
                return false;
            for (int a = 0; a + 2 * k - 1 < n; ++a) {
                if (incEnd[a + k - 1] >= k && incEnd[a + 2 * k - 1] >= k)
                    return true;
            }
            return false;
        };
        int lo = 0, hi = n / 2;
        while (lo < hi) {
            int mid = (lo + hi + 1) >> 1;
            if (ok(mid))
                lo = mid;
            else
                hi = mid - 1;
        }
        return lo;
    }
};
