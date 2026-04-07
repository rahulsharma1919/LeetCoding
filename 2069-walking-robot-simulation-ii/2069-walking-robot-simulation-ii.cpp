class Robot {
    vector<pair<int, int>> perim;
    vector<string> dirs;
    int pos, total;
    bool moved = false;

public:
    Robot(int width, int height) {
        // East: (1,0) -> (width-1, 0)
        for (int x = 1; x < width; x++) {
            perim.push_back({x, 0});
            dirs.push_back("East");
        }
        // North: (width-1,1) -> (width-1, height-1)
        for (int y = 1; y < height; y++) {
            perim.push_back({width - 1, y});
            dirs.push_back("North");
        }
        // West: (width-2, height-1) -> (0, height-1)
        for (int x = width - 2; x >= 0; x--) {
            perim.push_back({x, height - 1});
            dirs.push_back("West");
        }
        // South: (0, height-2) -> (0, 0)  <-- (0,0) is "South" after full loop
        for (int y = height - 2; y >= 0; y--) {
            perim.push_back({0, y});
            dirs.push_back("South");
        }

        total = perim.size();
        pos = total - 1; // (0,0) lives at end of South
    }

    void step(int num) {
        pos = (pos + num) % total;
        moved = true;
    }

    vector<int> getPos() { return {perim[pos].first, perim[pos].second}; }

    string getDir() {
        if (!moved)
            return "East";
        return dirs[pos];
    }
};