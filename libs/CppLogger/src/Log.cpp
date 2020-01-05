//
// Created by Emilien Lemaire on 08/12/2019.
//
#include "Log.h"

Log* Log::s_Instance = nullptr;
std::map<std::string, Log::Console> Log::m_ConsolesMap;

void Log::init(const Log::Console& console){
    if(!s_Instance){
        s_Instance = new Log(console);
        return;
    }
    auto it = m_ConsolesMap.find(console.name);
    if (it != m_ConsolesMap.end()){
        std::cerr << "The console " << console.name << " is already defined" << std::endl;
        return;
    }
    m_ConsolesMap.insert({console.name, console});
}

void Log::createConsole(const std::string& t_Name, Log::Level t_Level) {
    Console console(t_Name, t_Level);
    auto it = m_ConsolesMap.find(console.name);
    if (it != m_ConsolesMap.end()){
        std::cerr << "The console " << console.name << " is already defined" << std::endl;
        return;
    }
    m_ConsolesMap.insert({t_Name, console});
}

Log::~Log() {
    delete s_Instance;
}

Log::Log(const Log::Console& console) {
    m_ConsolesMap.insert({console.name, console});
}
