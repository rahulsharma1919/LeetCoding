class Solution {
public:
    int reverseDegree(string s) {
        int n = s.size();
        long long total = 0;

        for (int i = 0; i < n; i++) {
            int revAlphaPos = 26 - (s[i] - 'a');
            int stringPos = i + 1;
            total += (long long)revAlphaPos * stringPos;
        }

        return (int)total;
    }
};