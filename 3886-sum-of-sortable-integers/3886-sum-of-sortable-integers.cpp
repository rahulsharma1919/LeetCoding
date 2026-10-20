class Solution {
public:
    int sortableIntegers(vector<int>& nums) {
        int n = nums.size();

        int total = 0;
        vector<char> bad(n, 0);
        for (int i = 0; i + 1 < n; i++) {
            if (nums[i] > nums[i + 1]) {
                bad[i] = 1;
                total++;
            }
        }
        if (total == 0) {
            int sum = 0;
            for (int k = 1; k <= n; k++)
                if (n % k == 0)
                    sum += k;
            return sum;
        }

        int ans = 0;
        for (int k = 1; k <= n; k++) {
            if (n % k)
                continue;

            int inner = 0;
            bool ok = true;
            int firstElemOfMax = 0;

            for (int s = 0; s < n && ok; s += k) {
                int d = 0;
                for (int i = s; i + 1 < s + k; i++)
                    d += bad[i];
                if (d > 1)
                    ok = false;
                else if (d == 1 && nums[s + k - 1] > nums[s])
                    ok = false;
                inner += d;
                (void)firstElemOfMax;
            }
            if (!ok)
                continue;

            int prevMax = 0;
            for (int s = 0; s < n && ok; s += k) {
                int bmin, bmax;
                int pos = -1;
                for (int i = s; i + 1 < s + k; i++)
                    if (bad[i]) {
                        pos = i;
                        break;
                    }
                if (pos == -1) {
                    bmin = nums[s];
                    bmax = nums[s + k - 1];
                } else {
                    bmin = nums[pos + 1];
                    bmax = nums[pos];
                }
                if (bmin < prevMax)
                    ok = false;
                prevMax = bmax;
            }
            if (ok)
                ans += k;
        }
        return ans;
    }
};