class Solution {
public:
    int countMajoritySubarrays(vector<int>& nums, int target) {
        int n = nums.size(), ans = 0;
        for (int i = 0; i < n; i++) {
            int bal = 0;
            for (int j = i; j < n; j++) {
                bal += (nums[j] == target) ? 1 : -1;
                if (bal > 0)
                    ans++;
            }
        }
        return ans;
    }
};