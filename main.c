/*This program is just for testing */
#include"wave.h"
#include<stdio.h>
#include<math.h>
#include<signal.h>
#include<sys/wait.h>
#include"screen.h"

//this program will open a wave file and display header info
int main(int argc, char *argv[]){
        FILE *fp;
        WAVHDR myhdr;
	short int sa[SAMPLE_RATE];
	int answer, ret;
/*        if(argc != 2){
                printf("Usage: %s wav_file\n", argv[0]);
                return -1;
        }
        fp = fopen(argv[1], "r");       //try to open the wav file
        if(fp == NULL){
                printf("Cannot  fine file %s\n", argv[1]);
                return -1;
        }*/
	while(1){
		ret = system("arecord -r16000 -c1 -d1 -f S16_LE -q data.wav");
		clearScreen();	//a fresh screen to display
		if(WIFSIGNALED(ret) && (WTERMSIG(ret)==SIGINT || WTERMSIG(ret)==SIGQUIT))break;
		fp = fopen("data.wav", "r");
        	fread(&myhdr, sizeof(myhdr), 1, fp);
        	displayWAVHDR(myhdr);
		fread(&sa, sizeof(short int), SAMPLE_RATE, fp);
		displayWAVdata(sa);
        	fclose(fp);
	}
	printf("Do u want to generate a test tone? (1:yes, 0:no)\n");
	scanf("%d", &answer);
	if(answer==1) testTone(1000, 5);
}

