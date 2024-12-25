#include <iostream>
#include <queue>
#include <vector>
#include <string>

struct Patient {
    int id;
    int severity; // Higher number means more severe
    std::string arrivalTime;

    // Custom comparator for priority queue
    bool operator<(const Patient& other) const {
        if (severity != other.severity) return severity < other.severity; // Max-heap based on severity
        return arrivalTime > other.arrivalTime; // If severity is the same, prioritize by arrival time
    }
};

class Hospital {
public:
    void addPatient(const Patient& patient) {
        patients.push(patient);
    }

    void treatPatients(int n) {
        std::cout << "Treating top " << n << " patients:\n";
        for (int i = 0; i < n && !patients.empty(); ++i) {
            Patient p = patients.top();
            patients.pop();
            std::cout << "Patient ID: " << p.id 
                      << ", Severity: " << p.severity 
                      << ", Arrival Time: " << p.arrivalTime << std::endl;
        }
    }

private:
    std::priority_queue<Patient> patients;
};

int main() {
    Hospital hospital;

    // Example patients
    hospital.addPatient({1, 5, "2023-10-01 08:00"});
    hospital.addPatient({2, 3, "2023-10-01 08:05"});
    hospital.addPatient({3, 7, "2023-10-01 08:10"});
    
    hospital.treatPatients(2); // Treat top 2 patients

    return 0;
}