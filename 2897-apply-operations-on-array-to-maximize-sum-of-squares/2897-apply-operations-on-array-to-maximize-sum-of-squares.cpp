class Solution {
public:
    int maxSum(vector<int>& nums, int k) {
        const long long MOD = 1000000007LL;
        int cnt[30] = {0};
        for (int x : nums)
            for (int b = 0; b < 30; b++)
                cnt[b] += (x >> b) & 1;

        long long ans = 0;
        for (int i = 0; i < k; i++) {
            long long cur = 0;
            for (int b = 0; b < 30; b++) {
                if (cnt[b] > 0) {
                    cur |= 1LL << b;
                    cnt[b]--;
                }
            }
            if (!cur)
                break;
            cur %= MOD;
            ans = (ans + cur * cur) % MOD;
        }
        return (int)ans;
    }
};