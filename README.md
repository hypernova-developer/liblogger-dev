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
