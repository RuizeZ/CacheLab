#include "cachelab.h"
#include <getopt.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define SIZE 100

void readargv(int argc, char* argv[]);
void enQueue(unsigned *setaddr);
unsigned* deQueue();
void simulate();

int HelpFlag, VerboseFlag, SetIndexBits, LinesPerSet, BlockBits;
int hit = 0, miss = 0, evictions = 0;
char filename[50];
unsigned *items[SIZE];
int front = -1, rear = -1;
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
    unsigned setindex, tag;
    unsigned *setaddr, *pi;
    unsigned linesize = pow(2, BlockBits)+2;

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
        pi = malloc(pow(2, SetIndexBits) * LinesPerSet * linesize * sizeof(int));
        //printf("pi = %p\n", pi);
        while(fscanf(pFile, " %c %x,%d", &identifier, &address, &size)>0)	
        {	
            
            if(identifier == ' ')
            {
                continue;
            }
            else
            {
                // Separate address into differnt part in cache
                // blockoffset = (address << (32 - BlockBits)) >> (32 - BlockBits);
                setindex = (address << (32 - BlockBits - SetIndexBits)) >> (32 - SetIndexBits);
                tag = address >> (BlockBits + SetIndexBits);
                // printf("blockoffset = %d\n", blockoffset);
                // printf("setindex = %d\n", setindex);
                // printf("tag = %d\n", tag);

                //find the set
                setaddr = pi + (setindex * linesize);
                // printf("setaddr %p\n", setaddr);
                enQueue(setaddr);
                //if miss
                identifier_M:
                // printf("tag = %d\n", tag);
                // printf("*(setaddr + 1) = %d\n", *(setaddr + 1));
                if ((tag != *(setaddr + 1)) || (!*setaddr) )
                {
                    //printf("miss\n");
                    miss++;
                    setaddr = deQueue();
                    //printf("current setaddr %p\n", setaddr);
                    *setaddr = 1;
                    *(setaddr + 1) = tag;
                    if(identifier == 'M'){
                        goto identifier_M;
                    }
                }
                else
                {
                    //printf("hit\n");
                    hit++;
                }
                
                // //if data load
                // if(identifier == 'L')
                // {
                    
                // //if miss

                    
                // }
                // else if(identifier == 'M')
                // {

                // }
                // else if(identifier == 'S'){

                // }
            }
            
        }
    }
    



    
}
void enQueue(unsigned * setaddr) {
    if (rear == SIZE - 1)
    printf("Queue is Full!!\n");
    else {
        if (front == -1)
            front = 0;
        rear++;
        items[rear] = setaddr;
        // printf("Inserted -> %p\n", items[rear]);
    }
}

unsigned* deQueue() {
    unsigned * currentsetaddr;
    if (front == -1)
        printf("Queue is Empty!!\n");
    else {
        currentsetaddr = items[front];
        // printf("Deleted : %p\n", items[front]);
        front++;
        if (rear != 0)
        {
            //printf("eviction\n");
            evictions++;
        }
        
        if (front > rear)
            front = rear = -1;
    }
    return currentsetaddr;
}






int main(int argc, char* argv[])
{
    readargv(argc, argv);
    simulate();
    printSummary(hit, miss, evictions);
    return 0;
}
