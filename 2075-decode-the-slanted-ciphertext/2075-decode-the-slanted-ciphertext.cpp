class Solution {
public:
    string decodeCiphertext(string encodedText, int rows) {
        if (rows == 1 || encodedText.empty())
            return encodedText;

        int cols = encodedText.size() / rows;
        string ans;

        for (int c = 0; c < cols; c++) {
            int r = 0, col = c;
            while (r < rows && col < cols) {
                ans += encodedText[r * cols + col];
                r++;
                col++;
            }
        }

        while (!ans.empty() && ans.back() == ' ')
            ans.pop_back();
        return ans;
    }
};