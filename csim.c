#include "cachelab.h"
#include <getopt.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void readargv(int argc, char* argv[]);
void simulate();

int HelpFlag, VerboseFlag, SetIndexBits, LinesPerSet, BlockBits;
char filename[50];
FILE *pFile;

void readargv(int argc, char* argv[])
{
    int opt;
    while(-1 != (opt = getopt(argc, argv, "hvs:E:b:t:"))){
        /* determine which argument it’s processing*/
        switch(opt) {
            case 'h':
            HelpFlag = 1;
            break;
            case 'v':
            VerboseFlag = 1;
            break;
            case 's':
            SetIndexBits = atoi(optarg);
            break;
            case 'E':
            LinesPerSet = atoi(optarg);
            break;
            case 'b':
            BlockBits = atoi(optarg);
            break;
            case 't':
            pFile = fopen(optarg, "r");
            break;
            default:
            printf("wrong argument\n");
            break;
        }
    }
}

void simulate(){
    char identifier;
    unsigned address;	
    int	size;	
    if (HelpFlag == 1)
    {
        printf("Usage: ./csim-ref [-hv] -s <num> -E <num> -b <num> -t <file>\n");
        printf("Options:\n");
        printf("  -h         Print this help message.\n");
        printf("  -v         Optional verbose flag.\n");
        printf("  -s <num>   Number of set index bits.\n");
        printf("  -E <num>   Number of lines per set.\n");
        printf("  -b <num>   Number of block offset bits.\n");
        printf("  -t <file>  Trace file.\n");
        printf("\n");
        printf("Examples:\n");
        printf("  linux>  ./csim-ref -s 4 -E 1 -b 4 -t traces/yi.trace\n");
        printf("  linux>  ./csim-ref -v -s 8 -E 2 -b 4 -t traces/yi.trace\n");
        exit(0);
    }
    else
    {
        while(fscanf(pFile, " %c %x,%d", &identifier, &address, &size)>0)	
        {	
            if(identifier == ' ')
            {
                continue;
            }
            else
            {
                
            }
            
        }
    }
    



    
}

int main(int argc, char* argv[])
{
    readargv(argc, argv);
    simulate();
    // printSummary(0, 0, 0);
    return 0;
}
