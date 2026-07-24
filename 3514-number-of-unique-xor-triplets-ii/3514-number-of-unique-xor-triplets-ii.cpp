class Solution {
public:
    int uniqueXorTriplets(vector<int>& nums) {
        int n = nums.size();
        const int MAXV = 4096;

        bitset<4096> pairs, result;

        for (int i = 0; i < n; i++)
            for (int j = i; j < n; j++)
                pairs.set(nums[i] ^ nums[j]);

        for (int k = 0; k < n; k++) {
            int v = nums[k];
            for (int p = 0; p < MAXV; p++)
                if (pairs[p])
                    result.set(p ^ v);
        }

        return result.count();
    }
};