class Solution {
public:
    int countCommas(int n) {
        int total = 0;

        for (int i = 1; i <= n; i++) {
            int digits = to_string(i).size();
            if (digits > 3) {
                total += (digits - 1) / 3;
            }
        }

        return total;
    }
};