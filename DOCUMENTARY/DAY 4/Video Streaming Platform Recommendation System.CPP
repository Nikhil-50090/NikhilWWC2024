#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

struct Video {
    std::string title;
    int totalViews;
    double userRating;
    int releaseYear;

    double popularityScore() const {
        return totalViews * userRating; // Example scoring
    }
};

bool compareVideos(const Video& a, const Video& b) {
    if (a.popularityScore() != b.popularityScore()) return a.popularityScore() > b.popularityScore();
    return a.releaseYear > b.releaseYear; // More recent first
}

class VideoRecommendationSystem {
public:
    void addVideo(const Video& video) {
        videos.push_back(video);
    }

    void recommendVideos() {
        std::sort(videos.begin(), videos.end(), compareVideos);
        std::cout << "Recommended Videos:\n";
        for (const auto& video : videos) {
            std::cout << "Title: " << video.title 
                      << ", Views: " << video.totalViews 
                      << ", Rating: " << video.userRating 
                      << ", Year: " << video.releaseYear << std::endl;
        }
    }

private:
    std::vector<Video> videos;
};

int main() {
    VideoRecommendationSystem system;

    // Example videos
    system.addVideo({"Inception", 1000000, 8.8, 2010});
    system.addVideo({"The Matrix", 800000, 8.7, 1999});
    system.addVideo({"Avengers: Endgame", 1500000, 8.4, 2019});
    system.addVideo({"The Shawshank Redemption", 500000, 9.3, 1994});
    
    system.recommendVideos(); // Recommend videos based on popularity and recency

    return 0;
}