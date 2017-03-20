#include "screen.h"
#include <stdio.h>

//function definitions
void clearScreen(void){
        printf("\033[2J");
        fflush(stdout);
}

void setFGcolor(int fg){        // fg is a value between 30 and 37
        printf("\033[%d;1m", fg);
        fflush(stdout);         // send out the esc sequence to terminal
}

void resetColors(void){
        printf("\033[0m");
        fflush(stdout);
}

void gotoXY(int row, int col){
        // row number should be 1-30, col should be 1-80
        printf("\033[%d;%dH", row, col);
        fflush(stdout);
}

void displayBar(double rms, int col){
        int i;
        for(i=0; i<rms/100; i++){
                gotoXY(i+2, col);
#ifndef UNICODE
                printf("*");
#else
		printf("%s", BAR);
#endif
        }
        fflush(stdout);
}
