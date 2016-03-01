#ifndef _SYSTYPES_H_
#define _SYSTYPES_H_

#include <stdbool.h>

#define __BIT(x)        (1L<<(x))
#define __NULL(x)       (0L<<(x))       

typedef unsigned char U8;
typedef unsigned short U16;
typedef unsigned long int U32;
typedef signed long int S32;
typedef unsigned long long U64;
typedef char A16C[16];
typedef char A32C[32];

typedef signed char I8;
typedef short int I16;
typedef long int I32;
typedef long long I64;

#endif