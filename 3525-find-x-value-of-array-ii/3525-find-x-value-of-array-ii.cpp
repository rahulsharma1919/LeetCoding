class Solution {
public:
    int K, n;
    vector<vector<array<long long, 5>>> cntMat;
    vector<array<int, 5>> fullTrans;
    vector<int> tarr;

    void build(int node, int l, int r) {
        if (l == r) {
            int m = tarr[l];
            for (int a = 0; a < K; a++) {
                int nb = (a * m) % K;
                for (int b = 0; b < K; b++)
                    cntMat[node][a][b] = 0;
                cntMat[node][a][nb] = 1;
                fullTrans[node][a] = nb;
            }
            return;
        }
        int mid = (l + r) / 2;
        build(2 * node, l, mid);
        build(2 * node + 1, mid + 1, r);

        for (int a = 0; a < K; a++) {
            for (int b = 0; b < K; b++)
                cntMat[node][a][b] = cntMat[2 * node][a][b];
            int c = fullTrans[2 * node][a];
            for (int b = 0; b < K; b++) {
                cntMat[node][a][b] += cntMat[2 * node + 1][c][b];
            }
            fullTrans[node][a] = fullTrans[2 * node + 1][c];
        }
    }

    void update(int node, int l, int r, int idx, int val) {
        if (l == r) {
            int m = val;
            for (int a = 0; a < K; a++) {
                int nb = (a * m) % K;
                for (int b = 0; b < K; b++)
                    cntMat[node][a][b] = 0;
                cntMat[node][a][nb] = 1;
                fullTrans[node][a] = nb;
            }
            return;
        }
        int mid = (l + r) / 2;
        if (idx <= mid)
            update(2 * node, l, mid, idx, val);
        else
            update(2 * node + 1, mid + 1, r, idx, val);

        for (int a = 0; a < K; a++) {
            for (int b = 0; b < K; b++)
                cntMat[node][a][b] = cntMat[2 * node][a][b];
            int c = fullTrans[2 * node][a];
            for (int b = 0; b < K; b++) {
                cntMat[node][a][b] += cntMat[2 * node + 1][c][b];
            }
            fullTrans[node][a] = fullTrans[2 * node + 1][c];
        }
    }

    array<long long, 5> queryFrom(int node, int l, int r, int qs,
                                  int startResidue, int& curResidue) {
        if (r < qs) {
            array<long long, 5> zero{};
            return zero;
        }
        if (l >= qs) {
            array<long long, 5> res;
            for (int b = 0; b < K; b++)
                res[b] = cntMat[node][curResidue][b];
            curResidue = fullTrans[node][curResidue];
            return res;
        }
        int mid = (l + r) / 2;
        array<long long, 5> leftRes =
            queryFrom(2 * node, l, mid, qs, startResidue, curResidue);
        array<long long, 5> rightRes =
            queryFrom(2 * node + 1, mid + 1, r, qs, startResidue, curResidue);
        array<long long, 5> res{};
        for (int b = 0; b < K; b++)
            res[b] = leftRes[b] + rightRes[b];
        return res;
    }

    vector<int> resultArray(vector<int>& nums, int k,
                            vector<vector<int>>& queries) {
        K = k;
        n = nums.size();
        tarr.resize(n);
        for (int i = 0; i < n; i++)
            tarr[i] = nums[i] % k;

        int size = 4 * n;
        cntMat.assign(size, vector<array<long long, 5>>(K));
        fullTrans.assign(size, array<int, 5>());

        build(1, 0, n - 1);

        vector<int> result;
        for (auto& q : queries) {
            int index = q[0], value = q[1], start = q[2], x = q[3];
            tarr[index] = value % k;
            update(1, 0, n - 1, index, tarr[index]);

            int curResidue =
                1 % k; // start with multiplicative identity residue
            auto counts = queryFrom(1, 0, n - 1, start, 1, curResidue);
            result.push_back((int)counts[x]);
        }

        return result;
    }
};