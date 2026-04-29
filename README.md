# 🔧 RTOS-Projects

![FreeRTOS](https://img.shields.io/badge/FreeRTOS-Based-brightgreen?style=flat-square&logo=freertos)
![Language](https://img.shields.io/badge/Language-C-blue?style=flat-square&logo=c)
![Platform](https://img.shields.io/badge/Platform-Embedded-orange?style=flat-square)
![License](https://img.shields.io/badge/License-MIT-lightgrey?style=flat-square)

A collection of hands-on **Real-Time Operating System (RTOS)** projects built using **FreeRTOS**, covering core concepts from task management and scheduling to inter-task communication and synchronization primitives.

---

## 📖 What is RTOS?

A **Real-Time Operating System (RTOS)** is a specialized operating system designed to serve real-time applications that process data and events deterministically within strict timing constraints. Unlike general-purpose operating systems, an RTOS guarantees that critical tasks are executed within a defined time window, making it essential in embedded systems, robotics, automotive electronics, medical devices, and industrial automation.

**Key characteristics of an RTOS:**
- **Determinism** – Predictable and consistent response times
- **Preemptive Scheduling** – High-priority tasks can preempt lower-priority ones
- **Inter-Task Communication** – Mechanisms like queues, semaphores, and mutexes enable safe data sharing
- **Lightweight** – Optimized for resource-constrained microcontrollers

**FreeRTOS** is one of the most widely used open-source RTOS kernels, supporting dozens of microcontroller architectures and trusted in millions of embedded devices worldwide.

---

## 📁 Project Structure

```
RTOS-Projects/
│
├── Free_RTOS/                  # FreeRTOS kernel setup and introduction
├── RTOS_Tasks/                 # Basic task creation and management
├── RTOS_queues_nopriority/     # Queue-based inter-task communication (no priority)
├── TASK_Operations/            # Task operations: suspend, resume, delete
├── Task_Priority_execution/    # Priority-based task scheduling and execution
├── 06RTOS_Semaphores/          # Binary semaphore for synchronization
├── 07RTOS_Queue_ISR/           # Queue communication between tasks and ISR
├── 08RTOS_USERINTERRUPT/       # User-triggered interrupt handling with queues
├── 09RTOS_prioritty_inv/       # Priority inversion demonstration and analysis
├── 10RTOS_SEMAPHORE_COUNTER/   # Counting semaphores for resource management
└── 11RTOS_Mutex/               # Mutex for mutual exclusion and deadlock prevention
```

---

## 🚀 Projects Overview

| # | Project | Concept | Description |
|---|---------|---------|-------------|
| 01 | `Free_RTOS` | Kernel Setup | FreeRTOS initialization and basic configuration |
| 02 | `RTOS_Tasks` | Task Management | Creating, running, and managing multiple tasks |
| 03 | `RTOS_queues_nopriority` | Queues | Passing data between tasks using FreeRTOS queues |
| 04 | `TASK_Operations` | Task Control | Suspend, resume, and delete tasks dynamically |
| 05 | `Task_Priority_execution` | Scheduling | Observing preemptive scheduling with task priorities |
| 06 | `06RTOS_Semaphores` | Binary Semaphore | Task synchronization using binary semaphores |
| 07 | `07RTOS_Queue_ISR` | Queue + ISR | Sending data from an ISR to a task via queue |
| 08 | `08RTOS_USERINTERRUPT` | User Interrupt | Handling user-triggered hardware interrupts |
| 09 | `09RTOS_prioritty_inv` | Priority Inversion | Demonstrating the priority inversion problem |
| 10 | `10RTOS_SEMAPHORE_COUNTER` | Counting Semaphore | Managing multiple resource instances |
| 11 | `11RTOS_Mutex` | Mutex | Preventing race conditions with mutual exclusion locks |

---

## 🧠 Concepts Covered

- ✅ Task Creation, Priority, and Scheduling
- ✅ Task States: Running, Ready, Blocked, Suspended
- ✅ FreeRTOS Queues for Inter-Task Communication
- ✅ Queue from ISR (Interrupt Service Routines)
- ✅ Binary Semaphores for Task Synchronization
- ✅ Counting Semaphores for Resource Management
- ✅ Mutex and Mutual Exclusion
- ✅ Priority Inversion Problem
- ✅ User Interrupts and Event Handling

---

## 🛠️ Getting Started

### Prerequisites

- **IDE**: STM32CubeIDE / Keil MDK / VS Code with PlatformIO
- **RTOS**: FreeRTOS (integrated via STM32CubeMX or manually)
- **Hardware**: STM32 (or compatible ARM Cortex-M board) *(or any supported MCU)*
- **Toolchain**: ARM GCC

### Clone the Repository

```bash
git clone https://github.com/Amrutkumarbh/RTOS-Projects.git
cd RTOS-Projects
```

### Running a Project

1. Open the desired project folder in your IDE
2. Configure the target microcontroller if needed
3. Build and flash to your hardware
4. Use a serial monitor to observe task output

---

## 📚 References

- [FreeRTOS Official Documentation](https://www.freertos.org/Documentation/RTOS_book.html)
- [FreeRTOS API Reference](https://www.freertos.org/a00106.html)
- [STM32CubeIDE](https://www.st.com/en/development-tools/stm32cubeide.html)
- [Mastering the FreeRTOS Real Time Kernel – Free PDF](https://www.freertos.org/Documentation/161204_Mastering_the_FreeRTOS_Real_Time_Kernel-A_Hands-On_Tutorial_Guide.pdf)

---

## 🤝 Contributing

Contributions are welcome! If you'd like to add a new RTOS project or improve an existing one:

1. Fork this repository
2. Create a new branch: `git checkout -b feature/your-project-name`
3. Commit your changes: `git commit -m "Add: your project description"`
4. Push to the branch: `git push origin feature/your-project-name`
5. Open a Pull Request

---

## 👤 Author

**Amrutkumarbh**  
📌 [GitHub Profile](https://github.com/Amrutkumarbh)

---

## 📄 License

This project is licensed under the [MIT License](LICENSE).

---

> *"Understanding RTOS is the gateway to building reliable, real-time embedded systems."*
