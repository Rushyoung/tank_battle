#include <stdio.h>

extern "C" FILE * __cdecl __imp___iob_func(void){
    return _iob;
}