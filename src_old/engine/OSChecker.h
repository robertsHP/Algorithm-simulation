#include "windows.h"

namespace RawEngine {

    #if defined(_WIN32) || defined(_WIN64)
        #define OS_REMOVE(name) remove(name)
        #define OS_RENAME(new,old) rename(new,old)

        #define OS_FOUND true
    #elif defined(__MACH__) || defined(__APPLE__)
        #define OS_FOUND true
    #elif defined(__linux__)
        #define OS_FOUND true
    #endif // defined

    #ifndef OS_FOUND
        #define OS_FOUND false
    #endif // OS_FOUND

}
