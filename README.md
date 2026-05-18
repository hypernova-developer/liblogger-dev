# liblogger-dev

A high-performance, asynchronous, zero-dependency logging library implemented in pure C++ without namespaces, utilizing the elegant **Allman Style** formatting. Designed for maximum throughput and minimal overhead, it serves as a robust foundational component for the SyntaX ecosystem.

## Features

- **Pure C++ Power:** No external dependencies required. Uses modern standard library features.
- **Asynchronous Architecture:** Offloads disk I/O operations to a dedicated worker thread, preventing core program execution blocks.
- **Thread-Safe Queue:** Mutex and condition variable mechanisms ensure stable cross-thread log production and consumption.
- **Millisecond Precision:** Detailed timestamps calculated at execution runtime.
- **Namespace-Free Design:** Global accessibility for rapid integration into system drivers and low-level modules.
- **Allman Style Formatting:** Perfect bracket alignment for ultimate code readability and aesthetic consistency.

## Architecture & Code Style

The library enforces the **Allman Style**, where every curly brace `{}` occupies its own dedicated line. This alignment ensures structural clarity and matches high-performance system standards.

### Core Implementation Preview (`betterlogger.hpp`)

```cpp
#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <string>
#include <fstream>
#include <mutex>
#include <queue>
#include <thread>
#include <condition_variable>
#include <iostream>
#include <chrono>
#include <ctime>

enum class LogLevel
{
    INFO,
    WARNING,
    ERROR,
    CRITICAL
};

class Logger
{
private:
    std::ofstream log_file;
    std::mutex log_mutex;
    std::queue<std::string> log_queue;
    std::thread worker_thread;
    std::condition_variable cv;
    bool stop_worker;
    // ...
};

#endif
```
## Quick Start & Integration
## Quick Start & Integration

### 1. Include and Initialize
Drop `betterlogger.hpp` into your project directory. Instantiating the class will automatically initialize the asynchronous logger and start the internal worker thread.

```cpp
#include "betterlogger.hpp"

int main()
{
    Logger logger("system.log");

    logger.log(LogLevel::INFO, "System initialized successfully.");
    logger.log(LogLevel::WARNING, "Testing asynchronous boundary limits.");
    logger.log(LogLevel::ERROR, "Simulated runtime error handled safely.");
    logger.log(LogLevel::CRITICAL, "System execution context verification required.");

    return 0;
}
```

### 2. Compilaation
Compile using any standard C++11 or higher compliant compiler with threading support enabled:
```bash
g++ -std=c++11 main.cpp -o system_logger -lpthread
```

## Severity Levels

The engine filters log outputs across four clear, explicit tiers to optimize analysis profiles:
- `INFO` : Standard operational feedback data.
- `WARNING` : Non-critical deviations requiring review.
- `ERROR` : Runtime failures causing partial data degradation.
- `CRITICAL` : Immediate failures threatening system thread execution context stability.

## Project Philosophy
Part of the hypernova-developer library development ecosystem. Engineered with the mindset of: *First small components, then complete ecosystems.*

## Licensing
This project is protected under the **GNU GPL v3.0 License**. All rights reserved by **hypernova-developer**.

## Completed
**liblogger-dev** project is completed. 18/05/2026 23:13
