#include <iostream>
#include <vector>
#include <queue>      // For std::priority_queue
#include <algorithm>  // For std::sort, std::max, std::find_if
#include <iomanip>    // For std::setw, std::left

// --- 1. 任务结构体 ---
struct Task {
    int id;
    int arrival_time;
    int service_time;

    void print() const {
        std::cout << "Task ID: " << id
                  << ", Arrived: " << arrival_time
                  << ", Service: " << service_time << std::endl;
    }
};

// --- 2. 服务台结构体 ---
struct ServiceDesk {
    int id;
    int available_time; // This desk will be free at this time or later

    ServiceDesk(int _id = -1, int _available_time = 0)
        : id(_id), available_time(_available_time) {}
};

// --- 3. 事件结构体 ---
enum EventType {
    ARRIVAL,
    SERVICE_COMPLETE
};

struct Event {
    int time;
    EventType type;
    Task task; // For ARRIVAL event, the task that arrives
    int desk_id; // For SERVICE_COMPLETE event, the desk that completed service

    // Comparison operator for std::priority_queue (min-heap based on time)
    // std::greater<Event> will make it a min-heap
    bool operator>(const Event& other) const {
        if (time != other.time) {
            return time > other.time;
        }
        // If times are equal, SERVICE_COMPLETE events have higher priority
        // (so they are "smaller" according to > operator for min-heap)
        // This ensures a desk becoming free is processed before a new task arrives at the same time,
        // allowing the desk to immediately pick up a waiting task.
        return type > other.type; 
    }
};

// --- 4. 任务优先级比较器 (用于就绪队列，到达时间小的优先) ---
struct CompareTasks {
    bool operator()(const Task& t1, const Task& t2) const {
        if (t1.arrival_time != t2.arrival_time) {
            return t1.arrival_time > t2.arrival_time; // For min-heap based on arrival_time
        }
        return t1.id > t2.id; // Tie-breaker for stable sorting
    }
};

// --- 5. 任务模拟结果结构体 ---
struct TaskResult {
    int id;
    int arrival_time;
    int start_time;
    int finish_time;
    int wait_time;
    int desk_id;
};


// --- QueueSimulator 类 ---
class QueueSimulator {
private:
    std::vector<ServiceDesk> desks;
    std::priority_queue<Event, std::vector<Event>, std::greater<Event>> event_queue;
    std::priority_queue<Task, std::vector<Task>, CompareTasks> ready_queue;

    int current_time;
    int tasks_completed_count;
    int total_initial_tasks;
    std::vector<TaskResult> simulation_results; // Store results of each task

public:
    // Constructor: Initializes the simulator with a given number of service desks
    QueueSimulator(int num_desks) : 
        current_time(0), 
        tasks_completed_count(0), 
        total_initial_tasks(0) {
        
        if (num_desks <= 0) {
            throw std::invalid_argument("Number of desks must be positive.");
        }
        desks.reserve(num_desks); // Pre-allocate memory
        for (int i = 0; i < num_desks; ++i) {
            desks.emplace_back(i, 0); // Initialize desks (id, available_time)
        }
    }

    // Add a task to the simulation (will be converted to an ARRIVAL event)
    void add_task(const Task& task) {
        event_queue.push({task.arrival_time, ARRIVAL, task, -1}); // -1 for desk_id in arrival events
        total_initial_tasks++; // Keep track of how many tasks we expect to process
    }

