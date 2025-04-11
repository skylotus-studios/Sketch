#pragma once
#include <iostream>
#include <string>
#include <ctime>
#include <iomanip>
#include <sstream>
#if defined(_WIN32)
    #include <windows.h>
#endif

enum class LogLevel {
    TEST,
    INFO,
    WARN,
    FAIL,
    SPECIAL
};

class logger {
private:
    static std::string tag(const LogLevel level) {
        switch (level) {
            case LogLevel::TEST: return " [TEST] ";
            case LogLevel::INFO: return " [INFO] ";
            case LogLevel::WARN: return " [WARN] ";
            case LogLevel::FAIL: return " [FAIL] ";
            default: return "";
        }
    }

    static void setColor(const LogLevel level) {
        switch (level) {
            case LogLevel::TEST: std::cout << "\033[38;2;178;235;148m"; break;      // Green
            case LogLevel::INFO: std::cout << "\033[38;2;210;210;210m"; break;      // Gray
            case LogLevel::WARN: std::cout << "\033[38;2;255;255;150m"; break;      // Yellow
            case LogLevel::FAIL: std::cout << "\033[38;2;255;110;110m"; break;      // Red
            default: std::cout << "\033[48;2;150;150;150m\033[38;2;0;0;0m"; break;  // Black
        }
    }

    static void resetColor() {
        std::cout << "\033[0m";
    }

    static std::string timestamp() {
        const std::time_t now = std::time(nullptr);
        std::tm localTime{};
        localtime_s(&localTime, &now);
        std::ostringstream oss;
        oss << std::put_time(&localTime, "[%H:%M:%S]");
        return oss.str();
    }

    static void print(LogLevel level, const std::string& message) {
        setColor(level);
        if (level == LogLevel::FAIL) {
            std::cerr << timestamp() << tag(level) << message << std::endl;
        } else if (level != LogLevel::SPECIAL) {
            std::cout << timestamp() << tag(level) << message << std::endl;
        } else {
            std::cout << message << std::endl;
        }
        resetColor();
    }
public:
    logger() {
        log("  ---[[WELCOME TO SKETCH ENGINE!]]---  ");
    }
    ~logger() {
        log("Shutting Down...");
    }

#ifdef SKETCH_DEBUG
    void debug(const std::string& message) {
        print(LogLevel::TEST, message);
    }
#else
    void debug(const std::string&) {} // stripped in release
#endif
    void info(const std::string& message) {
        print(LogLevel::INFO, message);
    }
    void warn(const std::string& message) {
        print(LogLevel::WARN, message);
    }
    void error(const std::string& message) {
        print(LogLevel::FAIL, message);
    }
    void log(const std::string& message) {
        print(LogLevel::SPECIAL, message);
    }
};