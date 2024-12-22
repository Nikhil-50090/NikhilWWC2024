#include <iostream>
#include <memory>
#include <thread>
#include <chrono>
#include <atomic>

struct Task {
    int taskID;
    int priority;
    int executionTime;
    Task* next;

    Task(int id, int prio, int execTime) : taskID(id), priority(prio), executionTime(execTime), next(nullptr) {}
};

class TaskScheduler {
private:
    Task* head;
    std::atomic<bool> running;

public:
    TaskScheduler() : head(nullptr), running(false) {}

    void insertTask(int id, int priority, int execTime) {
        Task* newTask = new Task(id, priority, execTime);
        if (!head || head->priority < priority) {
            newTask->next = head;
            head = newTask;
        } else {
            Task* current = head;
            while (current->next && current->next->priority >= priority) {
                current = current->next;
            }
            newTask->next = current->next;
            current->next = newTask;
        }
    }

    void removeTask(int id) {
        if (!head) return;
        if (head->taskID == id) {
            Task* temp = head;
            head = head->next;
            delete temp;
            return;
        }
        Task* current = head;
        while (current->next && current->next->taskID != id) {
            current = current->next;
        }
        if (current->next) {
            Task* temp = current->next;
            current->next = current->next->next;
            delete temp;
        }
    }

    void executeTasks() {
        running = true;
        while (running) {
            if (head) {
                Task* current = head;
                while (current) {
                    std::cout << "Executing Task ID: " << current->taskID << " with Priority: " << current->priority << std::endl;
                    std::this_thread::sleep_for(std::chrono::seconds(current->executionTime));
                    removeTask(current->taskID);
                    current = head; // Restart from head after removal
                }
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }

    void stop() {
        running = false;
    }

    void displayTasks() {
        Task* current = head;
        while (current) {
            std::cout << "Task ID: " << current->taskID << ", Priority: " << current->priority << ", Execution Time: " << current->executionTime << std::endl;
            current = current->next;
        }
    }
};

int main() {
    TaskScheduler scheduler;

    scheduler.insertTask(1, 2, 3);
    scheduler.insertTask(2, 1, 2);
    scheduler.insertTask(3, 3, 1);

    std::thread schedulerThread(&TaskScheduler::executeTasks, &scheduler);

    std::this_thread::sleep_for(std::chrono::seconds(5));
    scheduler.insertTask(4, 4, 2);

    std::this_thread::sleep_for(std::chrono::seconds(5));
    scheduler.stop();
    schedulerThread.join();

    std::cout << "Final Task List:" << std::endl;
    scheduler.displayTasks();

    return 0;
}
