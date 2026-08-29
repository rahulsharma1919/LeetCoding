class Solution {
public:
    vector<int> lexicographicallySmallestArray(vector<int>& nums, int limit) {
        int n = nums.size();

        vector<int> idx(n);
        for (int i = 0; i < n; i++)
            idx[i] = i;
        sort(idx.begin(), idx.end(),
             [&](int a, int b) { return nums[a] < nums[b]; });

        vector<int> result(n);
        int i = 0;

        while (i < n) {
            int j = i;
            while (j + 1 < n && nums[idx[j + 1]] - nums[idx[j]] <= limit) {
                j++;
            }
            vector<int> groupIndices;
            for (int k = i; k <= j; k++)
                groupIndices.push_back(idx[k]);
            sort(groupIndices.begin(), groupIndices.end());

            for (int k = 0; k <= j - i; k++) {
                result[groupIndices[k]] = nums[idx[i + k]];
            }

            i = j + 1;
        }

        return result;
    }
};