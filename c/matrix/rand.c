#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    uint8_t start = 0x01;
    uint8_t a = start;
    int i;    
    for(i = 1;; i++) {
        int newbit = (((a >> 5) ^ (a >> 4)) & 1);
        a = ((a << 1) | newbit) & 0x3f;

        //if ( a > 63 ) { i--; continue; }

        printf("%d, ", a);
        if (a == start) {
            printf("\nrepetition period is %d\n", i);
            break;
        }
    }
}
