class Solution {
public:
    int minSwaps(vector<vector<int>>& grid) {
        int n = grid.size();
        vector<int> tz(n);

        // Count trailing zeros
        for (int i = 0; i < n; i++) {
            int count = 0;
            for (int j = n - 1; j >= 0 && grid[i][j] == 0; j--) {
                count++;
            }
            tz[i] = count;
        }

        int swaps = 0;

        for (int i = 0; i < n; i++) {
            int need = n - 1 - i;
            int j = i;
            while (j < n && tz[j] < need)
                j++;

            if (j == n)
                return -1;

            while (j > i) {
                swap(tz[j], tz[j - 1]);
                swaps++;
                j--;
            }
        }
        return swaps;
    }
};