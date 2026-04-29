#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm>
#include <limits>

const int QUANTUM = 4; // Quantum for the Round Robin algorithm

class Process {
public:
    int pid;
    int burst_time;
    int priority;

    Process(int pid, int burst_time, int priority)
        : pid(pid), burst_time(burst_time), priority(priority) {}
};

std::vector<Process> generateProcesses(int num_processes) {
    srand(time(nullptr));
    std::vector<Process> processes;

    for (int i = 0; i < num_processes; i++) {
        processes.emplace_back(i, rand() % 20 + 1, rand() % 3 + 1);
    }

    return processes;
}

void displayProcesses(const std::vector<Process>& processes) {
    int N = processes.size(); // Number of processes
    std::cout << "ID\tBurst Time\tPriority" << std::endl;
    std::cout << "--------------------------------" << std::endl;

    for (int i = 0; i < N; i++) {
      std::cout << processes[i].pid << "\t" << processes[i].burst_time << "\t\t" << processes[i].priority << std::endl;
    }
}

double total_burst_time(const std::vector<Process>& processes) {
    double total_burst_time = 0;
    for (const auto& process : processes) {
        total_burst_time += process.burst_time;
    }
    return total_burst_time;
}

double first_come_first_served(const std::vector<Process>& processes) {
    int N = processes.size(); // Number of processes
    std::vector<int> waiting_time(N, 0); // Initialize the waiting time of all processes

    // Calculate the waiting time for each process
    for (int i = 1; i < N; i++) {
        waiting_time[i] = waiting_time[i - 1] + processes[i - 1].burst_time;
    }

    // Calculate the average waiting time
    double avg_waiting_time = 0;
    for (int i = 0; i < N; i++) {
        avg_waiting_time += waiting_time[i];
    }
    avg_waiting_time /= N;

    // Show the scheduling results
    std::cout << "FCFS Scheduling:\n";
    std::cout << "Process\tBurst Time\tPriority\tWaiting Time\n";
    for (int i = 0; i < N; i++) {
        std::cout << processes[i].pid << "\t" << processes[i].burst_time << "\t\t"
                  << processes[i].priority << "\t\t" << waiting_time[i] << "\n";
    }
    std::cout << "Average Waiting Time: " << avg_waiting_time << "\n";
    return avg_waiting_time;
}

bool compareByBurstTime(const Process& a, const Process& b) {
    return a.burst_time < b.burst_time;
}

double shortest_job_first(const std::vector<Process>& processes) {
  int N = processes.size(); // Number of processes
  // Creation of a copy of the processes vector
  std::vector<Process> processes_copy = processes;

  // Sort the processes based on the shortest burst time
  std::sort(processes_copy.begin(), processes_copy.end(), compareByBurstTime);

  std::vector<int> waiting_time(N, 0); // Initialize the waiting time for all processes

  // Calculate the waiting time for each process
  for (int i = 1; i < N; i++) {
      waiting_time[i] = waiting_time[i - 1] + processes_copy[i - 1].burst_time;
  }

  // Calculate the average waiting time
  double avg_waiting_time = 0;
  for (int i = 0; i < N; i++) {
      avg_waiting_time += waiting_time[i];
  }
  avg_waiting_time /= N;

  // Display the scheduling result
  std::cout << "SJF Scheduling:\n";
  std::cout << "Process\tBurst Time\tPriority\tWaiting Time\n";
  for (int i = 0; i < N; i++) {
      std::cout << processes_copy[i].pid << "\t" << processes_copy[i].burst_time << "\t\t"
                << processes_copy[i].priority << "\t\t" << waiting_time[i] << "\n";
  }
  std::cout << "Average Waiting Time: " << avg_waiting_time << "\n";
  return avg_waiting_time;
}

