class Solution {
public:
    int longestBalanced(string s) {
        int n = s.size();
        int ans = 1;

        for (int l = 0; l < n; l++) {
            vector<int> cnt(26, 0);
            for (int r = l; r < n; r++) {
                cnt[s[r] - 'a']++;

                int freq = 0;
                bool ok = true;
                for (int c = 0; c < 26; c++) {
                    if (cnt[c] == 0)
                        continue;
                    if (freq == 0)
                        freq = cnt[c];
                    else if (cnt[c] != freq) {
                        ok = false;
                        break;
                    }
                }

                if (ok) {
                    ans = max(ans, r - l + 1);
                }
            }
        }
        return ans;
    }
};
