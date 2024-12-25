#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

struct Trade {
    std::string timestamp;
    std::string stockSymbol;
    double tradePrice;
    int tradeVolume;
};

bool compareTrades(const Trade& a, const Trade& b) {
    if (a.timestamp != b.timestamp) return a.timestamp < b.timestamp;
    if (a.stockSymbol != b.stockSymbol) return a.stockSymbol < b.stockSymbol;
    return a.tradeVolume < b.tradeVolume;
}

class StockMarketAnalyzer {
public:
    void addTrade(const Trade& trade) {
        trades.push_back(trade);
    }

    void analyzeTrades() {
        std::sort(trades.begin(), trades.end(), compareTrades);
        std::cout << "Sorted Trades:\n";
        for (const auto& trade : trades) {
            std::cout << "Timestamp: " << trade.timestamp 
                      << ", Symbol: " << trade.stockSymbol 
                      << ", Price: " << trade.tradePrice 
                      << ", Volume: " << trade.tradeVolume << std::endl;
        }
    }

private:
    std::vector<Trade> trades;
};

int main() {
    StockMarketAnalyzer analyzer;

    // Example trades
    analyzer.addTrade({"2023-10-01 09:30", "AAPL", 150.0, 100});
    analyzer.addTrade({"2023-10-01 09:31", "GOOGL", 2800.0, 50});
    analyzer.addTrade({"2023-10-01 09:30", "AAPL", 151.0, 200});
    
    analyzer.analyzeTrades(); // Analyze and sort trades

    return 0;
}