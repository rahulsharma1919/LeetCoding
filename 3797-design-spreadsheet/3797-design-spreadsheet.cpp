class Spreadsheet {
    unordered_map<string, int> cells;

public:
    Spreadsheet(int rows) {
        // Rows info not needed for our hashmap-based approach
    }

    void setCell(string cell, int value) {
        cells[cell] = value;
    }

    void resetCell(string cell) {
        cells.erase(cell);  // Remove cell from map, default value 0 if accessed
    }

    int getValue(string formula) {
        // Remove '=' at the start
        formula = formula.substr(1);
        int plusPos = formula.find('+');
        string left = formula.substr(0, plusPos);
        string right = formula.substr(plusPos + 1);

        auto getVal = [&](const string &s) {
            if (isalpha(s[0])) return cells.count(s) ? cells[s] : 0; // cell reference
            return stoi(s);  // numeric value
        };

        return getVal(left) + getVal(right);
    }
};
