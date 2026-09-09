class Solution {
public:
    long long countCommas(long long n) {
        long long total = 0;

        for (long long c = 1;; c++) {
            long long threshold = 1;
            bool overflow = false;
            for (int k = 0; k < 3 * c; k++) {
                if (threshold > n) {
                    overflow = true;
                    break;
                }
                threshold *= 10;
                if (threshold > (long long)2e18) {
                    overflow = true;
                    break;
                }
            }

            if (overflow || threshold > n)
                break;

            long long countAtLeastC = n - threshold + 1;
            total += countAtLeastC;
        }

        return total;
    }
};