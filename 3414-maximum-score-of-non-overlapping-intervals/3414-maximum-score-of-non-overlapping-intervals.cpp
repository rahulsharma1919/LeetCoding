class Solution {
public:
    vector<int> maximumWeight(vector<vector<int>>& intervals) {
        int n = intervals.size();
        // sorted by right endpoint; store {l, r, w, originalIndex}
        vector<array<long long, 4>> arr(n);
        for (int i = 0; i < n; i++) {
            arr[i] = {intervals[i][0], intervals[i][1], intervals[i][2], i};
        }
        sort(arr.begin(), arr.end(),
             [](const array<long long, 4>& a, const array<long long, 4>& b) {
                 return a[1] < b[1];
             });

        vector<long long> rVals(n);
        for (int i = 0; i < n; i++)
            rVals[i] = arr[i][1];

        // bestPrev(i) (1-indexed interval i, i.e., arr[i-1]) = count of
        // intervals with r < l[i]
        auto bestPrev = [&](long long l) -> int {
            // find first index with rVals[idx] >= l; count before that = answer
            int lo = 0, hi = n;
            while (lo < hi) {
                int mid = (lo + hi) / 2;
                if (rVals[mid] >= l)
                    hi = mid;
                else
                    lo = mid + 1;
            }
            return lo; // number of intervals with r < l
        };

        const int K = 4;
        // dp[i][k] = {score, sorted list of original indices}
        vector<vector<long long>> dpScore(n + 1, vector<long long>(K + 1, 0));
        vector<vector<vector<int>>> dpList(n + 1, vector<vector<int>>(K + 1));

        auto lexSmaller = [](const vector<int>& a,
                             const vector<int>& b) -> bool {
            int m = min(a.size(), b.size());
            for (int i = 0; i < m; i++) {
                if (a[i] != b[i])
                    return a[i] < b[i];
            }
            return a.size() < b.size();
        };

        auto insertSorted = [](vector<int> lst, int val) -> vector<int> {
            lst.push_back(val);
            sort(lst.begin(), lst.end());
            return lst;
        };

        for (int i = 1; i <= n; i++) {
            long long l = arr[i - 1][0];
            long long w = arr[i - 1][2];
            int origIdx = (int)arr[i - 1][3];
            int p = bestPrev(l);

            for (int k = 0; k <= K; k++) {
                // option A: skip interval i
                long long scoreA = dpScore[i - 1][k];
                vector<int> listA = dpList[i - 1][k];

                if (k == 0) {
                    dpScore[i][k] = scoreA;
                    dpList[i][k] = listA;
                    continue;
                }

                // option B: take interval i
                long long scoreB = w + dpScore[p][k - 1];
                vector<int> listB = insertSorted(dpList[p][k - 1], origIdx);

                if (scoreB > scoreA) {
                    dpScore[i][k] = scoreB;
                    dpList[i][k] = listB;
                } else if (scoreB < scoreA) {
                    dpScore[i][k] = scoreA;
                    dpList[i][k] = listA;
                } else {
                    dpScore[i][k] = scoreA;
                    dpList[i][k] = lexSmaller(listA, listB) ? listA : listB;
                }
            }
        }

        return dpList[n][K];
    }
};