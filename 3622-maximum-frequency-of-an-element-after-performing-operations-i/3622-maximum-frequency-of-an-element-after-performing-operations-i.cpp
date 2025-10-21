class Solution {
public:
    int maxFrequency(vector<int>& nums, int k, int numOperations) {
        int maxNum = *max_element(nums.begin(), nums.end());
        int limit = maxNum + k + 2;

        vector<int> prefix(limit, 0);
        for (int v : nums)
            prefix[v]++;

        for (int i = 1; i < limit; ++i)
            prefix[i] += prefix[i - 1];

        int res = 0;
        for (int i = 0; i < limit; ++i) {
            int left = max(0, i - k);
            int right = min(limit - 1, i + k);
            int total = prefix[right] - (left ? prefix[left - 1] : 0);
            int freq = prefix[i] - (i ? prefix[i - 1] : 0);
            res = max(res, freq + min(numOperations, total - freq));
        }
        return res;
    }
};
