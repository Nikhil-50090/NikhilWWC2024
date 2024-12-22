#include <iostream>
#include <string>
#include <vector>

struct Passenger {
    std::string name;
    int seatNumber;
    Passenger* next;

    Passenger(const std::string& name, int seatNumber)
        : name(name), seatNumber(seatNumber), next(nullptr) {}
};

struct Compartment {
    int compartmentNumber;
    int totalSeats;
    int availableSeats;
    Passenger* passengerList;

    Compartment(int number, int seats)
        : compartmentNumber(number), totalSeats(seats), availableSeats(seats), passengerList(nullptr) {}

    bool bookSeat(const std::string& passengerName) {
        if (availableSeats <= 0) {
            std::cout << "No available seats in Compartment " << compartmentNumber << std::endl;
            return false;
        }
        int seatNumber = totalSeats - availableSeats + 1; // Assign seat number
        Passenger* newPassenger = new Passenger(passengerName, seatNumber);
        newPassenger->next = passengerList;
        passengerList = newPassenger;
        availableSeats--;
        std::cout << "Booked seat " << seatNumber << " for " << passengerName << " in Compartment " << compartmentNumber << std::endl;
        return true;
    }

    bool cancelSeat(int seatNumber) {
        Passenger* current = passengerList;
        Passenger* previous = nullptr;

        while (current) {
            if (current->seatNumber == seatNumber) {
                if (previous) {
                    previous->next = current->next;
                } else {
                    passengerList = current->next; // Head of the list
                }
                delete current;
                availableSeats++;
                std::cout << "Cancelled seat " << seatNumber << " in Compartment " << compartmentNumber << std::endl;
                return true;
            }
            previous = current;
            current = current->next;
        }
        std::cout << "Seat " << seatNumber << " not found in Compartment " << compartmentNumber << std::endl;
        return false;
    }

    void checkAvailability() const {
        std::cout << "Compartment " << compartmentNumber << ": " << availableSeats << "/" << totalSeats << " seats available." << std::endl;
    }
};

struct Train {
    int trainNumber;
    std::vector<Compartment*> compartments;

    Train(int number) : trainNumber(number) {}

    void addCompartment(int seats) {
        compartments.push_back(new Compartment(compartments.size() + 1, seats));
    }

    Compartment* getCompartment(int number) {
        if (number > 0 && number <= compartments.size()) {
            return compartments[number - 1];
        }
        return nullptr;
    }
};

class TrainReservationSystem {
private:
    std::vector<Train*> trains;

public:
    ~TrainReservationSystem() {
        for (auto train : trains) {
            for (auto compartment : train->compartments) {
                Passenger* current = compartment->passengerList;
                while (current) {
                    Passenger* temp = current;
                    current = current->next;
                    delete temp;
                }
                delete compartment;
            }
            delete train;
        }
    }

    void addTrain(int trainNumber) {
        trains.push_back(new Train(trainNumber));
        std::cout << "Added Train " << trainNumber << std::endl;
    }

    void addCompartmentToTrain(int trainNumber, int seats) {
        Train* train = getTrain(trainNumber);
        if (train) {
            train->addCompartment(seats);
            std::cout << "Added Compartment to Train " << trainNumber << " with " << seats << " seats." << std::endl;
        } else {
            std::cout << "Train " << trainNumber << " not found." << std::endl;
        }
    }

    void bookSeat(int trainNumber, int compartmentNumber, const std::string& passengerName) {
        Train* train = getTrain(trainNumber);
        if (train) {
            Compartment* compartment = train->getCompartment(compartmentNumber);
            if (compartment) {
                compartment->bookSeat(passengerName);
            } else {
                std::cout << "Comp artment " << compartmentNumber << " not found in Train " << trainNumber << std::endl;
            }
        } else {
            std::cout << "Train " << trainNumber << " not found." << std::endl;
        }
    }

    void cancelSeat(int trainNumber, int compartmentNumber, int seatNumber) {
        Train* train = getTrain(trainNumber);
        if (train) {
            Compartment* compartment = train->getCompartment(compartmentNumber);
            if (compartment) {
                compartment->cancelSeat(seatNumber);
            } else {
                std::cout << "Compartment " << compartmentNumber << " not found in Train " << trainNumber << std::endl;
            }
        } else {
            std::cout << "Train " << trainNumber << " not found." << std::endl;
        }
    }

    void checkAvailability(int trainNumber, int compartmentNumber) {
        Train* train = getTrain(trainNumber);
        if (train) {
            Compartment* compartment = train->getCompartment(compartmentNumber);
            if (compartment) {
                compartment->checkAvailability();
            } else {
                std::cout << "Compartment " << compartmentNumber << " not found in Train " << trainNumber << std::endl;
            }
        } else {
            std::cout << "Train " << trainNumber << " not found." << std::endl;
        }
    }

private:
    Train* getTrain(int trainNumber) {
        for (auto train : trains) {
            if (train->trainNumber == trainNumber) {
                return train;
            }
        }
        return nullptr;
    }
};

int main() {
    TrainReservationSystem system;

    // Adding trains and compartments
    system.addTrain(101);
    system.addCompartmentToTrain(101, 5); // 5 seats in compartment 1
    system.addCompartmentToTrain(101, 10); // 10 seats in compartment 2

    // Booking seats
    system.bookSeat(101, 1, "Alice");
    system.bookSeat(101, 1, "Bob");
    system.bookSeat(101, 2, "Charlie");

    // Checking availability
    system.checkAvailability(101, 1);
    system.checkAvailability(101, 2);

    // Canceling a seat
    system.cancelSeat(101, 1, 1); // Cancel Alice's seat
    system.checkAvailability(101, 1);

    // Attempting to cancel a non-existent seat
    system.cancelSeat(101, 1, 3); // Seat 3 does not exist

    return 0;
}