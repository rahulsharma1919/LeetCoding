class Solution {
public:
    vector<int> findDiagonalOrder(vector<vector<int>>& mat) {
        int m = mat.size();
        int n = mat[0].size();
        vector<int> result;
        result.reserve(m * n);

        for (int d = 0; d < m + n - 1; d++) {
            vector<int> temp;

            int r = max(0, d - n + 1);
            int c = min(d, n - 1);

            while (r < m && c >= 0) {
                temp.push_back(mat[r][c]);
                r++;
                c--;
            }

            if (d % 2 == 0) {
                reverse(temp.begin(), temp.end());
            }

            result.insert(result.end(), temp.begin(), temp.end());
        }

        return result;
    }
};
