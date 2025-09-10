class Solution {
public:
    int minimumTeachings(int n, vector<vector<int>>& languages, vector<vector<int>>& friendships) {
        int m = languages.size();
        vector<unordered_set<int>> knows(m + 1);
        for (int i = 0; i < m; i++)
            knows[i + 1] = unordered_set<int>(languages[i].begin(), languages[i].end());

        unordered_set<int> needTeach;
        for (auto &f : friendships) {
            int u = f[0], v = f[1];
            bool ok = false;
            for (int lang : knows[u]) {
                if (knows[v].count(lang)) { ok = true; break; }
            }
            if (!ok) { needTeach.insert(u); needTeach.insert(v); }
        }

        if (needTeach.empty()) return 0;

        vector<int> freq(n + 1, 0);
        for (int user : needTeach)
            for (int lang : knows[user]) freq[lang]++;

        int best = *max_element(freq.begin(), freq.end());
        return (int)needTeach.size() - best;
    }
};
