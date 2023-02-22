//debug constant
#define DEBUG 1

//color constants, source:https://stackoverflow.com/questions/3585846/color-text-in-terminal-applications-in-unix
#define RED		"\x1B[31m"
#define BLUE	"\x1B[36m"
#define GREEN	"\x1B[32m"
#define DEF		"\x1B[0m"

#include <stdio.h>
#include <stdlib.h>

int weeksNumber = 4;

typedef struct Jobs{
    int value;
    int start;
    int finish;
} Job;

int max(int a, int b);
int latestNonConflict(Job* job, int i);
int main (void){
    int i;

    // printf("Please enter the number of weeks: ");
    // scanf("%d", weeksNumber);
    
    int* low = (int*)malloc(sizeof(int) * (weeksNumber + 1));
    int* high = (int*)malloc(sizeof(int) * (weeksNumber + 1));

    low[0] = 10;
    low[1] = 1;
    low[2] = 10;
    low[3] = 10;
    high[0] = 5;
    high[1] = 50; 
    high[2] = 5;
    high[3] = 1;

    int n = weeksNumber * 2;
    Job* job = (Job*)malloc(sizeof(Job) * (n));
    Job* job2 = (Job*)malloc(sizeof(Job) * (n));
    Job* temp;

    // Initiallizing job array
    for(i = 0; i < n; i++)
    {
        if(i < n/2)
        {
            job[i].start = i+1;
            job[i].finish = job[i].start+1;
            job[i].value = low[i];
        }
        else
        {
            job[i].start = i%(n/2);
            job[i].finish = job[i].start+2;
            job[i].value = high[i%(n/2)];
        }
    }

    if(DEBUG){printf(GREEN "Debug before core dump 1\n" DEF);}

    // Ordering job array to spare sorting complexity
    i = 0;
    do
    {
        int j;
        for(j = (i < n/2); j < n; j = j+2)
        {
            if(DEBUG){printf("Debug i = %d\n", i);}
            if(DEBUG){printf("Debug j = %d\n", j);}
            job2[j] = job[i];
            i++;
        }
    }while(i < n);
    if(DEBUG){printf(GREEN "Debug before core dump 2\n" DEF);}
    // Swapping array pointers
    temp = job2;
    job2 = job;
    job = temp;

    // Saving space from used arrays
    //free(job2);
    free(low);
    free(high);


    for(i = 0; i < n; i++)
    {
        if(DEBUG){printf(GREEN "job[%d] = %d, %d, %d\n" DEF, i, job[i].value,  job[i].start, job[i].finish);}
    }

    // Create an array to store solutions of subproblems.
    int* table = (int*)malloc(sizeof(int)*n);
    table[0] = 0;
    
    if(DEBUG){printf(GREEN "Debug before core dump 3\n" DEF);}
    // Fill entries in M[] using recursive property
    for (i = 1; i < n; i++) {
        // Find value including the current job
        int inclProf = job[i].value;

        int l = latestNonConflict(job, i);

        // if(DEBUG){printf("Debug i = %d\n", i);}
        // if(DEBUG){printf("Debug l = %d\n", l);}

        if (l != -1){
            inclProf += table[l];
            
            if(DEBUG){printf("++ table[%d] = %d\n" DEF, l, table[l]);}
            
        }
    
        // Store maximum of including and excluding
        table[i] = max(inclProf, table[i - 1]);
        if(DEBUG){printf("Debug table[%d] = %d\n" DEF, i, table[i]);}
    }

    if(DEBUG){printf(GREEN "Debug before core dump 4\n" DEF);}

    int result = table[n - 1];
    free(table);
 
    printf("\nresult = %d\n", result);
    // for(i = 0; i < weeksNumber; i++)
    // {

    // }

}

int max(int a, int b)
{
    return (a>=b)*a + (b>a)*b;
}

int latestNonConflict(Job* job, int i)
{
    int j;
    for (j = i - 1; j >= 0; j--) {
        if (job[j].finish <= job[i].start){
            return j;
        }
    }
    return -1;
}