#include <Arduino.h>
#include <utils.h>
#include <limits.h>
#include <log.h>


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
    
    if (loglevel > getLogLevel()) return;

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
            printme(NO_CR, NO_TIMESTAMP,"[%7d]  ", timeNow);
        }
        else {
            printme(NO_CR, NO_TIMESTAMP,"%s", (char*) "                      ");
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

