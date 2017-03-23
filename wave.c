#include "wave.h"
#include <stdio.h>
#include <math.h>
#include "screen.h"
#include "comm.h"
void  testTone( int freq, double d)
{
        FILE *fp;
        int i;
        WAVHDR h;
        short int sample;
        fp = fopen("testtone.wav","w");
        fillID("RIFF", h.ChunkID);
        fillID("WAVE",h.Format);
        fillID("fmt ", h.Subchunk1ID);
        h.Subchunk1Size = 16;
        h.AudioFormat = 1;
        h.NumChannels = 1;
        h.SampleRate = SAMPLE_RATE;
        h.BitsPerSample = 16;
        h.ByteRate = SAMPLE_RATE * h.NumChannels * (h.BitsPerSample/8);
        h.BlockAlign= h.NumChannels * (h.BitsPerSample/8);
        fillID("data", h.Subchunk2ID);
        h.Subchunk2Size = (int)h.ByteRate * d;
        h.ChunkSize = h.Subchunk2Size + 36;
        fwrite(&h, sizeof(h),1,fp);
        for ( i=0; i<d*SAMPLE_RATE; i++)
        {
                sample = 32768*sin(2*PI*freq*i/SAMPLE_RATE);
                fwrite(&sample, sizeof(sample), 1, fp);
        }
}
void displayWAVHDR(WAVHDR hdr)
{
        double duration;
	duration=(double)hdr.Subchunk2Size/hdr.ByteRate;
#ifdef DEBUG
        printf("Chunk ID"); printID(hdr.ChunkID);
        printf("Chunk Size: %d\n",hdr.ChunkSize);
        printf("Format : "); printID(hdr.Format);
        printf("Subchunk1 ID :");printID(hdr.Subchunk1ID);
        printf("SubChunk1 Size : %d\n", hdr.Subchunk1Size);
        printf("Audio Format : %d\n", hdr.AudioFormat);
        printf("Num of Channels ; %d\n",hdr.NumChannels);
        printf("Sample Rate: %d\n", hdr.SampleRate);
        printf("Byte Rate: %d\n",hdr.ByteRate);
        printf("Block Align %d\n", hdr.BlockAlign);
        printf("Bits Per Sample: %d\n", hdr.BitsPerSample);
        printf("Subchunk2 ID "); printID(hdr.Subchunk2ID);
        printf("SubChunk2 Size : %d\n",hdr.Subchunk2Size);
        printf("duration of Audio %.3f\n",duration);
#else
	gotoXY(1, 1);	setFGcolor(RED); printf("%.2f sec", duration);
	gotoXY(1, 10);	setFGcolor(CYAN); printf("%d bit/s", hdr.BitsPerSample);
	gotoXY(1, 20);	setFGcolor(YELLOW); printf("%d sps", hdr.SampleRate);
	resetColors();
#endif
}
void printID(char id[])
{
        int i;
        for (i=0; i<4;i++)
                putchar(id[i]);
printf("\n");
}
void fillID( const char *s, char d[])
{
        int i;
        for (i=0; i<4;i++)  d[i]=*s++;
}
void displayWAVdata(short int d[])
{
        int i,j;
        double sum200,rms200, max200=0.0, min200=20000.0;
	double Leqf[8], sum2000=0.0;

        for (i=0; i<80;++i)
        {
                sum200=0.0;
                for (j=0;j<SAMPLE_RATE/80; ++j)
                        {
                                sum200+= (*d)*(*d);
                                d++;
                        }
			sum2000+=sum200;
			if(i%10==9){
				Leqf[i/10]=sqrt(sum2000/SAMPLE_RATE/8);
				sum2000=0.0;
			}
                rms200=sqrt(sum200/(SAMPLE_RATE/80));
		rms200=20*log10(rms200);
		if(rms200<min200) min200=rms200;
		if(rms200>max200) max200=rms200;
#ifdef DEBUG	//conditional compilling
		printf("%d %10.2f",i,rms200);
#else
		displayBar(rms200, i+1);
#endif
        }
#ifdef DEBUG
	printf("\nmin = %.2f, max = %.2f\n", min200, max200);
#endif
#ifdef COMM
	send_data_curl(Leqf);
#endif 
}

