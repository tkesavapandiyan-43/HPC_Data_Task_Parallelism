#include <stdio.h>
#include <time.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
int main()
{
    int row,col,p1,i,j;
    printf("Enter the number of rows and columns: ");
    scanf("%d %d",&row,&col);
    int **F_Matrix1=malloc(row*sizeof(int *));
    int **S_Matrix2=malloc(row*sizeof(int *));
    for(i=0;i<row;i++){
        F_Matrix1[i]=malloc(col*sizeof(int));
        S_Matrix2[i]=malloc(col*sizeof(int));
    }
    srand(time(NULL));
    for(i=0;i<row;i++){
        for(j=0;j<col;j++){
            F_Matrix1[i][j]=rand()%43;
            S_Matrix2[i][j]=rand()%43;
        }
    }

    p1=fork();
    if(p1==0){
        printf("Child Process in progress...\n");
        printf("Doing Matrix Addition..\n");
        clock_t Cpu_Starttime=clock();
        int **R_Matrix=malloc(row*sizeof(int*));
        for(i=0;i<row;i++){
            R_Matrix[i]=malloc(col*sizeof(int));
        }
        for(i=0;i<row;i++){
            for(j=0;j<col;j++){
                R_Matrix[i][j]=F_Matrix1[i][j]+S_Matrix2[i][j];
                printf("%d\t",R_Matrix[i][j]);
            }
            printf("\n");
        }
        clock_t Cpu_Endtime=clock();
        double childprocess=(double)(Cpu_Starttime - Cpu_Endtime)/CLOCKS_PER_SEC;
        printf("Duration: %fsec\n",childprocess);
        printf("Child process Terminated.\n");
        for(i=0;i<row;i++){
            free(R_Matrix[i]);
        }
        free(R_Matrix);
        exit(0);
    }
    else if(p1<0){
        printf("Process can't be created.\n");
        return 1;
    }
    else
    {
        printf("Parent process running...\n");
        printf("Doing Matrix Subtraction..\n");
        clock_t Cpu_Starttime=clock();
        int **R_Matrix=malloc(row*sizeof(int*));
        for(i=0;i<row;i++){
            R_Matrix[i]=malloc(col*sizeof(int));
        }
        for(i=0;i<row;i++){
            for(j=0;j<col;j++){
                R_Matrix[i][j]=F_Matrix1[i][j]-S_Matrix2[i][j];
                printf("%d\t",R_Matrix[i][j]);
            }
            printf("\n");
        }
        clock_t Cpu_Endtime=clock();
        double parentprocess=(double)(Cpu_Endtime - Cpu_Starttime)/CLOCKS_PER_SEC;
        printf("Duration: %fsec\n",parentprocess);
        wait(NULL);
        printf("Parent process Terminated.\n");
        for(i=0;i<row;i++){
            free(R_Matrix[i]);
        }
        free(R_Matrix);
    }
    for(i=0;i<row;i++){
        free(F_Matrix1[i]);
        free(S_Matrix2[i]);
    }
    free(F_Matrix1);
    free(S_Matrix2);
    return 0;
}
