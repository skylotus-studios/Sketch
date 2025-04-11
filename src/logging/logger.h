#pragma once
#include <iostream>
#include <string>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <format>
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
    static void enableAnsiColors() {
#if defined(_WIN32)
        const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        DWORD dwMode = 0;
        GetConsoleMode(hOut, &dwMode);
        dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
        SetConsoleMode(hOut, dwMode);
#endif
    }

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
            resetColor();
            std::cout << "Engine Shutting Down. Press Enter to Exit...\n";
            std::cin.get();
            exit(1);
        }
        if (level != LogLevel::SPECIAL) {
            std::cout << timestamp() << tag(level) << message << std::endl;
        } else {
            std::cout << message << std::endl;
        }
        resetColor();
    }
public:
    logger() {
        enableAnsiColors();
        log("  ---[[WELCOME TO SKETCH ENGINE!]]---  ");
    }

#ifdef SKETCH_DEBUG
    template <typename... Args>
    void debug(std::format_string<Args...> fmt, Args&&... args) {
        print(LogLevel::TEST, std::format(fmt, std::forward<Args>(args)...));
    }
#else
    template <typename... Args>
    void debug(std::format_string<Args...> fmt, Args&&... args) {} // stripped in release
#endif
    template <typename... Args>
    void info(std::format_string<Args...> fmt, Args&&... args) {
        print(LogLevel::INFO, std::format(fmt, std::forward<Args>(args)...));
    }
    template <typename... Args>
    void warn(std::format_string<Args...> fmt, Args&&... args) {
        print(LogLevel::WARN, std::format(fmt, std::forward<Args>(args)...));
    }
    template <typename... Args>
    void error(std::format_string<Args...> fmt, Args&&... args) {
        print(LogLevel::FAIL, std::format(fmt, std::forward<Args>(args)...));
    }
    template <typename... Args>
    void log(std::format_string<Args...> fmt, Args&&... args) {
        print(LogLevel::SPECIAL, std::format(fmt, std::forward<Args>(args)...));
    }
};