double priority_scheduling(const std::vector<Process>& processes) {
  int N = processes.size(); // Number of processes
  // Creation of a copy of the processes vector
  std::vector<Process> processes_copy = processes;

  // Sort the processes based on priority
  std::sort(processes_copy.begin(), processes_copy.end(), [](const Process& a, const Process& b) {
      return a.priority < b.priority;
  });

  std::vector<int> waiting_time(N, 0); // Initialize the waiting time for all processes

  // Calculate the waiting time for each process
  for (int i = 1; i < N; i++) {
      waiting_time[i] = waiting_time[i - 1] + processes_copy[i - 1].burst_time;
  }

  // Calculate the average waiting time
  double avg_waiting_time = 0;
  for (int i = 0; i < N; i++) {
      avg_waiting_time += waiting_time[i];
  }
  avg_waiting_time /= N;

  // Display the scheduling result
  std::cout << "Priority Scheduling:\n";
  std::cout << "Process\tBurst Time\tPriority\tWaiting Time\n";
  for (int i = 0; i < N; i++) {
      std::cout << processes_copy[i].pid << "\t" << processes_copy[i].burst_time << "\t\t"
                << processes_copy[i].priority << "\t\t" << waiting_time[i] << "\n";
  }
  std::cout << "Average Waiting Time: " << avg_waiting_time << "\n";
  return avg_waiting_time;
}

double round_robin(const std::vector<Process>& processes) {
int N = processes.size(); // Number of processes
  // Initialize the waiting time and completion time for all processes
std::vector<int> waiting_time(N, 0);
std::vector<int> completion_time(N, 0);

// Create a copy of the burst time
std::vector<int> remaining_burst_time(N);
for (int i = 0; i < N; i++) {
    remaining_burst_time[i] = processes[i].burst_time;
}

int time = 0; // The current system time

// Continue executing processes in the queue until all are completed
while (true) {
    bool done = true;

    // Execute all processes one by one
    for (int i = 0; i < N; i++) {
        // If the burst time of the process is greater than 0, then the process is not yet completed
        if (remaining_burst_time[i] > 0) {
            done = false; // There is still a process waiting

            if (remaining_burst_time[i] > QUANTUM) {
                // Increase the system time by a quantum of time
                time += QUANTUM;

                // Decrement the burst time of the process by a quantum of time
                remaining_burst_time[i] -= QUANTUM;
            } else {
                // Increase the system time by the remaining burst time of the process
                time += remaining_burst_time[i];

                // The waiting time is the system time minus the burst time of the process
                waiting_time[i] = time - processes[i].burst_time;

                // The remaining burst time of the process becomes 0
                remaining_burst_time[i] = 0;
            }
        }
    }

    // If all processes are completed
    if (done == true)
        break;
}

// Calculate the average waiting time
double avg_waiting_time = 0;
for (int i = 0; i < N; i++) {
    avg_waiting_time += waiting_time[i];
}
avg_waiting_time /= N;

// Display the scheduling result
std::cout << "Round Robin Scheduling:\n";
std::cout << "Process\tBurst Time\tPriority\tWaiting Time\n";
for (int i = 0; i < N; i++) {
    std::cout << processes[i].pid << "\t" << processes[i].burst_time << "\t\t"
              << processes[i].priority << "\t\t" << waiting_time[i] << "\n";
}
std::cout << "Average Waiting Time: " << avg_waiting_time << "\n";
return avg_waiting_time;
}

