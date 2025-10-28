class Solution {
public:
    int countValidSelections(vector<int>& nums) {
        int total = accumulate(nums.begin(), nums.end(), 0);
        int left_sum = 0, ans = 0;

        for (int i = 0; i < nums.size(); ++i) {
            total -= nums[i];
            if (nums[i] == 0) {
                if (left_sum == total)
                    ans += 2;
                else if (abs(left_sum - total) == 1)
                    ans += 1;
            }
            left_sum += nums[i];
        }
        return ans;
    }
};
