/*
Name: Shan Sahib
Email: sssahib@crimson.ua.edu
Course Section: CS 481
Homework #: 1
Instructions to compile the program: gcc -O gameoflife1.c -o gameoflife (to print matrices add -DDEBUG_PRINT)
Instructions to run the program: ./gameoflife <size> <max number of generations>    
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

double gettime(void) {
  struct timeval tval;

  gettimeofday(&tval, NULL);

  return( (double)tval.tv_sec + (double)tval.tv_usec/1000000.0 );
}

int **allocarray(int P, int Q) {
  int i;
  int *p, **a;
  
  p = (int *)malloc(P*Q*sizeof(int));
  a = (int **)malloc(P*sizeof(int*));

  if (p == NULL || a == NULL) 
    printf("Error allocating memory\n");

  /* for row major storage */
  for (i = 0; i < P; i++)
    a[i] = &p[i*Q];
  
  return a;
}

int **initarray(int **a, int mrows, int ncols, int value) {
  int i,j;

  for (i=0; i<mrows; i++) {
    for (j=0; j<ncols; j++) {
      if (i == 0 || j == 0 || i == mrows-1 || j == ncols-1) {
        a[i][j] = 0;
      }
      else {
        a[i][j] = drand48()*value;
      }
    }
  }
  
  return a;
}

void printarray(int **a, int mrows, int ncols) {
  int i,j;
  
  for (i=0; i<mrows; i++) {
    for (j=0; j<ncols; j++)
      printf("%d ", a[i][j]);
    printf("\n");
  }
}

// counts the # of alive cells around given cell
int count(int **a, int i, int j) {
  int count = 0;

  if (a[i-1][j-1] == 1) {
    count++;
  }
  if (a[i-1][j] == 1) {
    count++;
  }
  if (a[i-1][j+1] == 1) {
    count++;
  }
  if (a[i][j-1] == 1) {
    count++;
  }
  if (a[i][j+1] == 1) {
    count++;
  }
  if (a[i+1][j-1] == 1) {
    count++;
  }
  if (a[i+1][j] == 1) {
    count++;
  }
  if (a[i+1][j+1] == 1) {
    count++;
  }
    
  return count;
}

// changes the board from the previous generation to the next generation
void playgame(int **a, int **b, int mrows, int ncols) {
  int i, j;
  int numofalive = 0;

  for (i = 0; i < mrows; i++) {
    for (j = 0; j < ncols; j++) {
      if (i == 0 || j == 0 || i == mrows-1 || j == ncols-1) {
        continue;
      }
      else {
        numofalive = count(a, i, j);
        // if cell is alive
        if (a[i][j] == 1) {
          if (numofalive <= 1){
              b[i][j] = 0;
          }
          else if (numofalive >= 4){
              b[i][j] = 0;
          }
          else if (numofalive == 2 || numofalive == 3) {
              b[i][j] = 1;
          }
        }
        // if cell is dead
        else if (a[i][j] == 0) {
          if (numofalive == 3) {
              b[i][j] = 1;
          }
          else {
              b[i][j] = 0;
          }
        } 
      } 
    }
  }
}

int main(int argc, char **argv) {
    int N, maxGen;
    int **a=NULL, **b=NULL;
    double starttime, endtime;

    if (argc != 3) {
      printf("Usage: %s <N>\n", argv[0]);
      exit(-1);
    }
    
    N = atoi(argv[1]);
    maxGen = atoi(argv[2]);
    
    /* Allocate memory both matrices */
    a = allocarray(N+2, N+2);
    b = allocarray(N+2, N+2);
    
    /* Initialize the matrices */
    srand48(123456);
    a = initarray(a, N+2, N+2, (int)(2));
    b = initarray(b, N+2, N+2, (int)(1));
  
    #ifdef DEBUG_PRINT
      printarray(a, N+2, N+2);
      printf("\n");
    #endif

    starttime = gettime();

    int arrayswap = 0;
    for (int i = 0; i < maxGen; i++) {
      // if array a is the previous generation
      if (arrayswap == 0) {
        playgame(a, b, N+2, N+2);
        #ifdef DEBUG_PRINT
          printarray(b, N+2, N+2);
          printf("\n");
        #endif
        arrayswap = 1;
      }
      // if array b is the previous generation
      else if (arrayswap == 1) {
        playgame(b, a, N+2, N+2);
        #ifdef DEBUG_PRINT
          printarray(a, N+2, N+2);
          printf("\n");
        #endif
        arrayswap = 0;
      }
    }
    endtime = gettime();

    free(a);
    free(b);
    printf("Time taken = %lf seconds\n", endtime-starttime);

    return 0;
}