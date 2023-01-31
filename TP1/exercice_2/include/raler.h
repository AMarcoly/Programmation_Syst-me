#ifndef _RALER_H
#define _RALER_H

#include <stdio.h>
#include <stdarg.h>
#include <stdnoreturn.h>
#include <stdlib.h>

#define CHK(op) do { if ( (op) == NULL) raler (1,#op);  } while(0)
#define CHK2(op) do { if ( (op) == -1) raler (1,#op);  } while(0)

noreturn void raler(int syserr,  const char *msg, ...);
#endif

