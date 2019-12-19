#ifndef UTILS_H
#define UTILS_H

#define  MOVING_WINDOW_SIZE 20

struct Window {
    int window[MOVING_WINDOW_SIZE];
    int window_idx;
    long int window_total;
};

float moving_window_average(int dat, Window& window);
unsigned int stringToBcd(char *buffer, int hole, int frac);
unsigned int doubleToBcd(double number, int hole, int frac);
bool expired_interval(size_t& timer, size_t interval, size_t& prev_run_time, char* name, bool debug);
double CheckLimits(double min, double max, double value, String desc);
//float CheckLimits(float min, float max, float value);
int CheckLimits(int min, int max, int value, String desc);
void hexdump(const void * memory, size_t bytes);
uint32_t rotl32(uint32_t n, unsigned int c);
uint32_t rotr32(uint32_t n, unsigned int c);
#endif
