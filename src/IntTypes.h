

#pragma once


#ifdef _WIN32
    #include <windef.h>
#elif __linux__
    #include <stdint.h>
#elif __APPLE__
    #include <stdint.h>
#endif
