#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <time.h>
int main()
{
    int row,col,p1,i,j,k;
    printf("Enter the number of rows and columns:");
    scanf("%d %d",&row,&col);
    int **F_Matrix1=malloc(row*sizeof(int*));
    int **S_Matrix2=malloc(col*sizeof(int*));
    for(i=0;i<row;i++){
        F_Matrix1[i]=malloc(col*sizeof(int));
    }
    for(i=0;i<col;i++){
        S_Matrix2[i]=malloc(row*sizeof(int));
    }
    srand(time(NULL));
    for(i=0;i<row;i++){
        for(j=0;j<col;j++){
            F_Matrix1[i][j]=rand()%43;
        }
    }
    for(i=0;i<col;i++){
        for(j=0;j<row;j++){
            S_Matrix2[i][j]=rand()%43;
        }
    }
    int shm1_res=shmget(4343, row*row*sizeof(int),IPC_CREAT|0666);
    int (*arr)[row]=shmat(shm1_res,NULL,0);
    int shm1_time=shmget(4747, row*sizeof(double),IPC_CREAT|0666);
    double *t_arr=shmat(shm1_time, NULL, 0);
    for(i=0;i<row;i++){
        p1=fork();
        if(p1==0){
            clock_t Cpu_Starttime=clock();
            for(j=0;j<row;j++)
            {
                arr[i][j]=0;
                for(k=0;k<col;k++){
                    arr[i][j]+=F_Matrix1[i][k]*S_Matrix2[k][j];
                }
                printf("%d\t",arr[i][j]);
            }
            printf("\n");
            clock_t Cpu_Endtime=clock();
            t_arr[i]=(double)(Cpu_Endtime - Cpu_Starttime)/CLOCKS_PER_SEC;
            shmdt(arr);
            shmdt(t_arr);
            exit(0);
        }
    }
    for(i=0;i<row;i++){
        wait(NULL);
    }
    double High=t_arr[0];
    for(i=1;i<row;i++)
        if(t_arr[i]>High)
            High=t_arr[i];
    printf("Execution Time by Parallely:%fsec\n",High);
    shmdt(arr);
    shmdt(t_arr);
    shmctl(shm1_res,IPC_RMID,NULL);
    shmctl(shm1_time,IPC_RMID,NULL);
    for(i=0;i<row;i++){
        free(F_Matrix1[i]);
    }
    for(i=0;i<col;i++){
        free(S_Matrix2[i]);
    }
    free(F_Matrix1);
    free(S_Matrix2);
    return 0;
}
