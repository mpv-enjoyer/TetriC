#ifndef MISC_H
#define MISC_H

#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <string.h>

#ifndef NDEBUG
 #define D_ASSERT(expr) if (!(expr)) raise(SIGSEGV);
#else
 #define D_ASSERT(expr)
#endif

#ifndef __cplusplus
 typedef unsigned char bool;
 static const bool false = 0;
 static const bool true = 1;
#endif

const char* to_string(int number);

#endif