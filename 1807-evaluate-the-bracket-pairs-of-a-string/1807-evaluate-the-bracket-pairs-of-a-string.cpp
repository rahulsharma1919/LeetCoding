class Solution {
public:
    string evaluate(string s, vector<vector<string>>& knowledge) {
        unordered_map<string, string> mp;
        mp.reserve(knowledge.size() * 2);
        for (auto& kv : knowledge) {
            mp[kv[0]] = kv[1];
        }

        string result;
        result.reserve(s.size());
        int n = s.size();
        int i = 0;

        while (i < n) {
            if (s[i] == '(') {
                int j = i + 1;
                while (s[j] != ')')
                    j++;
                string key = s.substr(i + 1, j - i - 1);
                auto it = mp.find(key);
                if (it != mp.end())
                    result += it->second;
                else
                    result += '?';
                i = j + 1;
            } else {
                result += s[i];
                i++;
            }
        }

        return result;
    }
};