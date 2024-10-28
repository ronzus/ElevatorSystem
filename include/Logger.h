#pragma once

#include <mutex>
#include <string>

enum class LogLevel
  {
    DEBUG,
    INFO,
    WARNING,
    ERROR,
  };

class Logger {
    private:
    
    std::mutex logLock;
    
    public:

    Logger(const std::string& filename);

    void log(LogLevel log_level, const std::string& message);

};