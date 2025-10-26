class Bank {
    vector<long long> bal;

public:
    Bank(vector<long long>& balance) { bal = balance; }

    bool valid(int acc) { return acc >= 1 && acc <= bal.size(); }

    bool transfer(int a1, int a2, long long money) {
        if (!valid(a1) || !valid(a2) || bal[a1 - 1] < money)
            return false;
        bal[a1 - 1] -= money;
        bal[a2 - 1] += money;
        return true;
    }

    bool deposit(int acc, long long money) {
        if (!valid(acc))
            return false;
        bal[acc - 1] += money;
        return true;
    }

    bool withdraw(int acc, long long money) {
        if (!valid(acc) || bal[acc - 1] < money)
            return false;
        bal[acc - 1] -= money;
        return true;
    }
};
