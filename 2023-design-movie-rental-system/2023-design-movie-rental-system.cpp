class MovieRentingSystem {
    struct Entry {
        int shop, movie, price;
        bool operator<(const Entry& other) const {
            if (price != other.price) return price < other.price;
            if (shop != other.shop) return shop < other.shop;
            return movie < other.movie;
        }
    };

    // Map (shop, movie) -> price
    unordered_map<long long, int> priceMap;

    // movie -> available shops (ordered by price, then shop)
    unordered_map<int, set<Entry>> available;

    // all currently rented movies (ordered by price, then shop, then movie)
    set<Entry> rented;

    long long encode(int shop, int movie) {
        return ((long long)shop << 20) | movie;
    }

public:
    MovieRentingSystem(int n, vector<vector<int>>& entries) {
        for (auto &e : entries) {
            int shop = e[0], movie = e[1], price = e[2];
            priceMap[encode(shop, movie)] = price;
            available[movie].insert({shop, movie, price});
        }
    }

    vector<int> search(int movie) {
        vector<int> ans;
        if (!available.count(movie)) return ans;
        auto &s = available[movie];
        int cnt = 0;
        for (auto it = s.begin(); it != s.end() && cnt < 5; ++it, ++cnt) {
            ans.push_back(it->shop);
        }
        return ans;
    }

    void rent(int shop, int movie) {
        int price = priceMap[encode(shop, movie)];
        Entry e{shop, movie, price};
        available[movie].erase(e);
        rented.insert(e);
    }

    void drop(int shop, int movie) {
        int price = priceMap[encode(shop, movie)];
        Entry e{shop, movie, price};
        rented.erase(e);
        available[movie].insert(e);
    }

    vector<vector<int>> report() {
        vector<vector<int>> ans;
        int cnt = 0;
        for (auto it = rented.begin(); it != rented.end() && cnt < 5; ++it, ++cnt) {
            ans.push_back({it->shop, it->movie});
        }
        return ans;
    }
};
