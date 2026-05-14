class Solution {
public:
    int minMoves(vector<int>& nums, int limit) {
        int n = nums.size();
        vector<int> diff(2 * limit + 2, 0);

        for (int i = 0; i < n / 2; i++) {
            int a = nums[i], b = nums[n - 1 - i];
            int lo = min(a, b) + 1;
            int hi = max(a, b) + limit;
            int exact = a + b;

            diff[2] += 2;
            diff[lo] -= 1;
            diff[exact] -= 1;
            diff[exact + 1] += 1;
            diff[hi + 1] += 1;
        }

        int ans = INT_MAX, cur = 0;
        for (int t = 2; t <= 2 * limit; t++) {
            cur += diff[t];
            ans = min(ans, cur);
        }
        return ans;
    }
};