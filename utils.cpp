#include <Arduino.h>
#include <utils.h>
#include <log.h>

/****************************************************************************/
/* return temp in C   */
/****************************************************************************/
float moving_window_average(int dat, Window& window)
{
    window.window_total -= window.window[window.window_idx];
    window.window_total += dat;
    window.window[window.window_idx] = dat;
    window.window_idx = (window.window_idx < (MOVING_WINDOW_SIZE - 1)) ? (window.window_idx + 1) : 0;
    return (window.window_total / MOVING_WINDOW_SIZE);
}

/*!
 ********************************************************************
 * brief
 *
 *
 * return
 ********************************************************************
 */
bool expired_interval(size_t& timer, size_t interval, size_t& prev_run_time, char* name, bool debug)
{
    size_t timenow = millis();

    if(timer >  timenow)
    {
        return false;
    }
    else
    {
        prev_run_time = timenow;
        timer = timenow + interval;
        return true;
    }

    return false;
}


/*****************************************************************


* *************************************************************
*/
unsigned int stringToBcd(char *buffer, int hole, int frac)
{
    unsigned int ret = 0;
    int i = 0;

    for(i = 0; i < (hole); i++)
    {
        if(buffer[i] == '.')
        {
            if(!frac)
            {
                return ret;
            }

            continue;
        }

        if(i)
        {
            ret = ret << 4;
        }

        ret |= (buffer[i] - '0') & 0x0F;
    }

    return ret;
}


/*****************************************************************


* *************************************************************
*/
unsigned int doubleToBcd(double number, int hole, int frac)
{
    unsigned int ret;
    char buffer[32];
    char format[32];
    sprintf(format, "%%%d.%df", hole, frac);
    sprintf(buffer, format, number);
    ret = stringToBcd(buffer, hole, frac);
    return ret;
}
/*****************************************************************


* *************************************************************
*/
double CheckLimits(double min, double max, double value, String desc)
{
    if((value < min) || (value > max))
    {
        // logme(kLogError, "%s:%d  %s Limit Error %2.2lf-%2.2lf value = %2.2lf", POS_LOG_ARG,desc.c_str(), min,max,value );
        return 0.0l;
    }

    return value;
}

/*****************************************************************


* *************************************************************
*/
float CheckLimits1(float min, float max, float value, String desc)
{
    if((value < min) || (value > max))
    {
        logme(kLogError, "%s:%d  %s Limit Error %2.2f-%2.2f value = %2.2f", POS_LOG_ARG, desc.c_str(), min, max, value);
        return 0.0;
    }

    return value;
}

/*****************************************************************


* *************************************************************
*/
int CheckLimits(int min, int max, int value, String desc)
{
    if((value < min) || (value > max))
    {
        logme(kLogError, "%s:%d %s  Limit Error %d-%d value = %d", POS_LOG_ARG, desc.c_str(), min, max, value);
        return 0;
    };

    return value;
}


/*****************************************************************


* *************************************************************
*/
void hexdump(const void * memory, size_t bytes)
{
    const unsigned char * p, * q;
    int i;
    p = (unsigned char *) memory;
    Serial.println("Hex Dump");

    while(bytes)
    {
        q = p;
        Serial.printf("%p: ", (void *) p);

        for(i = 0; i < 12 && bytes; ++i)
        {
            Serial.printf("%02X ", *p);
            ++p;
            --bytes;
        }

        bytes += i;

        while(i < 12)
        {
            Serial.printf("XX ");
            ++i;
        }

        Serial.printf("| ");
        p = q;

        for(i = 0; i < 12 && bytes; ++i)
        {
            Serial.printf("%c", isprint(*p) && !isspace(*p) ? *p : ' ');
            ++p;
            --bytes;
        }

        while(i < 12)
        {
            Serial.printf(" ");
            ++i;
        }

        Serial.printf(" |\n\r");
    }

    return;
}
