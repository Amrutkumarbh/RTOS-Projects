# 🔧 RTOS-Projects

![FreeRTOS](https://img.shields.io/badge/FreeRTOS-Based-brightgreen?style=flat-square&logo=freertos)
![Language](https://img.shields.io/badge/Language-C-blue?style=flat-square&logo=c)
![Platform](https://img.shields.io/badge/Platform-Embedded-orange?style=flat-square)
![License](https://img.shields.io/badge/License-MIT-lightgrey?style=flat-square)

A collection of hands-on **Real-Time Operating System (RTOS)** projects built using **FreeRTOS**, covering core concepts from task management and scheduling to inter-task communication and synchronization primitives.

---

# 🧠 RTOS Projects — FreeRTOS Learning Journey

> A hands-on documentation of my journey into Real-Time Operating Systems using **FreeRTOS** on **STM32F407** microcontrollers. Each folder is a standalone project covering a specific RTOS concept — built, tested, and documented as I learn.

---

## 📌 About This Repository

This repo is not a finished product — it's a **living record of learning**. I add projects daily as I explore FreeRTOS concepts from the ground up. The goal is to build a deep, practical understanding of real-time embedded systems while maintaining clean, well-documented code.

**Platform:** STM32F407 Discovery Board  
**RTOS:** FreeRTOS (via STM32CubeIDE HAL integration)  
**Language:** Embedded C  
**IDE:** STM32CubeIDE

---

## 📚 RTOS — Theory & Core Concepts

Before diving into projects, here's a concise reference for the foundational concepts used throughout this repo.

### What is an RTOS?

A **Real-Time Operating System (RTOS)** is a lightweight OS designed for embedded systems where tasks must execute within strict timing deadlines. Unlike a general-purpose OS (Linux, Windows), an RTOS provides:

- **Deterministic timing** — tasks run when they're supposed to, not when the OS "gets around to it"
- **Preemptive multitasking** — higher-priority tasks can interrupt lower-priority ones
- **Minimal footprint** — runs on microcontrollers with kilobytes of RAM

> FreeRTOS is one of the most widely used open-source RTOSes in the embedded industry, supported by STM32 natively through CubeIDE.

---

### 🔷 Core Concepts

#### 1. Tasks
A **task** in FreeRTOS is similar to a thread. Each task is an independent function with its own:
- Stack memory
- Priority level (0 = lowest, configMAX_PRIORITIES-1 = highest)
- State: **Running**, **Ready**, **Blocked**, **Suspended**

```c
// Creating a task
xTaskCreate(vMyTask,        // Task function
            "MyTask",       // Task name (for debug)
            128,            // Stack depth (words)
            NULL,           // Parameters
            1,              // Priority
            &xTaskHandle);  // Task handle
```

#### 2. The Scheduler
The FreeRTOS **scheduler** decides which task runs at any given moment. It uses a **priority-based preemptive** algorithm:
- The highest-priority **Ready** task always runs
- Tasks of equal priority share CPU via **Round-Robin** time-slicing
- The scheduler runs every **tick** (typically 1ms, configurable via `configTICK_RATE_HZ`)

#### 3. Task States

```
           ┌─────────────────────────────────────┐
           │                                     ▼
        [Created] ──► [Ready] ◄──── [Running] ──► [Deleted]
                         ▲              │
                         │    (block)   ▼
                         └──── [Blocked / Suspended]
```

| State | Description |
|---|---|
| **Running** | Currently executing on the CPU |
| **Ready** | Waiting for CPU, all dependencies met |
| **Blocked** | Waiting for an event (delay, queue, semaphore) |
| **Suspended** | Manually paused via `vTaskSuspend()` |

#### 4. Queues
A **queue** is a FIFO buffer used to safely pass data **between tasks** or between an **ISR and a task**. It is the primary inter-task communication mechanism in FreeRTOS.

```c
// Create a queue that holds 10 uint32_t values
xQueueHandle = xQueueCreate(10, sizeof(uint32_t));

// Send to queue (from a task)
xQueueSend(xQueueHandle, &data, portMAX_DELAY);

// Receive from queue
xQueueReceive(xQueueHandle, &receivedData, portMAX_DELAY);
```

#### 5. Semaphores & Mutexes
Used for **synchronization** and **resource protection**:

| Type | Use Case |
|---|---|
| **Binary Semaphore** | Signal between tasks or ISR→Task |
| **Counting Semaphore** | Track multiple resource instances |
| **Mutex** | Protect shared resources (with priority inheritance) |

#### 6. Task Priority & Priority Inversion
- Higher numerical priority = higher importance
- **Priority Inversion**: A low-priority task holds a resource needed by a high-priority task — solved using **Mutexes** (not binary semaphores) due to priority inheritance

#### 7. Stack & Heap
- Each task gets its **own stack** — sized at creation
- FreeRTOS manages heap using one of 5 memory schemes (`heap_1` through `heap_5`)
- Stack overflow detection: enable `configCHECK_FOR_STACK_OVERFLOW` in `FreeRTOSConfig.h`

#### 8. `vTaskDelay` vs `vTaskDelayUntil`

```c
vTaskDelay(pdMS_TO_TICKS(500));           // Delay 500ms from now
vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(500));  // Delay until fixed period (preferred for periodic tasks)
```

`vTaskDelayUntil` ensures **consistent execution periods** regardless of how long the task itself took to run.

#### 9. Tick & Time in FreeRTOS
- The system tick drives the scheduler
- Use `pdMS_TO_TICKS(ms)` to convert milliseconds to tick counts — never hardcode tick values

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

### 🔬 Project Highlights

#### `Free_RTOS` — Getting Started
The starting point of this journey. Covers:
- Setting up FreeRTOS in STM32CubeIDE
- Creating and starting the first task
- Understanding `osKernelStart()` and why code after it never runs
- UART debug output to observe task execution

#### `RTOS_Tasks` — Working with Multiple Tasks
Explores how FreeRTOS manages multiple concurrent tasks:
- Creating tasks with different priorities
- Observing round-robin scheduling for equal-priority tasks
- Using `vTaskDelay()` to yield CPU

#### `Task_Priority_execution` — Preemption in Action
Demonstrates real preemptive behavior:
- High-priority task preempts a running low-priority task
- Visualizing scheduler decisions through UART output
- Understanding why priority assignment matters in real systems

#### `TASK_Operations` — Task Lifecycle Control
Hands-on with the full task state machine:
- `vTaskSuspend()` / `vTaskResume()`
- `vTaskDelete()` and memory reclamation
- Task handles and managing tasks from other tasks

#### `RTOS_queues_nopriority` — Inter-Task Communication
First look at FreeRTOS queues:
- Creating a queue and passing data between producer/consumer tasks
- Blocking behavior when queue is full or empty
- `portMAX_DELAY` vs finite timeout

---

## 🛠️ Setup & How to Use

```
1. Clone the repository
   git clone https://github.com/Amrutkumarbh/RTOS-Projects.git

2. Open any project folder in STM32CubeIDE
   File → Open Projects from File System → Select the project folder

3. Build and flash to STM32F407 Discovery Board
   Project → Build All → Run → Debug

4. Open a serial terminal (115200 baud) to view UART debug output
```

**Requirements:**
- STM32CubeIDE (v1.x or later)
- STM32F407 Discovery Board
- USB-to-Serial adapter (for UART output if not using SWV)

---

## 🗺️ Roadmap

Upcoming topics I plan to explore and document:

- [ ] Semaphores & Mutexes
- [ ] Software Timers
- [ ] Event Groups
- [ ] Stream Buffers & Message Buffers
- [ ] ISR-safe FreeRTOS APIs (`FromISR` variants)
- [ ] Stack overflow detection
- [ ] FreeRTOS + I2C peripheral integration
- [ ] FreeRTOS + DMA
- [ ] `configUSE_TRACE_FACILITY` and runtime stats

---

## 📖 References

- [FreeRTOS Official Documentation](https://www.freertos.org/Documentation/RTOS_book.html)
- [Mastering the FreeRTOS Kernel — Free PDF](https://www.freertos.org/Documentation/161204_Mastering_the_FreeRTOS_Real_Time_Kernel-A_Hands-On_Tutorial_Guide.pdf)
- [STM32CubeIDE + FreeRTOS Setup Guide](https://wiki.st.com/stm32mcu/wiki/Introduction_to_FreeRTOS)
- [Shawn Hymel's FreeRTOS Series (YouTube)](https://www.youtube.com/playlist?list=PLEBQazB0HUyQ4hAPU1cJED6t3DU0h34bz)

---

## 👤 About

**Amrut Kumar** — Embedded systems enthusiast learning RTOS, STM32, and low-level C from the ground up.  
📍 Currently exploring: FreeRTOS on STM32F407  
🔗 [STM32 Projects Repo](https://github.com/Amrutkumarbh) | [LinkedIn](#)

---

<div align="center">
  <i>Built one project at a time — understanding first, code second.</i>
</div> *"Understanding RTOS is the gateway to building reliable, real-time embedded systems."*
