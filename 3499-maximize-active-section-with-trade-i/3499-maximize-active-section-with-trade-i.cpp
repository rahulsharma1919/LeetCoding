class Solution {
public:
    int maxActiveSectionsAfterTrade(string s) {
        int total1 = count(s.begin(), s.end(), '1');
        string t = "1" + s + "1";
        int m = t.size();

        vector<pair<char, int>> blocks;
        int i = 0;
        while (i < m) {
            char c = t[i];
            int len = 0;
            while (i < m && t[i] == c) {
                len++;
                i++;
            }
            blocks.push_back({c, len});
        }

        int B = blocks.size();
        int best = 0;

        for (int j = 1; j + 1 < B; j++) {
            if (blocks[j].first == '1') {
                int net = blocks[j - 1].second + blocks[j + 1].second;
                best = max(best, net);
            }
        }

        return total1 + max(0, best);
    }
};