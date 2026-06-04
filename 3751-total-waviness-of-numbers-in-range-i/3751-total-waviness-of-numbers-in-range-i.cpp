class Solution {
public:
    int waviness(int n) {
        string s = to_string(n);
        int w = 0;
        for (int i = 1; i + 1 < (int)s.size(); i++) {
            if (s[i] > s[i - 1] && s[i] > s[i + 1])
                w++;
            else if (s[i] < s[i - 1] && s[i] < s[i + 1])
                w++;
        }
        return w;
    }

    int totalWaviness(int num1, int num2) {
        int ans = 0;
        for (int i = num1; i <= num2; i++)
            ans += waviness(i);
        return ans;
    }
};