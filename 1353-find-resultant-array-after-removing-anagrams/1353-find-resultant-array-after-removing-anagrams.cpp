class Solution {
public:
    vector<string> removeAnagrams(vector<string>& words) {
        vector<string> res;
        string prev = "";
        for (auto& w : words) {
            string sortedWord = w;
            sort(sortedWord.begin(), sortedWord.end());
            if (sortedWord != prev) {
                res.push_back(w);
                prev = sortedWord;
            }
        }
        return res;
    }
};
