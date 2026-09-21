class Solution {
public:
    vector<long long> resultArray(vector<int>& nums, int k) {
        int n = nums.size();
        vector<long long> result(k, 0);
        vector<long long> cnt(k, 0);

        for (int j = 0; j < n; j++) {
            int m = nums[j] % k;
            vector<long long> newCnt(k, 0);

            for (int r = 0; r < k; r++) {
                if (cnt[r] == 0)
                    continue;
                int nr = (r * m) % k;
                newCnt[nr] += cnt[r];
            }

            newCnt[m] += 1; // the subarray consisting of just nums[j] alone

            cnt = newCnt;

            for (int x = 0; x < k; x++) {
                result[x] += cnt[x];
            }
        }

        return result;
    }
};