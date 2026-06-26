class Solution {
public:
    long long countMajoritySubarrays(vector<int>& nums, int target) {
        int n = nums.size();
        vector<int> bit(2 * n + 2, 0);

        auto update = [&](int i) {
            for (i++; i < (int)bit.size(); i += i & (-i))
                bit[i]++;
        };
        auto query = [&](int i) {
            int s = 0;
            for (i++; i > 0; i -= i & (-i))
                s += bit[i];
            return s;
        };

        update(n);

        long long ans = 0;
        int bal = 0;

        for (int i = 0; i < n; i++) {
            bal += (nums[i] == target) ? 1 : -1;
            int cur = bal + n;
            if (cur > 0)
                ans += query(cur - 1);
            update(cur);
        }

        return ans;
    }
};