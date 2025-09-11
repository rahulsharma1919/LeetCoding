class Solution {
public:
    string sortVowels(string s) {
        auto isVowel = [](char c) {
            c = tolower(c);
            return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
        };

        vector<char> vowels;
        for (char c : s) {
            if (isVowel(c)) vowels.push_back(c);
        }

        sort(vowels.begin(), vowels.end());

        int j = 0;
        for (int i = 0; i < s.size(); i++) {
            if (isVowel(s[i])) {
                s[i] = vowels[j++];
            }
        }

        return s;
    }
};
