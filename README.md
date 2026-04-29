# os_stimulator
🚀 Process Scheduler Simulator (C++)

A CPU Scheduling Simulator built in C++ that demonstrates core concepts of Operating Systems such as process scheduling, queue management, and performance evaluation.

📌 Overview

This project simulates how an operating system schedules processes using different algorithms. It provides an interactive CLI interface where users can generate processes and apply various scheduling techniques.

The simulator helps in understanding:

Process lifecycle
CPU scheduling strategies
Performance metrics like waiting time
⚙️ Features
✅ First Come First Serve (FCFS)
✅ Shortest Job First (SJF)
✅ Priority Scheduling
✅ Round Robin (Time Quantum Based)
✅ Multilevel Queue Scheduling
✅ Dynamic Process Generation
✅ Interactive Command Line Interface
✅ Performance Metrics Calculation (Average Waiting Time)
🧠 Concepts Covered
Process Scheduling
Ready Queue Management
Time Sharing (Round Robin)
Priority-based Execution
Multilevel Queue Systems
Algorithm Comparison
🏗️ Project Structure
.
├── main.cpp        # Core implementation
├── scheduler logic # FCFS, SJF, RR, Priority, Multilevel Queue
├── process model   # Process class and attributes
▶️ How to Run
1. Compile
g++ main.cpp -o scheduler
2. Execute
./scheduler
🖥️ Sample Menu
Choose a scheduling algorithm:
1. FCFS
2. SJF
3. Priority Scheduling
4. Round Robin
5. Multilevel Queue Scheduling
8. Display Processes
9. Generate New Processes
0. Exit
📊 Example Output
FCFS Scheduling:
Process   Burst Time   Priority   Waiting Time
0         5            2          0
1         3            1          5
2         8            3          8

Average Waiting Time: 4.33
🔧 Technologies Used
C++
STL (Vectors, Algorithms)
CLI-based interface
🚀 Future Improvements
Add Gantt Chart visualization
File-based input/output
GUI version (Qt / Web)
Multithreading simulation
Real-time process input
🎯 Learning Outcomes
Strong understanding of CPU scheduling algorithms
Practical implementation of OS concepts
Improved problem-solving and debugging skills
Hands-on experience with system-level programming
👨‍💻 Author

Jay Shankar

📧 jayshankarkrsingh8877@gmail.com
🔗 GitHub: (add your link)
💼 LinkedIn: (add your link)
⭐ Contribution

Feel free to fork the project, raise issues, or suggest improvements!
