#include <Arduino.h>
#include <utils.h>
#include <limits.h>



/*!
 ********************************************************************
 * brief
 *
 *
 * return
 ********************************************************************
 */
bool expired_interval(size_t& timer, size_t interval, size_t& prev_run_time, char* name, bool debug) {
    size_t timenow = millis();

    if(timer >  timenow) {
        return false;
    }
    else {
        prev_run_time = timenow;
        timer = timenow + interval;
        return true;
    }

    return false;
}


/*****************************************************************


* *************************************************************
*/
unsigned int stringToBcd(char *buffer, int hole, int frac) {
    unsigned int ret = 0;
    int i = 0;

    for(i = 0; i < (hole); i++) {
        if(buffer[i] == '.') {
            if(!frac) {
                return ret;
            }

            continue;
        }

        if(i) {
            ret = ret << 4;
        }

        ret |= (buffer[i] - '0') & 0x0F;
    }

    return ret;
}


/*****************************************************************


* *************************************************************
*/
unsigned int doubleToBcd(double number, int hole, int frac) {
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
double CheckLimits(double min, double max, double value, String desc) {
    if((value < min) || (value > max)) {
        // logme(kLogError, "%s:%d  %s Limit Error %2.2lf-%2.2lf value = %2.2lf", POS_LOG_ARG,desc.c_str(), min,max,value );
        return 0.0l;
    }

    return value;
}

/*****************************************************************


* *************************************************************
*/
float CheckLimits1(float min, float max, float value, String desc) {
    if((value < min) || (value > max)) {
        return 0.0;
    }

    return value;
}

/*****************************************************************


* *************************************************************
*/
int CheckLimits(int min, int max, int value) {
    if((value < min) || (value > max)) {
        return -1;
    };

    return value;
}



/*****************************************************************


* *************************************************************
*/
/*****************************************************************


* *************************************************************
*/
void hexdump(const void * memory, size_t bytes) {
    const unsigned char * p, * q;
    uint32_t prevDumpFile = 0;
    int i;
    boolean printTimetsamp = true;

    if(!Serial) {
        return;
    }

    p = (unsigned char *) memory;

    while(bytes) {
        q = p;
        uint32_t timeNow = micros();

        if(printTimetsamp) {
            Serial.printf("%11.3f  %7.3f  ", timeNow / 1000.0, (timeNow - prevDumpFile) / 1000.0);
        }
        else {
            Serial.printf("%s", (char*) "                      ");
        }

        prevDumpFile = timeNow;
        printTimetsamp = false;

        for(i = 0; i < 16 && bytes; ++i) {
            Serial.printf("%02X ", *p);
            ++p;
            --bytes;
        }

        bytes += i;

        while(i < 16) {
            Serial.printf("XX ");
            ++i;
        }

        Serial.printf("| ");
        p = q;

        for(i = 0; i < 16 && bytes; ++i) {
            Serial.printf("%c", isprint(*p) && !isspace(*p) ? *p : ' ');
            ++p;
            --bytes;
        }

        while(i < 16) {
            Serial.printf(" ");
            ++i;
        }

        Serial.printf(" |\n\r");
    }

    Serial.println();
    return;
}

/*****************************************************************
 *
 *
 * *************************************************************
 */
uint32_t rotl32(uint32_t n, unsigned int c) {
    const unsigned int mask = (CHAR_BIT * sizeof(n) - 1);      // assumes width is a power of 2.
    // assert ( (c<=mask) &&"rotate by type width or more");
    c &= mask;
    return (n << c) | (n >> ((-c) &mask));
}

/*****************************************************************


* *************************************************************
*/
uint32_t rotr32(uint32_t n, unsigned int c) {
    const unsigned int mask = (CHAR_BIT * sizeof(n) - 1);
    // assert ( (c<=mask) &&"rotate by type width or more");
    c &= mask;
    return (n >> c) | (n << ((-c) &mask));
}

