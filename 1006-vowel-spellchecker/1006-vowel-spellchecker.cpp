class Solution {
public:
    string maskVowels(string word) {
        string res;
        for (char c : word) {
            char lower = tolower(c);
            if (lower == 'a' || lower == 'e' || lower == 'i' || lower == 'o' || lower == 'u')
                res += '*';   // replace all vowels with '*'
            else
                res += lower;
        }
        return res;
    }

    vector<string> spellchecker(vector<string>& wordlist, vector<string>& queries) {
        unordered_set<string> exact(wordlist.begin(), wordlist.end());
        unordered_map<string, string> caseMap;
        unordered_map<string, string> vowelMap;

        for (string &w : wordlist) {
            string lower = w;
            for (char &c : lower) c = tolower(c);

            // Only keep first occurrence for precedence
            if (!caseMap.count(lower)) caseMap[lower] = w;
            string masked = maskVowels(lower);
            if (!vowelMap.count(masked)) vowelMap[masked] = w;
        }

        vector<string> ans;
        for (string &q : queries) {
            if (exact.count(q)) {
                ans.push_back(q);
                continue;
            }
            string lower = q;
            for (char &c : lower) c = tolower(c);

            if (caseMap.count(lower)) {
                ans.push_back(caseMap[lower]);
                continue;
            }
            string masked = maskVowels(lower);
            if (vowelMap.count(masked)) {
                ans.push_back(vowelMap[masked]);
                continue;
            }
            ans.push_back("");
        }
        return ans;
    }
};
