class Solution {
public:
    int numberOfBeams(vector<string>& bank) {
        int prev = 0, total = 0;
        for (auto& row : bank) {
            int count = count_if(row.begin(), row.end(),
                                 [](char c) { return c == '1'; });
            if (count > 0) {
                total += prev * count;
                prev = count;
            }
        }
        return total;
    }
};
