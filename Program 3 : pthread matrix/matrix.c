/*Run using : 
$ gcc matrix.c -o matrix -lpthread
$ ./matrix

To demonstrate use of pthread library functions to create and manage threads, using a
program that raises the numbers to the power of their corresponding row in the matrix (matrix
indexed from 1).
*/

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

int a[4][4], b[4][4];

void *matrixeval(void *val)
{
    int row = *(int *) val;
    for (int i=0; i<4; i++){
        b[row][i] = a[row][i];
        for (int j=0; j<row; j++){
            b[row][i] *= a[row][i];
        }
    }
    pthread_exit(NULL);
}

int main ()
{
    pthread_t tid[4];
    int row[4], i, j;

    for (i=0; i<4; i++){
        printf ("Enter elements of row %d : ", i+1);
        for (j=0; j<4; j++){
            scanf ("%d", &a[i][j]);
        }
    }

    printf ("Before Processing : \n");
    for (i=0; i<4; i++){
        for (j=0; j<4; j++){
            printf ("%d \t", a[i][j]);
        }
        printf("\n");
    }

    for (i=0; i<4; i++){
        row[i] = i;
        pthread_create(&tid[i], NULL, matrixeval, &row[i]);
    }

    for (i=0; i<4; i++){
        pthread_join(tid[i], NULL);
    }

    printf ("\nAfter Processing : \n");
    for (i=0; i<4; i++){
        for (j=0; j<4; j++){
            printf ("%d \t", b[i][j]);
        }
        printf("\n");
    }
    return 0;
}