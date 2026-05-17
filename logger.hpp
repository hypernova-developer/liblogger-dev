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

    std::string get_current_time()
    {
        auto now = std::chrono::system_clock::now();
        auto in_time_t = std::chrono::system_clock::to_time_t(now);
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
            now.time_since_epoch()) % 1000;
        
        char buf[20];
        std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", std::localtime(&in_time_t));
        return std::string(buf) + "." + std::to_string(ms.count());
    }

    std::string level_to_string(LogLevel level)
    {
        switch (level)
        {
            case LogLevel::INFO:     
                return "INFO";
            case LogLevel::WARNING:  
                return "WARNING";
            case LogLevel::ERROR:    
                return "ERROR";
            case LogLevel::CRITICAL: 
                return "CRITICAL";
        }
        return "UNKNOWN";
    }

    void process_logs()
    {
        while (true)
        {
            std::unique_lock<std::mutex> lock(log_mutex);
            cv.wait(lock, [this]() { return !log_queue.empty() || stop_worker; });

            while (!log_queue.empty())
            {
                if (log_file.is_open())
                {
                    log_file << log_queue.front() << std::endl;
                }
                std::cout << log_queue.front() << std::endl;
                log_queue.pop();
            }

            if (stop_worker && log_queue.empty())
            {
                break;
            }
        }
    }

public:
    Logger(const std::string& filename) : stop_worker(false)
    {
        log_file.open(filename, std::ios::app);
        worker_thread = std::thread(&Logger::process_logs, this);
    }

    ~Logger()
    {
        {
            std::lock_guard<std::mutex> lock(log_mutex);
            stop_worker = true;
        }
        cv.notify_one();
        if (worker_thread.joinable())
        {
            worker_thread.join();
        }
        if (log_file.is_open())
        {
            log_file.close();
        }
    }

    void log(LogLevel level, const std::string& message)
    {
        std::string formatted = "[" + get_current_time() + "] [" + level_to_string(level) + "] " + message;
        {
            std::lock_guard<std::mutex> lock(log_mutex);
            log_queue.push(formatted);
        }
        cv.notify_one();
    }
};

#endif
