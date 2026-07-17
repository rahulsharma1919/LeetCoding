class Solution {
public:
    long long gcdSum(vector<int>& nums) {
        int n = nums.size();
        vector<int> pg(n);
        int mx = 0;
        for (int i = 0; i < n; i++) {
            mx = max(mx, nums[i]);
            pg[i] = __gcd(nums[i], mx);
        }
        sort(pg.begin(), pg.end());
        long long ans = 0;
        int lo = 0, hi = n - 1;
        while (lo < hi)
            ans += __gcd(pg[lo++], pg[hi--]);
        return ans;
    }
};