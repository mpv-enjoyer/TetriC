#ifndef MISC_H
#define MISC_H

#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <string.h>
#include <malloc.h>
#include <stdbool.h>
#include <assert.h>

#ifdef _WIN32
#include <stdio.h>
#endif

#ifndef NDEBUG
 #define D_ASSERT(expr) assert(expr)
#else
 #define D_ASSERT(expr)
#endif

#ifndef __cplusplus
 #define nullptr (void*)0
#endif

#if RAYLIB_VERSION_MAJOR > 5 || ( RAYLIB_VERSION_MAJOR == 5 && RAYLIB_VERSION_MINOR >= 5 )
 #define IsTextureReady(texture) IsTextureValid(texture)
#endif

#define LOOP_PLUS(value, base) ((value + 1) % base)
#define LOOP_MINUS(value, base) ((value + (base - 1)) % base)

#define MIN(l, r) l < r ? l : r
#define MAX(l, r) l > r ? l : r

void* tMalloc(size_t size);
#define TMALLOC(T) (T*)tMalloc(sizeof(T))

typedef struct tString
{
    char* data;
    size_t size;
} tString;

tString* tAllocString();
size_t tActualStringSize(tString* string);
void tAppendString(tString* string, char c);
size_t tSizeUntilCharString(const tString *string, size_t begin, char c);
void tFreeString(tString *string);

void shuffle(int *array, size_t n);
int random_int(int left_bound, int right_bound);


#endif