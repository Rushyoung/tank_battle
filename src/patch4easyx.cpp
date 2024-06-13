// if you want to use easyx in MinGW, you should include this file in your project.
#ifdef __MINGW32__

#include <stdio.h>

extern "C" FILE * __cdecl __imp___iob_func(void){
    return _iob;
}

#endif