class Solution {
public:
    int longestBalanced(vector<int>& nums) {
        int n = nums.size();
        int ans = 0;

        for (int l = 0; l < n; l++) {
            unordered_set<int> evenSet, oddSet;
            for (int r = l; r < n; r++) {
                if (nums[r] % 2 == 0)
                    evenSet.insert(nums[r]);
                else
                    oddSet.insert(nums[r]);

                if (evenSet.size() == oddSet.size()) {
                    ans = max(ans, r - l + 1);
                }
            }
        }
        return ans;
    }
};
