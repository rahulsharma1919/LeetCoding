class Solution {
public:
    int K, n;
    vector<int> cntMat;    // flat: node*K*K + a*K + b
    vector<int> fullTrans; // flat: node*K + a
    vector<int> tarr;

    inline int cIdx(int node, int a, int b) { return node * K * K + a * K + b; }
    inline int fIdx(int node, int a) { return node * K + a; }

    void pull(int node) {
        int L = 2 * node, R = 2 * node + 1;
        for (int a = 0; a < K; a++) {
            int c = fullTrans[fIdx(L, a)];
            for (int b = 0; b < K; b++) {
                cntMat[cIdx(node, a, b)] =
                    cntMat[cIdx(L, a, b)] + cntMat[cIdx(R, c, b)];
            }
            fullTrans[fIdx(node, a)] = fullTrans[fIdx(R, c)];
        }
    }

    void setLeaf(int node, int m) {
        for (int a = 0; a < K; a++) {
            int nb = (a * m) % K;
            for (int b = 0; b < K; b++)
                cntMat[cIdx(node, a, b)] = 0;
            cntMat[cIdx(node, a, nb)] = 1;
            fullTrans[fIdx(node, a)] = nb;
        }
    }

    void build(int node, int l, int r) {
        if (l == r) {
            setLeaf(node, tarr[l]);
            return;
        }
        int mid = (l + r) / 2;
        build(2 * node, l, mid);
        build(2 * node + 1, mid + 1, r);
        pull(node);
    }

    void update(int node, int l, int r, int idx, int val) {
        if (l == r) {
            setLeaf(node, val);
            return;
        }
        int mid = (l + r) / 2;
        if (idx <= mid)
            update(2 * node, l, mid, idx, val);
        else
            update(2 * node + 1, mid + 1, r, idx, val);
        pull(node);
    }

    void query(int node, int l, int r, int qs, int x, int& curResidue,
               long long& ans) {
        if (r < qs)
            return;
        if (l >= qs) {
            ans += cntMat[cIdx(node, curResidue, x)];
            curResidue = fullTrans[fIdx(node, curResidue)];
            return;
        }
        int mid = (l + r) / 2;
        query(2 * node, l, mid, qs, x, curResidue, ans);
        query(2 * node + 1, mid + 1, r, qs, x, curResidue, ans);
    }

    vector<int> resultArray(vector<int>& nums, int k,
                            vector<vector<int>>& queries) {
        K = k;
        n = nums.size();
        tarr.resize(n);
        for (int i = 0; i < n; i++)
            tarr[i] = nums[i] % k;

        int size = 4 * n;
        cntMat.assign((long long)size * K * K, 0);
        fullTrans.assign((long long)size * K, 0);

        build(1, 0, n - 1);

        vector<int> result;
        result.reserve(queries.size());

        for (auto& q : queries) {
            int index = q[0], value = q[1], start = q[2], x = q[3];
            tarr[index] = value % K;
            update(1, 0, n - 1, index, tarr[index]);

            int curResidue = 1 % K;
            long long ans = 0;
            query(1, 0, n - 1, start, x, curResidue, ans);
            result.push_back((int)ans);
        }

        return result;
    }
};