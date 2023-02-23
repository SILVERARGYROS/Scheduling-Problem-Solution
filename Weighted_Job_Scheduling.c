// Algorithm Sources

// Solution idea - UoP eClass: Lecture #4 - Dynamic Programming (page 26): https://eclass.uop.gr/modules/document/file.php/3061/Lecture%204.pdf
// Implementation idea - GeeksforGeeks: Weighted Job Scheduling: https://www.geeksforgeeks.org/weighted-job-scheduling/?ref=lbp
// QuickSort Implementation idea - Tutorialspoint: https://www.tutorialspoint.com/explain-the-quick-sort-technique-in-c-language

// Libraries
#include <stdio.h>
#include <stdlib.h>

// Debug constants
#define DEBUG 1
#define CLEAR_SCREEN 1
#define DEBUG_SORT 1
#define DEBUG_INDEX 1
#define DEBUG_CORE_DUMP 1
#define FIXED_EXAMPLE 1

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

// Job Structure
typedef struct Jobs{
    int value;
    int start;
    int finish;
} Job;

// Supporting Functions
int max(int a, int b);
int P(Job* job, int i);
void findSolution(Job* job, int* M, int j);
int compare (Job a, Job b);
void quicksort(Job* job,int first,int last);
void findSolution(Job* job, int* M, int j);

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

    int n = weeksNumber * 2;

    // Initializing job array
    Job* job = (Job*)malloc(sizeof(Job) * (n));
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



    if(DEBUG){for(i = 0; i < n; i++){printf(BLUE "job[%d] : s = %d, f = %d, v = %d\n" DEF, i, job[i].start, job[i].finish, job[i].value);}printf("\n");}

    if(DEBUG_CORE_DUMP){printf(RED "Debug before core dump 1\n" DEF);}

    if(DEBUG_SORT){printf(RED "\nBefore sort\n");for(i = 0; i < n; i++){printf("job[%d] = %d, %d, %d\n", i, job[i].value,  job[i].start, job[i].finish);}printf("\n" DEF);}

    // Sorting job array
    quicksort(job, 0, n-1);

    if(DEBUG_SORT){printf(RED "After sort\n");for(i = 0; i < n; i++){printf("job[%d] = %d, %d, %d\n", i, job[i].value,  job[i].start, job[i].finish);}printf("\n" DEF);}

    if(DEBUG_CORE_DUMP){printf(RED "Debug before core dump 2\n" DEF);}


    // Saving space from unnecessary arrays
    free(low);
    free(high);

    if(DEBUG){for(i = 0; i < n; i++){printf(BLUE "job[%d] = %d, %d, %d\n" DEF, i, job[i].value,  job[i].start, job[i].finish);}}

    // Create an array to store solutions of subproblems.
    int* M = (int*)malloc(sizeof(int)*n);
    M[0] = job[0].value;
    
    if(DEBUG_CORE_DUMP){printf(RED "Debug before core dump 3\n" DEF);}

    // Fill entries in M[] using recursive property
    for (i = 1; i < n; i++) {
        // Find value including the current job
        int inclVal = job[i].value;
        int p = P(job, i);

        if(DEBUG){printf(GREEN "Debug i = %d\n" DEF, i);}
        if(DEBUG){printf(GREEN "Debug p = %d\n" DEF, p);}

        if (p != -1){
            inclVal += M[p];
            
            if(DEBUG){printf(BLUE "M[%d] = %d\n" DEF, p, M[p]);}
        }
    
        // Store maximum of including and excluding
        M[i] = max(inclVal, M[i - 1]);

        if(DEBUG){printf(BLUE "M[%d] = %d\n" DEF, i, M[i]);}
    }

    if(DEBUG_CORE_DUMP){printf(RED "Debug before core dump 4\n" DEF);}

    int result = M[n-1];
    printf("\nOptimal Result = %d\n", result);

    // Trace jobs here to find solution
    // findSolution(job, M, n-1);

    free(M);
    free(job);
    return 0;
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

int P(Job* job, int i)
{
    int j;
    for (j = i - 1; j >= 0; j--) {
        if (job[j].finish <= job[i].start){
            return j;
        }
    }
    return -1;
}

int compare (Job a, Job b){
    return a.finish <= b.finish;
}

void quicksort(Job* job,int first,int last)
{
   int i, j, pivot;
   Job temp;
   if(first<last){
      pivot=first;
      i=first;
      j=last;
      while(i<j){
         while(job[i].finish<=job[pivot].finish && i<last)
         i++;
         while(job[j].finish>job[pivot].finish)
         j--;
         if(i<j){
            temp=job[i];
            job[i]=job[j];
            job[j]=temp;
         }
      }
      temp=job[pivot];
      job[pivot]=job[j];
      job[j]=temp;
      quicksort(job,first,j-1);
      quicksort(job,j+1,last);
   }
}

// void findSolution(Job* job, int* M, int j) 
// {
//     if (j == 0){
//         return;
//     }
//     else
//     {
//         if(job[j].value + M[P(job, j)] > M[j-1]){
//             printf("j = %d\n", j);
//             findSolution(job, M, P(job, j));
//         }
//         else
//         {
//             findSolution(job, M, j-1);
//         }
//     }
// }