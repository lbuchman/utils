#ifndef UTILS_H
#define UTILS_H


#ifdef __cplusplus
extern "C"
{
#endif
    
unsigned int stringToBcd(char *buffer, int hole, int frac);
unsigned int doubleToBcd(double number, int hole, int frac);
int CheckLimits(int min, int max, int value);
void hexdump(const void * memory, size_t bytes);
uint32_t rotl32(uint32_t n, unsigned int c);
uint32_t rotr32(uint32_t n, unsigned int c);

#ifdef __cplusplus
}
#endif

#endif