    // Run the simulation
    void run_simulation() {
        std::cout << "--- Multi-Desk Queue Simulation ---" << std::endl;
        std::cout << std::left << std::setw(8) << "Time"
                  << std::setw(15) << "EventType"
                  << std::setw(10) << "Task ID"
                  << std::setw(10) << "Desk ID"
                  << std::setw(15) << "Arrival"
                  << std::setw(15) << "Start"
                  << std::setw(15) << "Finish"
                  << std::setw(10) << "Wait" << std::endl;
        std::cout << std::string(100, '-') << std::endl;

        while (!event_queue.empty() || tasks_completed_count < total_initial_tasks) {
            if (event_queue.empty() && tasks_completed_count < total_initial_tasks) {
                // This case should ideally not be reached if all tasks generate ARRIVAL events
                // and simulation logic is correct. It would mean tasks are "stuck".
                std::cerr << "Error: Event queue empty but tasks remain. Exiting." << std::endl;
                break; 
            }

            Event current_event = event_queue.top();
            event_queue.pop();

            current_time = current_event.time; // Advance simulation time

            if (current_event.type == ARRIVAL) {
                ready_queue.push(current_event.task);
                std::cout << std::left << std::setw(8) << current_time
                          << std::setw(15) << "ARRIVAL"
                          << std::setw(10) << current_event.task.id << std::endl;
            } else if (current_event.type == SERVICE_COMPLETE) {
                int completed_desk_id = current_event.desk_id;
                desks[completed_desk_id].available_time = current_time; // Mark desk as free
                tasks_completed_count++;

                // Find the corresponding result to print full row
                auto it = std::find_if(simulation_results.begin(), simulation_results.end(), 
                                       [&](const TaskResult& r){ return r.id == current_event.task.id; });
                if (it != simulation_results.end()) {
                     std::cout << std::left << std::setw(8) << current_time
                               << std::setw(15) << "COMPLETE"
                               << std::setw(10) << it->id
                               << std::setw(10) << it->desk_id
                               << std::setw(15) << it->arrival_time
                               << std::setw(15) << it->start_time
                               << std::setw(15) << it->finish_time
                               << std::setw(10) << it->wait_time << std::endl;
                } else {
                     // Fallback in case result not found (shouldn't happen with correct logic)
                     std::cout << std::left << std::setw(8) << current_time
                               << std::setw(15) << "COMPLETE"
                               << std::setw(10) << current_event.task.id
                               << std::setw(10) << completed_desk_id << std::endl;
                }
            }

            // --- Attempt to assign tasks to idle desks ---
            // Iterate through all desks to find available ones and assign tasks
            // Note: The order of checking desks here doesn't matter for correctness
            // if all desks are identical. If desks had priorities, this would need
            // to be a priority queue of desks.
            for (int i = 0; i < desks.size(); ++i) {
                if (desks[i].available_time <= current_time && !ready_queue.empty()) {
                    Task next_task = ready_queue.top();
                    ready_queue.pop();

                    int start_time = std::max(current_time, next_task.arrival_time);
                    int finish_time = start_time + next_task.service_time;
                    int wait_time = start_time - next_task.arrival_time;

                    desks[i].available_time = finish_time; // Update desk's next available time

                    // Store result
                    simulation_results.push_back({next_task.id, next_task.arrival_time,
                                                 start_time, finish_time, wait_time, desks[i].id});

                    // Schedule a SERVICE_COMPLETE event for this task
                    event_queue.push({finish_time, SERVICE_COMPLETE, next_task, desks[i].id});

                    std::cout << std::left << std::setw(8) << current_time
                              << std::setw(15) << "START"
                              << std::setw(10) << next_task.id
                              << std::setw(10) << desks[i].id
                              << std::setw(15) << next_task.arrival_time
                              << std::setw(15) << start_time
                              << std::setw(15) << finish_time
                              << std::setw(10) << wait_time << std::endl;
                }
            }
        }
        std::cout << std::string(100, '-') << std::endl;
        std::cout << "--- Simulation Finished ---" << std::endl;
    }

    // Print summary of all completed tasks
    void print_summary() const {
        std::cout << "\n--- Task Completion Summary ---" << std::endl;
        std::cout << std::left << std::setw(10) << "Task ID"
                  << std::setw(15) << "Arrival Time"
                  << std::setw(15) << "Start Time"
                  << std::setw(15) << "Finish Time"
                  << std::setw(15) << "Wait Time"
                  << std::setw(10) << "Desk ID" << std::endl;
        std::cout << std::string(90, '-') << std::endl;

        // Create a copy and sort it for presentation
        std::vector<TaskResult> sorted_results = simulation_results;
        std::sort(sorted_results.begin(), sorted_results.end(), [](const TaskResult& a, const TaskResult& b){
            return a.id < b.id; // Sort by Task ID for clean output
        });

        for (const auto& res : sorted_results) {
            std::cout << std::left << std::setw(10) << res.id
                      << std::setw(15) << res.arrival_time
                      << std::setw(15) << res.start_time
                      << std::setw(15) << res.finish_time
                      << std::setw(15) << res.wait_time
                      << std::setw(10) << res.desk_id << std::endl;
        }
    }
};

int main() {
    // Create a simulator with 3 service desks
    QueueSimulator simulator(3);

    // Add tasks
    simulator.add_task({1, 0, 5});
    simulator.add_task({2, 1, 3});
    simulator.add_task({3, 1, 4});
    simulator.add_task({4, 2, 2});
    simulator.add_task({5, 3, 6});
    simulator.add_task({6, 4, 1});
    simulator.add_task({7, 5, 5});
    simulator.add_task({8, 6, 3});
    simulator.add_task({9, 7, 2});
    simulator.add_task({10, 8, 4});

    // Run the simulation
    simulator.run_simulation();

    // Print summary
    simulator.print_summary();

    return 0;
}
