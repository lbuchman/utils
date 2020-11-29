#ifndef UTILS_H
#define UTILS_H

#include <log.h>

#ifdef __cplusplus
extern "C"
{
#endif
unsigned int stringToBcd(char *buffer, int hole, int frac);
unsigned int doubleToBcd(double number, int hole, int frac);
int CheckLimits(int min, int max, int value);
bool expired_interval(size_t& timer, size_t interval);
void hexdump(const void * memory, size_t bytes, boolean printTimetsamp = false, LogLevel loglevel = kLogTrace);
uint32_t rotl32(uint32_t n, unsigned int c);
uint32_t rotr32(uint32_t n, unsigned int c);
bool IsDST(int day, int month, int dow);

#ifdef __cplusplus
}
#endif

#endif
