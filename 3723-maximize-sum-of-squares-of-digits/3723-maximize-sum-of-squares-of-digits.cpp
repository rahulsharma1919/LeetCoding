class Solution {
public:
    string maxSumOfSquares(int num, int sum) {
        if (sum > 9 * num)
            return "";
        string s(num, '0');
        for (int i = 0; i < num && sum > 0; i++) {
            int d = min(9, sum);
            s[i] = '0' + d;
            sum -= d;
        }
        return s;
    }
};