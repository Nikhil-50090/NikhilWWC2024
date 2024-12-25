#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

struct Ad {
    int id;
    double bidAmount;
    double engagementRate;
    double remainingBudget;

    double priorityScore() const {
        return bidAmount * engagementRate; // Example scoring
    }
};

bool compareAds(const Ad& a, const Ad& b) {
    return a.priorityScore() > b.priorityScore(); // Max-heap based on priority score
}

class AdScheduler {
public:
    void addAd(const Ad& ad) {
        ads.push_back(ad);
    }

    void scheduleAds() {
        std::sort(ads.begin(), ads.end(), compareAds);
        std::cout << "Scheduled Ads:\n";
        for (const auto& ad : ads) {
            std::cout << "Ad ID: " << ad.id 
                      << ", Bid: " << ad.bidAmount 
                      << ", Engagement Rate: " << ad.engagementRate 
                      << ", Remaining Budget: " << ad.remainingBudget << std::endl;
        }
    }

private:
    std::vector<Ad> ads;
};

int main() {
    AdScheduler scheduler;

    // Example ads
    scheduler.addAd({1, 100.0, 0.8, 500.0});
    scheduler.addAd({2, 150.0, 0.6, 300.0});
    scheduler.addAd({3, 120.0, 0.9, 400.0});
    
    scheduler.scheduleAds(); // Schedule ads based on priority

    return 0;
}