class Solution {
public:
    vector<int> maxActiveSectionsAfterTrade(string s,
                                            vector<vector<int>>& queries) {
        int n = s.size();
        vector<int> pre(n + 1, 0);
        for (int i = 0; i < n; i++)
            pre[i + 1] = pre[i] + (s[i] == '1');
        int total1 = pre[n];

        vector<array<int, 3>> blk;
        for (int i = 0; i < n;) {
            int j = i;
            while (j < n && s[j] == s[i])
                j++;
            blk.push_back({s[i] - '0', i, j - 1});
            i = j;
        }
        int B = blk.size();

        struct Trip {
            int lz, rz, lS, rE, oS, oE;
        };
        vector<Trip> trips;
        for (int j = 1; j + 1 < B; j++)
            if (blk[j][0] == 1)
                trips.push_back({blk[j - 1][2] - blk[j - 1][1] + 1,
                                 blk[j + 1][2] - blk[j + 1][1] + 1,
                                 blk[j - 1][1], blk[j + 1][2], blk[j][1],
                                 blk[j][2]});
        int TN = trips.size();

        vector<int> byLS(TN);
        iota(byLS.begin(), byLS.end(), 0);
        sort(byLS.begin(), byLS.end(),
             [&](int a, int b) { return trips[a].lS > trips[b].lS; });

        vector<int> rEv;
        for (auto& t : trips)
            rEv.push_back(t.rE);
        sort(rEv.begin(), rEv.end());
        rEv.erase(unique(rEv.begin(), rEv.end()), rEv.end());
        int RS = rEv.size();
        auto idxRE = [&](int v) {
            return (int)(lower_bound(rEv.begin(), rEv.end(), v) - rEv.begin());
        };

        vector<int> bitA(RS + 2, 0);
        auto updA = [&](int i, int v) {
            for (i++; i <= RS; i += i & -i)
                bitA[i] = max(bitA[i], v);
        };
        auto qryA = [&](int i) -> int {
            int r = 0;
            for (i++; i > 0; i -= i & -i)
                r = max(r, bitA[i]);
            return r;
        };

        int Q = queries.size();
        vector<int> qord(Q);
        iota(qord.begin(), qord.end(), 0);
        sort(qord.begin(), qord.end(),
             [&](int a, int b) { return queries[a][0] > queries[b][0]; });

        vector<int> ans(Q);
        int tp = 0;

        for (int qi : qord) {
            int l = queries[qi][0], r = queries[qi][1];

            while (tp < TN && trips[byLS[tp]].lS >= l) {
                auto& t = trips[byLS[tp++]];
                updA(idxRE(t.rE), t.lz + t.rz);
            }

            int best = 0;
            {
                int ri = (int)(upper_bound(rEv.begin(), rEv.end(), r) -
                               rEv.begin()) -
                         1;
                if (ri >= 0)
                    best = qryA(ri);
            }

            if (tp < TN) {
                auto& t = trips[byLS[tp]];
                if (t.oS > l) {
                    int leftZ = t.oS - l;
                    if (t.rE <= r)
                        best = max(best, leftZ + t.rz);
                    else if (t.oE < r)
                        best = max(best, leftZ + (r - t.oE));
                }
            }

            {
                int blo = 0, bhi = B - 1, brB = 0;
                while (blo <= bhi) {
                    int m = (blo + bhi) / 2;
                    if (blk[m][1] <= r) {
                        brB = m;
                        blo = m + 1;
                    } else
                        bhi = m - 1;
                }
                if (blk[brB][0] == 0 && brB >= 2 && blk[brB - 1][0] == 1 &&
                    blk[brB - 2][0] == 0) {
                    int tLS = blk[brB - 2][1], tOE = blk[brB - 1][2],
                        tOS = blk[brB - 1][1];
                    int tLZ = blk[brB - 2][2] - tLS + 1;
                    if (tLS >= l)
                        best = max(best, tLZ + (r - tOE));
                    else if (tOS > l)
                        best = max(best, (tOS - l) + (r - tOE));
                }
            }

            ans[qi] = total1 + best;
        }

        return ans;
    }
};