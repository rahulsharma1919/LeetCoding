class Solution {
public:
    vector<int> pathExistenceQueries(int n, vector<int>& nums, int maxDiff,
                                     vector<vector<int>>& queries) {
        vector<int> idx(n);
        iota(idx.begin(), idx.end(), 0);
        sort(idx.begin(), idx.end(),
             [&](int a, int b) { return nums[a] < nums[b]; });

        vector<int> rnk(n), snum(n);
        for (int i = 0; i < n; i++) {
            rnk[idx[i]] = i;
            snum[i] = nums[idx[i]];
        }

        const int LOG = 17;
        vector<vector<int>> up(LOG, vector<int>(n));

        for (int i = 0, j = 0; i < n; i++) {
            if (j < i)
                j = i;
            while (j + 1 < n && snum[j + 1] - snum[i] <= maxDiff)
                j++;
            up[0][i] = j;
        }

        for (int k = 1; k < LOG; k++)
            for (int i = 0; i < n; i++)
                up[k][i] = up[k - 1][up[k - 1][i]];

        vector<int> ans;
        ans.reserve(queries.size());

        for (auto& q : queries) {
            int u = q[0], v = q[1];
            if (u == v) {
                ans.push_back(0);
                continue;
            }

            int pu = rnk[u], pv = rnk[v];
            if (pu > pv)
                swap(pu, pv);

            int pos = pu, dist = 0;
            for (int k = LOG - 1; k >= 0; k--) {
                if (up[k][pos] < pv) {
                    pos = up[k][pos];
                    dist += (1 << k);
                }
            }

            if (up[0][pos] >= pv)
                dist++;
            else {
                ans.push_back(-1);
                continue;
            }

            ans.push_back(dist);
        }
        return ans;
    }
};