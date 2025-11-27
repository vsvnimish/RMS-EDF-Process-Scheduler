# 🖥️ RMS & EDF Scheduling Simulation

> C++ Implementations of Rate Monotonic Scheduling (RMS) and Earliest Deadline First (EDF) Algorithms
> Simulate process scheduling, analyze deadlines, and measure performance.

---

## 📁 Repository Contents

| File                     | Description                              |
| ------------------------ | ---------------------------------------- |
| inp-params.txt           | Input file containing process parameters |
| RMS_ProcessScheduler.cpp | RMS scheduling implementation            |
| EDF_ProcessScheduler.cpp | EDF scheduling implementation            |

---

## ⚡ Quick Start

Make sure all files are in the same directory before running.

### 🟢 Run RMS Code

1. Compile:

```
g++ RMS_ProcessScheduler.cpp -o p
```

2. Execute:

Linux/macOS:

```
./p.out
```

Windows:

```
p.exe
```

3. Output:

| File         | Purpose                   |
| ------------ | ------------------------- |
| RM-Stats.txt | RMS statistics            |
| RMS-Log.txt  | RMS process execution log |

---

### 🔵 Run EDF Code

1. Compile:

```
g++ EDF_ProcessScheduler.cpp -o p
```

2. Execute:

Linux/macOS:

```
./p.out
```

Windows:

```
p.exe
```

3. Output:

| File          | Purpose                   |
| ------------- | ------------------------- |
| EDF-Stats.txt | EDF statistics            |
| EDF-Log.txt   | EDF process execution log |

---

## 📊 Process Structure

Each process has the following key attributes:

| Attribute      | Description                                 |
| -------------- | ------------------------------------------- |
| Available Time | Time at which process is ready to execute   |
| Deadline Time  | Time by which process must finish execution |
| Occur          | Number of times the process has executed    |
| Remaining Time | Time left for process to complete execution |

---

## ⚙️ Key Functions

* setup_process(y) — Move process y to its next period, updating all fields
* isdeadlinemissed(y) — Checks if process y will miss its deadline
* can_prempt_and_deadline(x, y) — Determines if process x can preempt y without missing its deadline
* preempt(x) — Returns the index of a process that can preempt x, or -1
* process_selector() — Selects the next process based on priority (RMS) or earliest deadline (EDF)

---

## 📝 RMS Algorithm

* Priority: Shorter period has higher priority
* Timer keeps track of current time
* Process array is sorted by priority
* Preemption and deadline checks ensure process deadlines are not missed
* Process selection chooses the highest priority ready process

---

## 📝 EDF Algorithm

* Priority: Earliest deadline has higher priority
* Timer keeps track of current time
* Preemption and deadline checks similar to RMS
* Process selection chooses the ready process with earliest deadline

---

## 📊 Analysis

* RMS may have more deadlines missed when high-period processes are skipped
* EDF may have more waiting time if it executes long processes near their deadlines
* Graph analysis shows RMS can outperform EDF in certain scenarios and vice versa depending on process parameters

---

## 🖇️ Notes

* All input parameters are in `inp-params.txt`
* RMS and EDF logs/statistics will be generated in the same directory
* Make sure to compile and execute each program separately
