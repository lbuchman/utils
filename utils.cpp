#include <Arduino.h>
#include <utils.h>
#include <limits.h>
#include <log.h>

/*!
 ********************************************************************
 *
 *
 *
 * return true if summer time, otherwise false
 ********************************************************************
 */
bool IsDST(int day, int month, int dow) {
    //January, february, and december are out.
    if(month < 3 || month > 11) {
        return false;
    }

    //April to October are in
    if(month > 3 && month < 11) {
        return true;
    }

    int previousSunday = day - dow;

    //In march, we are DST if our previous sunday was on or after the 8th.
    if(month == 3) {
        return previousSunday >= 8;
    }

    //In november we must be before the first sunday to be dst.
    //That means the previous sunday must be before the 1st.
    return previousSunday <= 0;
}


/*!
 ********************************************************************
 * brief
 * size_t& timer shall be global variables
 *
 * return
 ********************************************************************
 */
bool expired_interval(size_t& timer, size_t interval) {
    size_t timenow = millis();

    if(timer >  timenow) {
        return false;
    }
    else {
        timer = timenow + interval;
        return true;
    }

    return false;
}


/*****************************************************************


* *************************************************************
*/
void hexdump(const void * memory, size_t bytes, boolean printTimetsamp, LogLevel loglevel) {

    if(loglevel > getLogLevel()) {
        return;
    }

    const  char * p, * q;
    int i;

    if(!Serial) {
        return;
    }

    p = (char *) memory;


    while(bytes) {
        q = p;
        uint32_t timeNow = micros();

        if(printTimetsamp) {
            printme(NO_CR, NO_TIMESTAMP, "[%7d]  ", timeNow);
        }
        else {
            printme(NO_CR, NO_TIMESTAMP, "%s", (char*) "                      ");
        }

        printTimetsamp = false;

        for(i = 0; i < 16 && bytes; ++i) {
            printme(NO_CR, NO_TIMESTAMP, "%02X ", (char) *p);
            ++p;
            --bytes;
        }

        bytes += i;

        while(i < 16) {
            printme(NO_CR, NO_TIMESTAMP, "XX ");
            ++i;
        }

        printme(NO_CR, NO_TIMESTAMP, "| ");
        p = q;

        for(i = 0; i < 16 && bytes; ++i) {
            printme(NO_CR, NO_TIMESTAMP, "\033[1;32m%c\033[0m", isprint(*p) && !isspace(*p) ? (char)*p : ' ');
            ++p;
            --bytes;
        }

        while(i < 16) {
            printme(NO_CR, NO_TIMESTAMP, " ");
            ++i;
        }

        printme(NO_CR, NO_TIMESTAMP, " |\n\r");
    }

    printme(NO_CR, NO_TIMESTAMP, "\n\r");
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
