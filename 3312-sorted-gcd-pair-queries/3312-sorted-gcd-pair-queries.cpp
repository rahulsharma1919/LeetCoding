class Solution {
public:
    vector<int> gcdValues(vector<int>& nums, vector<long long>& queries) {
        int M = *max_element(nums.begin(), nums.end());

        vector<long long> freq(M + 1, 0);
        for (int x : nums)
            freq[x]++;

        vector<long long> cnt(M + 1, 0);
        for (int g = 1; g <= M; g++)
            for (int mul = g; mul <= M; mul += g)
                cnt[g] += freq[mul];

        vector<long long> pairs(M + 1, 0);
        for (int g = M; g >= 1; g--) {
            pairs[g] = cnt[g] * (cnt[g] - 1) / 2;
            for (int mul = 2 * g; mul <= M; mul += g)
                pairs[g] -= pairs[mul];
        }

        // prefix[g] = number of gcd pairs with value <= g
        vector<long long> prefix(M + 2, 0);
        for (int g = 1; g <= M; g++)
            prefix[g] = prefix[g - 1] + pairs[g];

        vector<int> ans;
        for (long long q : queries) {
            // find smallest g where prefix[g] > q
            int lo = 1, hi = M;
            while (lo < hi) {
                int mid = (lo + hi) / 2;
                if (prefix[mid] > q)
                    hi = mid;
                else
                    lo = mid + 1;
            }
            ans.push_back(lo);
        }
        return ans;
    }
};