class FoodRatings {
    unordered_map<string, pair<int,string>> foodInfo; // food -> {rating, cuisine}
    unordered_map<string, set<pair<int,string>>> cuisineFoods; // cuisine -> ordered set of {-rating, food}
public:
    FoodRatings(vector<string>& foods, vector<string>& cuisines, vector<int>& ratings) {
        int n = foods.size();
        for (int i = 0; i < n; i++) {
            foodInfo[foods[i]] = {ratings[i], cuisines[i]};
            cuisineFoods[cuisines[i]].insert({-ratings[i], foods[i]});
        }
    }
    
    void changeRating(string food, int newRating) {
        auto [oldRating, cuisine] = foodInfo[food];
        cuisineFoods[cuisine].erase({-oldRating, food});
        cuisineFoods[cuisine].insert({-newRating, food});
        foodInfo[food] = {newRating, cuisine};
    }
    
    string highestRated(string cuisine) {
        return cuisineFoods[cuisine].begin()->second;
    }
};
