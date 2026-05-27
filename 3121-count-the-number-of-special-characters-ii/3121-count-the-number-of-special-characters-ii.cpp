class Solution {
public:
    int numberOfSpecialChars(string word) {
        vector<int> lastLower(26, -1), firstUpper(26, INT_MAX);

        for (int i = 0; i < word.size(); i++) {
            char c = word[i];
            if (islower(c))
                lastLower[c - 'a'] = i;
            else
                firstUpper[c - 'A'] = min(firstUpper[c - 'A'], i);
        }

        int ans = 0;
        for (int i = 0; i < 26; i++)
            if (lastLower[i] != -1 && firstUpper[i] != INT_MAX &&
                lastLower[i] < firstUpper[i])
                ans++;
        return ans;
    }
};