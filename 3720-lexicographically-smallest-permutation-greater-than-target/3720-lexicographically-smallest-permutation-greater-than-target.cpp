class Solution {
public:
    string lexGreaterPermutation(string s, string target) {
        int n = s.size();
        int freq[26] = {0};
        for (char c : s)
            freq[c - 'a']++;

        int cnt[26];
        memcpy(cnt, freq, sizeof(freq));

        int bestI = -1;
        int bestCntSnapshot[26];

        for (int i = 0; i < n; i++) {
            int t = target[i] - 'a';

            for (int c = t + 1; c < 26; c++) {
                if (cnt[c] > 0) {
                    bestI = i;
                    memcpy(bestCntSnapshot, cnt, sizeof(cnt));
                    break;
                }
            }

            if (cnt[t] > 0) {
                cnt[t]--;
            } else {
                break; // can't match target[i] exactly, stop advancing
            }
        }

        if (bestI == -1)
            return "";

        string result = target.substr(0, bestI);

        int t = target[bestI] - 'a';
        int chosen = -1;
        for (int c = t + 1; c < 26; c++) {
            if (bestCntSnapshot[c] > 0) {
                chosen = c;
                break;
            }
        }

        bestCntSnapshot[chosen]--;
        result.push_back('a' + chosen);

        for (int c = 0; c < 26; c++) {
            for (int j = 0; j < bestCntSnapshot[c]; j++) {
                result.push_back('a' + c);
            }
        }

        return result;
    }
};