double multilevel_queue_scheduling(const std::vector<Process>& processes) {
    int N = processes.size(); // Number of processes
    std::vector<std::vector<Process>> queues(3); // Creation of 3 vectors

    // Random distribution of processes in queues
    srand(time(nullptr)); // Set the initial seed based on system time
    for (const auto& process : processes) {
        int queue_number = rand() % 3; // Generate a random number between 0 and 2
        queues[queue_number].push_back(process); // Add process to the vector
    }

    // Execution of processes in each queue using a different scheduling algorithm
    // Queue 0: Round Robin
    // Queue 1: First Come First Served (FCFS)
    // Queue 2: Shortest Job First (SJF)
    std::cout << "--------------------------------------------\n";
    std::cout << "Queue 0: Round Robin.\n";
    double avg_waiting_time_0 = 0;
    avg_waiting_time_0 += round_robin(queues[0]);
    double total_burst_time_0 = total_burst_time(queues[0]); // calculate the total burst time for queue 0
    std::cout << "--------------------------------------------\n";
    std::cout << "Queue 1: First Come First Served (FCFS).\n";
    double avg_waiting_time_1 = 0;
    avg_waiting_time_1 += first_come_first_served(queues[1]) + (total_burst_time_0 * queues[1].size()); // add the total burst time of queue 0 to the waiting time of each process in queue 1
    std::cout << "Average Waiting Time (including the previous queue): " << avg_waiting_time_1 << "\n";
    double total_burst_time_1 = total_burst_time(queues[1]); // calculate the total burst time for queue 1
    std::cout << "--------------------------------------------\n";
    std::cout << "Queue 2: Shortest Job First (SJF).\n";
    double avg_waiting_time_2 = 0;
    avg_waiting_time_2 += shortest_job_first(queues[2]) + (total_burst_time_0 * queues[1].size()) + (total_burst_time_1 * queues[2].size()); // add the total burst times of queues 0 and 1 to the waiting time of queue 2
    std::cout << "Average Waiting Time (including the previous queues): " << avg_waiting_time_2 << "\n";
    std::cout << "--------------------------------------------\n";

    double total_waiting_time = avg_waiting_time_0 + avg_waiting_time_1 + avg_waiting_time_2; // Calculate the overall total waiting time
    double avg_waiting_time = total_waiting_time / 3; // Calculate the overall average waiting time
    std::cout << "Average Waiting Time: " << avg_waiting_time << "\n";
    return avg_waiting_time;
}

int main() {
    srand(time(nullptr));

    std::vector<Process> processes = generateProcesses(10);

  while(true){
    int choice;
    do {
      std::cout << "\n\n";
      std::cout << "--------------------------------------------\n";
      std::cout << "Choose a scheduling algorithm:\n";
      std::cout << "1. First Come First Served (FCFS)\n";
      std::cout << "2. Shortest Job First (SJF)\n";
      std::cout << "3. Priority Scheduling\n";
      std::cout << "4. Round Robin (RR)\n";
      std::cout << "5. Multilevel Queue Scheduling\n";
      std::cout << "--\n";
      std::cout << "8. Display Processes\n";
      std::cout << "9. Clear Processes and Generate New Ones\n";
      std::cout << "0. Exit\n";
      std::cout << "--------------------------------------------\n";
      std::cout << "Enter your choice (0-9): ";
      std::cin >> choice;
      std::cout << "\n\n";

      // Input control
      if (std::cin.fail() || choice == 6 || choice == 7 || choice < 0 || choice > 9) {
          std::cout << "Invalid option! Please enter another option, choose from the menu above.\n";
          std::cin.clear();
          std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      }

    } while (std::cin.fail() || choice == 6 || choice == 7 || choice < 0 || choice > 9);

    switch (choice) {
        case 1:
            first_come_first_served(processes);
            break;
        case 2:
            shortest_job_first(processes);
            break;
        case 3:
            priority_scheduling(processes);
            break;
        case 4:
            round_robin(processes);
            break;
        case 5:
            multilevel_queue_scheduling(processes);
            break;
        case 8:
            // Show the processes
            displayProcesses(processes);
            break;
        case 9:
            // Delete
            processes.clear();
            std::cout << "Processes deleted. ";
            // Generate new processes
            processes = generateProcesses(10);
            std::cout << "New processes generated.\n";
            break;
          case 0:
            std::cout << "Goodbye.\n";
            return 0;
        default:
            std::cout << "Invalid option.\n";
    }
  }

    return 0;
}
