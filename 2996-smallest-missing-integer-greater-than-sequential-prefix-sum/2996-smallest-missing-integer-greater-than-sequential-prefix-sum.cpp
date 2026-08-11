class Solution {
public:
    int missingInteger(vector<int>& nums) {
        int n = nums.size();

        int i = 0;
        int sum = nums[0];
        while (i + 1 < n && nums[i + 1] == nums[i] + 1) {
            i++;
            sum += nums[i];
        }
        unordered_set<int> present(nums.begin(), nums.end());
        while (present.count(sum)) {
            sum++;
        }
        return sum;
    }
};