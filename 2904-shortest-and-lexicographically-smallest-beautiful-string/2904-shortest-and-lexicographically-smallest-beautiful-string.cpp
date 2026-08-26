class Solution {
public:
    string shortestBeautifulSubstring(string s, int k) {
        int n = s.size();
        int minLen = INT_MAX;
        string best = "";

        for (int i = 0; i < n; i++) {
            int ones = 0;
            for (int j = i; j < n; j++) {
                if (s[j] == '1')
                    ones++;
                if (ones == k) {
                    int len = j - i + 1;
                    string candidate = s.substr(i, len);
                    if (len < minLen) {
                        minLen = len;
                        best = candidate;
                    } else if (len == minLen && candidate < best) {
                        best = candidate;
                    }
                    break; 
                }
            }
        }

        return best;
    }
};