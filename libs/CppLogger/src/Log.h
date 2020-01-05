//
// Created by Emilien Lemaire on 04/12/2019.
//

#pragma once

#include <iostream>
#include <map>
#include <utility>

class Log {
public:
    enum Level{
        LevelFatal = 0, LevelError, LevelWarn, LevelInfo, LevelDebug
    };
private:
    struct Console {
        std::string name;
        Log::Level level;
        Console(std::string name, Log::Level level)
            :name(std::move(name)), level(level)
            {}
    };
    static Log *s_Instance;
    static std::map<std::string, Log::Console> m_ConsolesMap;
    explicit Log(const Log::Console& console);
    static void init(const Console &console);

public:
    ~Log();

    static void createConsole(const std::string& t_Name, Level t_Level);

    template<class T>
    static void printFatal(const std::string& name, T fatal, const std::string& file, int line){
        auto it = m_ConsolesMap.find(name);
        if (it == m_ConsolesMap.end()){
            std::cerr << "The console " << name << " was never added to Log" << std::endl;
            return;
        }
        Console console = it->second;
        if (console.level >= LevelFatal) std::cout << "\033[31m[" << console.name << "] Fatal error: \033[35m"<< file << ":" << line << ": \033[31m" << fatal << "\033[m" << std::endl;
        exit(EXIT_FAILURE);
    }
    template<class T>
    static void printErr(const std::string& name, T err, const std::string& file, int line){
        auto it = m_ConsolesMap.find(name);
        if (it == m_ConsolesMap.end()){
            std::cerr << "The console " << name << " was never added to Log" << std::endl;
            return;
        }
        Console console = it->second;
        if (console.level >= LevelError) std::cout << "\033[31m[" << console.name << "] Error: \033[35m"<< file << ":" << line << ": \033[31m" << err << "\033[m" << std::endl;
    }
    template<class T>
    static void printWarning(const std::string& name, T warn, const std::string& file, int line){
        auto it = m_ConsolesMap.find(name);
        if (it == m_ConsolesMap.end()){
            std::cerr << "The console " << name << " was never added to Log" << std::endl;
            return;
        }
        Console console = it->second;
        if (console.level >= LevelWarn) std::cout << "\033[33m[" << console.name << "] Warning: \033[35m" << file << ":" << line << ": \033[33m" << warn << "\033[m" << std::endl;
    }
    template<class T>
    static void printInfo(const std::string& name, T info){
        auto it = m_ConsolesMap.find(name);
        if (it == m_ConsolesMap.end()){
            std::cerr << "The console " << name << " was never added to Log" << std::endl;
            return;
        }
        Console console = it->second;
        if (console.level >= LevelInfo) std::cout << "\033[32m[" << console.name << "] Info: " << info << "\033[m" << std::endl;
    }

    template<class T>
    static void printDebug(const std::string& name, T debug){
        auto it = m_ConsolesMap.find(name);
        if (it == m_ConsolesMap.end()){
            std::cerr << "The console " << name << " was never added to Log" << std::endl;
            return;
        }
        Console console = it->second;
        std::string test = "\033";
        if (console.level >= LevelDebug) std::cout << "\033[34m[" << console.name << "] Debug: " << debug << "\033[m" << std::endl;
    }
};

#define Fatal(x, y) Log::printFatal(x, y, __FILE__, __LINE__)
#define Error(x, y) Log::printErr(x, y, __FILE__, __LINE__)
#define Warn(x, y) Log::printWarning(x, y, __FILE__, __LINE__)
#define Info(x, y) Log::printInfo(x, y)
#define Debug(x, y) Log::printDebug(x, y)