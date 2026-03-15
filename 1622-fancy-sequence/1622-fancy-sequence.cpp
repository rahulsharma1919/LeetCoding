class Fancy {
    const long long MOD = 1e9 + 7;
    vector<long long> seq;
    long long add = 0, mult = 1;

    long long power(long long base, long long exp, long long mod) {
        long long result = 1;
        base %= mod;
        while (exp > 0) {
            if (exp & 1)
                result = result * base % mod;
            base = base * base % mod;
            exp >>= 1;
        }
        return result;
    }

    long long modInv(long long x) { return power(x, MOD - 2, MOD); }

public:
    Fancy() {}

    void append(int val) {
        long long normalized =
            (val - add % MOD + MOD) % MOD * modInv(mult) % MOD;
        seq.push_back(normalized);
    }

    void addAll(int inc) { add = (add + inc) % MOD; }

    void multAll(int m) {
        add = add * m % MOD;
        mult = mult * m % MOD;
    }

    int getIndex(int idx) {
        if (idx >= seq.size())
            return -1;
        return (seq[idx] * mult % MOD + add) % MOD;
    }
};

/**
 * Your Fancy object will be instantiated and called as such:
 * Fancy* obj = new Fancy();
 * obj->append(val);
 * obj->addAll(inc);
 * obj->multAll(m);
 * int param_4 = obj->getIndex(idx);
 */