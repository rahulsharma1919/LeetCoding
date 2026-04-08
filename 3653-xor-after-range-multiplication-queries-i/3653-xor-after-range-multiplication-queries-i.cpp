class Solution {
public:
    int xorAfterQueries(vector<int>& nums, vector<vector<int>>& queries) {
        const long long MOD = 1e9 + 7;

        for (auto& q : queries)
            for (int idx = q[0]; idx <= q[1]; idx += q[2])
                nums[idx] = (1LL * nums[idx] * q[3]) % MOD;

        int ans = 0;
        for (int v : nums)
            ans ^= v;
        return ans;
    }
};