class Solution {
public:
    int specialTriplets(vector<int>& nums) {
        const int MOD = 1e9 + 7;

        unordered_map<int, long long> left, right;
        for (int x : nums) right[x]++;

        long long ans = 0;

        for (int j = 0; j < nums.size(); j++) {
            // current element moves from right to left
            right[nums[j]]--;

            long long target = 2LL * nums[j];

            if (left.count(target) && right.count(target)) {
                ans = (ans + left[target] * right[target]) % MOD;
            }

            left[nums[j]]++;
        }

        return (int)ans;
    }
};
