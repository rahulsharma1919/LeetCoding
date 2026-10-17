class Solution {
public:
    int minSwaps(vector<int>& nums) {
        int n = nums.size();
        vector<pair<int, int>> key(n); // {digit sum, value}
        for (int i = 0; i < n; i++) {
            int s = 0;
            for (int x = nums[i]; x; x /= 10)
                s += x % 10;
            key[i] = {s, nums[i]};
        }

        vector<int> idx(n);
        iota(idx.begin(), idx.end(), 0);
        sort(idx.begin(), idx.end(),
             [&](int a, int b) { return key[a] < key[b]; });

        vector<char> vis(n, 0);
        int swaps = 0;
        for (int i = 0; i < n; i++) {
            if (vis[i] || idx[i] == i)
                continue;
            int len = 0;
            for (int j = i; !vis[j]; j = idx[j]) {
                vis[j] = 1;
                len++;
            }
            swaps += len - 1;
        }
        return swaps;
    }
};