class Solution {
public:
    int maxDistinctElements(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());
        long long last = LLONG_MIN;
        int distinct = 0;

        for (long long num : nums) {
            long long low = num - k;
            long long high = num + k;
            long long chosen = max(low, last + 1);

            if (chosen <= high) {
                distinct++;
                last = chosen;
            }
        }
        return distinct;
    }
};
