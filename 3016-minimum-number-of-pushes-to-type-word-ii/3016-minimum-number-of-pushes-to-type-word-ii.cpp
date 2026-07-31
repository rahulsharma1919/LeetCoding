class Solution {
public:
    int minimumPushes(string word) {
        int freq[26] = {};
        for (char c : word)
            freq[c - 'a']++;
        vector<int> f(freq, freq + 26);
        sort(f.rbegin(), f.rend());
        int ans = 0;
        for (int i = 0; i < 26; i++)
            ans += f[i] * (i / 8 + 1);
        return ans;
    }
};