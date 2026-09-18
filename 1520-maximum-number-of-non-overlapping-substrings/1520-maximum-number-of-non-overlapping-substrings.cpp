class Solution {
public:
    vector<string> maxNumOfSubstrings(string s) {
        int n = s.size();
        vector<int> first(26, -1), last(26, -1);

        for (int i = 0; i < n; i++) {
            int c = s[i] - 'a';
            if (first[c] == -1)
                first[c] = i;
            last[c] = i;
        }

        vector<pair<int, int>> intervals; // {start, end}

        for (int i = 0; i < n; i++) {
            int c = s[i] - 'a';
            if (first[c] != i)
                continue; // only start candidates at first occurrence

            int start = i;
            int end = last[c];
            bool valid = true;

            int j = start;
            while (j <= end) {
                int cj = s[j] - 'a';
                if (first[cj] < start) {
                    valid = false;
                    break;
                }
                end = max(end, last[cj]);
                j++;
            }

            if (valid) {
                intervals.push_back({start, end});
            }
        }

        // sort by end ascending; tie-break by start descending (prefer narrower
        // intervals)
        sort(intervals.begin(), intervals.end(),
             [](const pair<int, int>& a, const pair<int, int>& b) {
                 if (a.second != b.second)
                     return a.second < b.second;
                 return a.first > b.first;
             });

        vector<string> result;
        int lastEnd = -1;

        for (auto& [st, en] : intervals) {
            if (st > lastEnd) {
                result.push_back(s.substr(st, en - st + 1));
                lastEnd = en;
            }
        }

        return result;
    }
};