class Solution {
public:
    int rotatedDigits(int n) {
        int valid[] = {0, 0, 1, -1, -1, 1, 1, -1, 0, 1};

        int ans = 0;
        for (int x = 1; x <= n; x++) {
            int tmp = x;
            bool good = false, bad = false;
            while (tmp) {
                int d = tmp % 10;
                if (valid[d] == -1) {
                    bad = true;
                    break;
                }
                if (valid[d] == 1)
                    good = true;
                tmp /= 10;
            }
            if (!bad && good)
                ans++;
        }
        return ans;
    }
};