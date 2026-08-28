class Solution {
public:
    string lexPalindromicPermutation(string s, string target) {
        int n = s.size();
        int freq[26] = {0};
        for (char c : s)
            freq[c - 'a']++;

        int oddCount = 0, oddChar = -1;
        for (int c = 0; c < 26; c++) {
            if (freq[c] % 2 == 1) {
                oddCount++;
                oddChar = c;
            }
        }

        bool needOdd = (n % 2 == 1);
        if (needOdd && oddCount != 1)
            return "";
        if (!needOdd && oddCount != 0)
            return "";

        int halfCnt[26];
        for (int c = 0; c < 26; c++)
            halfCnt[c] = freq[c] / 2;

        int k = n / 2;
        char middleChar = needOdd ? char('a' + oddChar) : 0;

        // Try exact match of first half with target[0..k-1]
        {
            int cnt[26];
            memcpy(cnt, halfCnt, sizeof(halfCnt));
            bool matched = true;
            string firstHalf;
            for (int i = 0; i < k; i++) {
                int t = target[i] - 'a';
                if (cnt[t] > 0) {
                    cnt[t]--;
                    firstHalf.push_back(target[i]);
                } else {
                    matched = false;
                    break;
                }
            }
            if (matched) {
                string T = firstHalf;
                if (needOdd)
                    T.push_back(middleChar);
                string rev = firstHalf;
                reverse(rev.begin(), rev.end());
                T += rev;
                if (T > target)
                    return T;
            }
        }

        // Deviation search
        int cnt[26];
        memcpy(cnt, halfCnt, sizeof(halfCnt));
        int bestI = -1;
        int bestSnapshot[26];

        for (int i = 0; i < k; i++) {
            int t = target[i] - 'a';

            for (int c = t + 1; c < 26; c++) {
                if (cnt[c] > 0) {
                    bestI = i;
                    memcpy(bestSnapshot, cnt, sizeof(cnt));
                    break;
                }
            }

            if (cnt[t] > 0) {
                cnt[t]--;
            } else {
                break;
            }
        }

        if (bestI == -1)
            return "";

        string firstHalf = target.substr(0, bestI);
        int t = target[bestI] - 'a';
        int chosen = -1;
        for (int c = t + 1; c < 26; c++) {
            if (bestSnapshot[c] > 0) {
                chosen = c;
                break;
            }
        }
        bestSnapshot[chosen]--;
        firstHalf.push_back('a' + chosen);

        for (int c = 0; c < 26; c++) {
            for (int j = 0; j < bestSnapshot[c]; j++) {
                firstHalf.push_back('a' + c);
            }
        }

        string T = firstHalf;
        if (needOdd)
            T.push_back(middleChar);
        string rev = firstHalf;
        reverse(rev.begin(), rev.end());
        T += rev;

        return T;
    }
};