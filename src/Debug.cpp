#include "Debug.h"

    std::string Debug::logText = "";

    void Debug::print (std::string txt) {
        std::cout << txt;
    }
    void Debug::println (std::string txt) {
        std::cout << txt << std::endl;
    }
    void Debug::log (const std::string type, const std::string message, const std::string codeLoc) {
        std::time_t currentTime;
        std::tm *localTime;
        std::stringstream stream;

        currentTime = std::time(0);
        localTime = localtime(&currentTime);
        stream << (localTime->tm_year + 1900) << '-' 
                << (localTime->tm_mon + 1) << '-' 
                << localTime->tm_mday << ' '
                << localTime->tm_hour << ':' 
                << localTime->tm_min << ':' 
                << localTime->tm_sec << ' '
                << type << '|';
        if(codeLoc != "")
            stream << codeLoc << '|';
        stream << message;
        std::cout << stream.str() << std::endl;
        Debug::logText += stream.str();
    }
    void Debug::saveLog () {
        std::time_t currentTime;
        std::tm *localTime;
        std::ofstream out;
        std::string finName;
        std::stringstream stream;

        currentTime = std::time(0);
        localTime = localtime(&currentTime);
        stream << localTime->tm_mday << '-' << localTime->tm_mon << '-' << localTime->tm_year << '-'
               << localTime->tm_hour << '-' << localTime->tm_min << '-' << localTime->tm_sec;
        finName = "CrashLog" + stream.str() + ".txt";
        out.open(finName);
        out << Debug::logText;
        out.close();
    }
