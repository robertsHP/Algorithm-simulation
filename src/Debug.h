#ifndef DEBUG_H
#define DEBUG_H

#include <string>
#include <iostream>
#include <fstream>
#include <ctime>
#include <sstream>

#define _CODELOC_ __PRETTY_FUNCTION__

class Debug {
    private:
        static std::string logText;

    public:
        static void print (std::string txt);
        static void println (std::string txt);
        static void log (
            const std::string type, const std::string message, const std::string codeLoc = _CODELOC_);
        static void saveLog ();
};

#endif // DEBUG_H
