class Solution {
public:
    int minOperations(vector<int>& nums, int x) {
        int n = nums.size();
        long long totalSum = 0;
        for (int v : nums)
            totalSum += v;

        long long target = totalSum - x;

        if (target < 0)
            return -1;
        if (target == 0)
            return n;

        int left = 0;
        long long windowSum = 0;
        int maxLen = -1;

        for (int right = 0; right < n; right++) {
            windowSum += nums[right];

            while (windowSum > target && left <= right) {
                windowSum -= nums[left];
                left++;
            }

            if (windowSum == target) {
                maxLen = max(maxLen, right - left + 1);
            }
        }

        return maxLen == -1 ? -1 : n - maxLen;
    }
};