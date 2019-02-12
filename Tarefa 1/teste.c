#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(){

    int n;
    omp_set_num_threads(4);
    #pragma omp parallel
    {
        #pragma omp for ordered
        for (n=0;n<10;n++)
            #pragma omp ordered
            printf("n = %d\n",n);
    }
    return 0;
}
