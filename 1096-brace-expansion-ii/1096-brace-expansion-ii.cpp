class Solution {
public:
    int pos;
    string expr;

    set<string> parseUnion() {
        set<string> result = parseConcat();

        while (pos < (int)expr.size() && expr[pos] == ',') {
            pos++; // skip comma
            set<string> next = parseConcat();
            for (auto& s : next)
                result.insert(s);
        }

        return result;
    }

    set<string> parseConcat() {
        vector<set<string>> factors;

        while (pos < (int)expr.size() && expr[pos] != ',' && expr[pos] != '}') {
            if (expr[pos] == '{') {
                pos++; // skip '{'
                set<string> inner = parseUnion();
                pos++; // skip '}'
                factors.push_back(inner);
            } else {
                int start = pos;
                while (pos < (int)expr.size() && isalpha(expr[pos]))
                    pos++;
                for (int i = start; i < pos; i++) {
                    factors.push_back({string(1, expr[i])});
                }
            }
        }

        set<string> result;
        result.insert("");

        for (auto& factor : factors) {
            set<string> newResult;
            for (auto& prefix : result) {
                for (auto& suffix : factor) {
                    newResult.insert(prefix + suffix);
                }
            }
            result = newResult;
        }

        return result;
    }

    vector<string> braceExpansionII(string expression) {
        expr = expression;
        pos = 0;
        set<string> resultSet = parseUnion();
        return vector<string>(resultSet.begin(), resultSet.end());
    }
};