class Solution {
public:
    vector<string> twoEditWords(vector<string>& queries,
                                vector<string>& dictionary) {
        vector<string> ans;
        for (auto& q : queries)
            for (auto& d : dictionary) {
                int diff = 0;
                for (int i = 0; i < q.size(); i++)
                    diff += q[i] != d[i];
                if (diff <= 2) {
                    ans.push_back(q);
                    break;
                }
            }
        return ans;
    }
};