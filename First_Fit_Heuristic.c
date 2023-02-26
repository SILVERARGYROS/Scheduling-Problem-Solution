// Libraries
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Debug constants
#define DEBUG 1
#define CLEAR_SCREEN 1
#define DEBUG_SORT 1
#define DEBUG_INDEX 1
#define DEBUG_CORE_DUMP 1
#define FIXED_EXAMPLE 0
#define RANDOM_PICK 1

// Color palette, source:https://stackoverflow.com/questions/3585846/color-text-in-terminal-applications-in-unix
#define RED		"\x1B[31m"
#define BLUE	"\x1B[36m"
#define GREEN	"\x1B[32m"
#define DEF		"\x1B[0m"

// Global Variables
int weeksNumber = 4;
int* low;
int* high;
int i;
int j;
clock_t start, end;
double cpu_time_used;

// Job Structure
typedef struct Jobs{
    int value;
    int start;
    int finish;
} Job;

int main (void){
    if(CLEAR_SCREEN){system("tput clear");}

    if(FIXED_EXAMPLE){
        if(DEBUG){printf(GREEN "Loading Fixed Example...\n\n" DEF);}
        weeksNumber = 4;
        low = (int*)malloc(sizeof(int) * (weeksNumber));
        high = (int*)malloc(sizeof(int) * (weeksNumber));

        low[0] = 10;
        low[1] = 1;
        low[2] = 10;
        low[3] = 10;
        high[0] = 5;
        high[1] = 50; 
        high[2] = 5;
        high[3] = 1;

        if(DEBUG){
            for(i = 0; i < weeksNumber; i++)
            {
                printf(GREEN "week %d: L = %d H = %d\n" DEF, i+1, low[i], high[i]);
            }
            printf("\n");
        }
    }
    else{
        printf("Please enter the number of weeks: ");
        do{
            scanf("%d", &weeksNumber);
            if(weeksNumber <= 0){
                printf("Please enter a proper positive integer: ");
            }
        }while(weeksNumber <= 0);

        low = (int*)malloc(sizeof(int) * (weeksNumber));
        high = (int*)malloc(sizeof(int) * (weeksNumber));

        if(RANDOM_PICK)
        {
            for(i = 0; i < weeksNumber; i++)
            {
                low[i] = rand() % 41 + 10;
            }
            for(i = 0; i < weeksNumber; i++)
            {
                high[i] = rand() % 41 + 90;
            }

            // printing the randomly generated job categories
            for(i = 0; i < weeksNumber; i++)
            {
                printf("low[%d] = %d\n", i, low[i]);
            }
            printf("\n");
            for(i = 0; i < weeksNumber; i++)
            {
                printf("high[%d] = %d\n", i, high[i]);
            }
        }
        else
        {
            for(i = 0; i < weeksNumber; i++)
            {
                printf("Please enter value of low skill job for week %d: ", i+1);
                scanf("%d", &low[i]);
            }
            for(i = 0; i < weeksNumber; i++)
            {
                printf("Please enter value of high skill job for week %d: ", i+1);
                scanf("%d", &high[i]);
            }
        }
    }

    // Initializing supporting "calendar" array
    int* work_week = (int*)malloc(sizeof(int)*weeksNumber);
    for(i = 0; i < weeksNumber; i++)
    {
        work_week[i] = 0;
    }
    int sum = 0;

    // Setting up timer to measure execution time of Dikjstra. 
    start = clock();

    //First Fit Heuristic Algorithm
    for(i = 0; i < weeksNumber;)
    {
        if(i == 0)
        {
            if(low[i] >= high[i])
            {
                printf("On week %d we do the low skill job.\n", i+1);
                sum += low[i];
            }   
            else
            {
                printf("On week %d we do the high skill job.\n", i+1);
                sum += high[i];
            }
            work_week[i] = 1;
        }
        else if(high[i] > low[i-1] + low[i])
        {
            printf("On week %d and %d we do the high skill job.\n", i, i+1);
            sum += high[i];
            work_week[i] = 1;
            work_week[i-1] = 1;
        }
        else
        {
            printf("On week %d we do the low skill job.\n", i);
            sum += low[i - 1];
            printf("On week %d we do the low skill job.\n", i+1);
            sum += low[i];
            work_week[i] = 1;
            work_week[i-1] = 1;
        }
        i += 2;
    }
    if(work_week[weeksNumber-1] == 0)
    {
        printf("On week %d we do the low skill job.\n", weeksNumber);
        sum += low[weeksNumber-1];
    }
    printf(GREEN "Final Total earned: %d\n" DEF, sum);

    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf("\n First-Fit algorith was executed in %f seconds\n", cpu_time_used);
}

int max(int a, int b)
{
    // return (a>=b)*a + (b>a)*b;

    if(a >=b)
    {
        return a;
    }
    else
    {
        return b;
    }
}