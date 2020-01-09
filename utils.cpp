
#include <utils.h>
#include <limits.h>
#include <ctype.h>


/*****************************************************************


* *************************************************************
*/
void hexdump(const void * memory, size_t bytes) {
    const unsigned char * p, * q;
    int i;


    p = (unsigned char *) memory;

    while(bytes) {
        q = p;
        printf("%p: ", (void *) p);

        for(i = 0; i < 16 && bytes; ++i) {
            printf("%02X ", *p);
            ++p;
            --bytes;
        }

        bytes += i;

        while(i < 16) {
            printf("XX ");
            ++i;
        }

        printf("| ");
        p = q;

        for(i = 0; i < 16 && bytes; ++i) {
            printf("%c", isprint(*p) && !isspace(*p) ? *p : ' ');
            ++p;
            --bytes;
        }

        while(i < 16) {
            printf(" ");
            ++i;
        }

        printf(" |\n\r");
    }

    return;
}

