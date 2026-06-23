class Solution {
public:
    int zigZagArrays(int n, int l, int r) {
        const int MOD = 1e9 + 7;
        int sz = r - l + 1;

        if (n == 1)
            return sz;

        vector<long long> up(sz), down(sz), nup(sz), ndown(sz);
        for (int v = 0; v < sz; v++) {
            up[v] = v;
            down[v] = sz - 1 - v;
        }

        vector<long long> preDown(sz + 1), sufUp(sz + 1);

        for (int i = 2; i < n; i++) {
            preDown[0] = 0;
            for (int v = 0; v < sz; v++)
                preDown[v + 1] = (preDown[v] + down[v]) % MOD;

            sufUp[sz] = 0;
            for (int v = sz - 1; v >= 0; v--)
                sufUp[v] = (sufUp[v + 1] + up[v]) % MOD;

            for (int v = 0; v < sz; v++) {
                nup[v] = preDown[v];
                ndown[v] = sufUp[v + 1];
            }
            swap(up, nup);
            swap(down, ndown);
        }

        long long ans = 0;
        for (int v = 0; v < sz; v++)
            ans = (ans + up[v] + down[v]) % MOD;

        return (int)ans;
    }
};