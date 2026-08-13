class Solution {
public:
    vector<int> longestRepeating(string s, string queryCharacters,
                                 vector<int>& queryIndices) {
        int n = s.size();
        int k = queryCharacters.size();

        map<int, int>
            seg; // start -> end (inclusive), representing maximal runs
        multiset<int> lengths;

        // Initialize segments from the original string
        int i = 0;
        while (i < n) {
            int j = i;
            while (j + 1 < n && s[j + 1] == s[i])
                j++;
            seg[i] = j;
            lengths.insert(j - i + 1);
            i = j + 1;
        }

        vector<int> result;
        result.reserve(k);

        for (int q = 0; q < k; q++) {
            int idx = queryIndices[q];
            char c = queryCharacters[q];

            if (s[idx] == c) {
                // no change at all, answer stays the same
                result.push_back(*lengths.rbegin());
                continue;
            }

            // 1. find segment containing idx
            auto it = seg.upper_bound(idx);
            --it;
            int st = it->first, en = it->second;
            seg.erase(it);
            lengths.erase(lengths.find(en - st + 1));

            // 2. split left part
            if (st <= idx - 1) {
                seg[st] = idx - 1;
                lengths.insert(idx - 1 - st + 1);
            }
            // 3. split right part
            if (idx + 1 <= en) {
                seg[idx + 1] = en;
                lengths.insert(en - (idx + 1) + 1);
            }

            int newStart = idx, newEnd = idx;

            // 4. check predecessor (segment ending at idx-1)
            if (idx - 1 >= 0) {
                auto pit = seg.upper_bound(idx - 1);
                if (pit != seg.begin()) {
                    --pit;
                    int pst = pit->first, pen = pit->second;
                    if (pen == idx - 1 && s[pst] == c) {
                        newStart = pst;
                        seg.erase(pit);
                        lengths.erase(lengths.find(pen - pst + 1));
                    }
                }
            }

            // 5. check successor (segment starting at idx+1)
            if (idx + 1 < n) {
                auto sit = seg.upper_bound(idx + 1);
                if (sit != seg.begin()) {
                    --sit;
                    int sst = sit->first, sen = sit->second;
                    if (sst == idx + 1 && s[sst] == c) {
                        newEnd = sen;
                        seg.erase(sit);
                        lengths.erase(lengths.find(sen - sst + 1));
                    }
                }
            }

            // 6. insert merged segment
            seg[newStart] = newEnd;
            lengths.insert(newEnd - newStart + 1);

            // 7. apply the character update
            s[idx] = c;

            result.push_back(*lengths.rbegin());
        }

        return result;
    }
};