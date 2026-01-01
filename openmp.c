#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#include<sys/time.h>
#define number 10000
int *x;
int *y;
int *z;
int main(){
    struct timeval s_start,s_end,p_start,p_end;

gettimeofday(&s_start,NULL);
x = malloc(number *sizeof(int));
y = malloc(number *sizeof(int));
z = malloc(number *sizeof(int));


for(int i=0;i<number;i++){
    x[i] = rand() % 10000;
     y[i] = rand() % 10000;
     z[i] = 0;

}
gettimeofday(&s_end,NULL);
double s_time=(s_end.tv_sec-s_start.tv_sec )  + ( s_end.tv_usec-s_start.tv_usec)/10000.0;
gettimeofday(&p_start,NULL);
#pragma omp parallel num_threads (4)
{
long int sum =0;
for (int i=0; i<number;i++){
    z[i]=x[i]*y[i];

    sum =sum+z[i];
}
}

gettimeofday(&p_end,NULL);
long int sum =0;
double p_time=(p_end.tv_sec-p_start.tv_sec )  + ( p_end.tv_usec-p_start.tv_usec)/10000.0;
 printf("Sum is %ld\nS time: %f sec\nP time: %f sec\nTotal time: %f sec\n",
       sum, s_time, p_time, s_time + p_time);

}