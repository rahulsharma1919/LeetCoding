class Solution {
public:
    vector<int> arrayRankTransform(vector<int>& arr) {
        vector<int> sorted = arr;
        sort(sorted.begin(), sorted.end());
        sorted.erase(unique(sorted.begin(), sorted.end()), sorted.end());
        unordered_map<int, int> rank;
        for (int i = 0; i < sorted.size(); i++)
            rank[sorted[i]] = i + 1;
        for (int& x : arr)
            x = rank[x];
        return arr;
    }
};