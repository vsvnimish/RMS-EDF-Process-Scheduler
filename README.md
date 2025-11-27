# 🖥️ RMS & EDF Scheduling Simulation

> **C++ Implementations of Rate Monotonic Scheduling (RMS) and Earliest Deadline First (EDF) Algorithms**
> Simulate process scheduling, analyze deadlines, and measure performance.

---

## 📁 Repository Contents

| File                      | Description                              |
| ------------------------- | ---------------------------------------- |
| `inp-params.txt`          | Input file containing process parameters |
| `Assgn2-RMSCS19B1026.cpp` | RMS scheduling implementation            |
| `Assgn2-EDFCS19B1026.cpp` | EDF scheduling implementation            |

---

## ⚡ Quick Start

Make sure all files are in the **same directory** before running.

### 🟢 Run RMS Code

1. Compile:

```bash
g++ Assgn2-RMSCS19B1026.cpp -o p
```

2. Execute:

* Linux/macOS:

```bash
./p.out
```

* Windows:

```bash
p.exe
```

3. Output:

| File           | Purpose                   |
| -------------- | ------------------------- |
| `RM-Stats.txt` | RMS statistics            |
| `RMS-Log.txt`  | RMS process execution log |

---

### 🔵 Run EDF Code

1. Compile:

```bash
g++ Assgn2-EDFCS19B1026.cpp -o p
```

2. Execute:

* Linux/macOS:

```bash
./p.out
```

* Windows:

```bash
p.exe
```

3. Output:

| File            | Purpose                   |
| --------------- | ------------------------- |
| `EDF-Stats.txt` | EDF statistics            |
| `EDF-Log.txt`   | EDF process execution log |

---

## 📊 Process Structure

Each process has the following key attributes:

| Attribute         | Description                                 |
| ----------------- | ------------------------------------------- |
| ⏱️ Available Time | Time at which process is ready to execute   |
| 🎯 Deadline Time  | Time by which process must finish execution |
| 🔁 Occur          | Number of times the process has executed    |
| ⏳ Remaining Time  | Time left for process to complete execution |

---

## ⚙️ Key Functions

* `setup_process(y)` — Move process `y` to its next period, updating all fields.
* `isdeadlinemissed(y)` — Checks if process `y` will miss its deadline.
* `can_prempt_and_deadline(x, y)` — Determines if process `x` can preempt `y` without missing its deadline.
* `preempt(x)` — Returns the index of a process that can preempt `x`, or `-1`.
* `process_selector()` — Selects the next process based on priority (RMS) or earliest deadline (EDF).

---

## 📝 RMS Algorithm

* **Priority**: Shorter period → higher priority
* **Execution**: Preemption allowed if higher-priority process is ready
* **Timer**: Tracks current execution time
* **Logs**: Deadline misses and waiting times recorded

---

## 📝 EDF Algorithm

* **Priority**: Earliest deadline → higher priority
* **Execution**: Preemption allowed if a process with an earlier deadline is ready
* **Timer**: Tracks current execution time
* **Logs**: Deadline misses and waiting times recorded

---

## 📈 Performance Analysis

### Deadlines Missed (Graph 1)

* RMS usually has **≥ deadlines missed** compared to EDF
* EDF favors early-deadline processes → higher schedulability

### Waiting Time (Graph 2)

* RMS often has **lower average waiting time** because high-priority processes complete earlier
* EDF may have longer waiting times when processes execute just before their deadlines

---

## 🔍 Observations

* RMS is better when process periods vary widely
* EDF is advantageous for strict early-deadline scenarios
* Input can influence which algorithm performs better

---

## ⚠️ Notes

* Ensure `inp-params.txt` and both source files are in the **same directory**
* Logs/statistics files overwrite on each execution
* Compatible with **Linux** and **Windows**

---

> 🚀 Enjoy exploring scheduling behavior with RMS & EDF!
> 💡 Tip: Check the generated logs to compare deadlines and waiting times visually.
