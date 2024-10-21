#include <iostream>
#include <vector>
#include <string>

class Task {
public:
    std::string description;
    std::string due_date;
    int priority;
    bool completed;

    Task(std::string desc, std::string date, int prio) 
        : description(desc), due_date(date), priority(prio), completed(false) {}
};

class ToDoList {
private:
    std::vector<Task> tasks;

public:
    void add_task(const std::string& description, const std::string& due_date, int priority) {
        tasks.push_back(Task(description, due_date, priority));
    }

    void delete_task(int index) {
        if (index < 0 || index >= tasks.size()) {
            std::cout << "Invalid task index.\n";
            return;
        }
        tasks.erase(tasks.begin() + index);
    }

    void mark_task_completed(int index) {
        if (index < 0 || index >= tasks.size()) {
            std::cout << "Invalid task index.\n";
            return;
        }
        tasks[index].completed = true;
    }

    void display_tasks() const {
        if (tasks.empty()) {
            std::cout << "No tasks available.\n";
            return;
        }
        for (size_t i = 0; i < tasks.size(); ++i) {
            std::cout << "Task " << i + 1 << ": " << tasks[i].description << " | Due Date: " << tasks[i].due_date 
                      << " | Priority: " << tasks[i].priority 
                      << " | Completed: " << (tasks[i].completed ? "Yes" : "No") << "\n";
        }
    }
};

int main() {
    ToDoList my_list;
    int choice;
    std::string description, due_date;
    int priority, index;

    do {
        std::cout << "\nTo-Do List Menu:\n";
        std::cout << "1. Add Task\n";
        std::cout << "2. Delete Task\n";
        std::cout << "3. Mark Task as Completed\n";
        std::cout << "4. Display All Tasks\n";
        std::cout << "5. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cin.ignore(); // To clear the buffer
                std::cout << "Enter task description: ";
                std::getline(std::cin, description);
                std::cout << "Enter due date (YYYY-MM-DD): ";
                std::getline(std::cin, due_date);
                std::cout << "Enter priority (1-5): ";
                std::cin >> priority;
                my_list.add_task(description, due_date, priority);
                break;

            case 2:
                std::cout << "Enter task index to delete: ";
                std::cin >> index;
                my_list.delete_task(index - 1);
                break;

            case 3:
                std::cout << "Enter task index to mark as completed: ";
                std::cin >> index;
                my_list.mark_task_completed(index - 1);
                break;

            case 4:
                my_list.display_tasks();
                break;

            case 5:
                std::cout << "Exiting...\n";
                break;

            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5);

    return 0;
}