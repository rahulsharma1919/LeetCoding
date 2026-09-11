class Solution {
public:
    int totalNumbers(vector<int>& digits) {
        set<int> results;
        int n = digits.size();

        vector<int> sorted_digits = digits;
        sort(sorted_digits.begin(), sorted_digits.end());

        for (int i = 0; i < n; i++) {
            if (sorted_digits[i] == 0)
                continue; // no leading zero
            for (int j = 0; j < n; j++) {
                if (j == i)
                    continue;
                for (int k = 0; k < n; k++) {
                    if (k == i || k == j)
                        continue;
                    if (sorted_digits[k] % 2 != 0)
                        continue; // must be even

                    int num = sorted_digits[i] * 100 + sorted_digits[j] * 10 +
                              sorted_digits[k];
                    results.insert(num);
                }
            }
        }

        return results.size();
    }
};