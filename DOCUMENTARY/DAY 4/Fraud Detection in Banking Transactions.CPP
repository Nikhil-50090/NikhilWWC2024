#include <iostream>
#include <queue>
#include <vector>

struct Transaction {
    int id;
    double amount;
    int frequency;
    std::string location;
    double suspiciousnessScore;

    // Custom comparator for priority queue
    bool operator<(const Transaction& other) const {
        return suspiciousnessScore < other.suspiciousnessScore; // Max-heap
    }
};

class FraudDetector {
public:
    void addTransaction(const Transaction& transaction) {
        transactions.push(transaction);
    }

    void reviewTransactions(int n) {
        std::cout << "Reviewing top " << n << " suspicious transactions:\n";
        for (int i = 0; i < n && !transactions.empty(); ++i) {
            Transaction t = transactions.top();
            transactions.pop();
            std::cout << "Transaction ID: " << t.id 
                      << ", Score: " << t.suspiciousnessScore << std::endl;
        }
    }

private:
    std::priority_queue<Transaction> transactions;
};

int main() {
    FraudDetector detector;

    // Example transactions
    detector.addTransaction({1, 1000.0, 5, "NY", 8.5});
    detector.addTransaction({2, 500.0, 10, "CA", 6.0});
    detector.addTransaction({3, 2000.0, 2, "TX", 9.0});
    
    detector.reviewTransactions(2); // Review top 2 transactions

    return 0;
}