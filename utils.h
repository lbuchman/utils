#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>


#ifdef __cplusplus
extern "C"
{
#endif
    
    
void hexdump(const void * memory, size_t bytes);


#ifdef __cplusplus
}
#endif
#endif
