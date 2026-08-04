class Solution {
public:
    vector<int> findMissingElements(vector<int>& nums) {
        int mn = *min_element(nums.begin(), nums.end());
        int mx = *max_element(nums.begin(), nums.end());

        unordered_set<int> present(nums.begin(), nums.end());

        vector<int> result;
        for (int i = mn + 1; i < mx; i++) {
            if (present.find(i) == present.end()) {
                result.push_back(i);
            }
        }

        return result;
    }
};