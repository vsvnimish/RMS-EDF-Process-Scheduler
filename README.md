╔══════════════════════════════════════════════════════╗
║           🖥️  RMS & EDF Scheduling Simulation       ║
╚══════════════════════════════════════════════════════╝

C++ Implementations of Rate Monotonic Scheduling (RMS)
and Earliest Deadline First (EDF) Algorithms.
Simulate process scheduling, analyze deadlines, and measure performance.

## Tech Stack

* Language   : C++
* Compiler   : g++ (GNU Compiler Collection)
* Platform   : Linux, Windows, macOS
* Output     : Text-based logs and statistics files

## Repository Contents

RMS_ProcessScheduler.cpp   : RMS scheduling implementation
EDF_ProcessScheduler.cpp   : EDF scheduling implementation

## Quick Start

Make sure all files are in the same directory before running.

## 🟢 Run RMS Code

1. Compile:
   g++ RMS_ProcessScheduler.cpp -o p

2. Execute:
   Linux/macOS: ./p.out
   Windows    : p.exe

3. Output:
   RM-Stats.txt  : RMS statistics
   RMS-Log.txt   : RMS process execution log

## 🔵 Run EDF Code

1. Compile:
   g++ EDF_ProcessScheduler.cpp -o p

2. Execute:
   Linux/macOS: ./p.out
   Windows    : p.exe

3. Output:
   EDF-Stats.txt : EDF statistics
   EDF-Log.txt   : EDF process execution log

## Process Structure

Available Time   : Time at which process is ready to execute
Deadline Time    : Time by which process must finish execution
Occur            : Number of times the process has executed
Remaining Time   : Time left for process to complete execution

## Key Functions

setup_process(y)             : Move process y to its next period, updating all fields
isdeadlinemissed(y)         : Checks if process y will miss its deadline
can_prempt_and_deadline(x,y): Determines if process x can preempt y without missing its deadline
preempt(x)                  : Returns index of process that can preempt x, or -1
process_selector()          : Selects the next process based on priority (RMS) or earliest deadline (EDF)

## RMS Algorithm

* Priority: Shorter period = higher priority
* Timer keeps track of current time
* Process array sorted by priority
* Preemption & deadline checks ensure deadlines are not missed
* Process selection chooses highest priority ready process

## EDF Algorithm

* Priority: Earliest deadline = higher priority
* Timer keeps track of current time
* Preemption & deadline checks similar to RMS
* Process selection chooses process with earliest deadline

## Analysis

* RMS may miss more deadlines if high-period processes are skipped
* EDF may have more waiting time if long processes execute near deadlines
* Performance varies depending on process parameters

## Notes

* Input parameters can be hardcoded or read from a file
* RMS & EDF logs/statistics will be generated in the same directory
* Compile & execute each program separately
