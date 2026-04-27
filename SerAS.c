#include<stdio.h>
#include<stdlib.h>
#include <time.h>
int main()
{
    int row,col,i=0,j=0;
    printf("Enter the number of rows and columns:");
    scanf("%d %d",&row,&col);
    int **F_Matrix1=malloc(row*sizeof(int*));
    int **S_Matrix2=malloc(row*sizeof(int*));
    int **R_Addition=malloc(row*sizeof(int*));
    int **R_Subtraction=malloc(row*sizeof(int*));
    for(i=0;i<row;i++)
    {
        F_Matrix1[i]=malloc(col*sizeof(int));
        S_Matrix2[i]=malloc(col*sizeof(int));
        R_Addition[i]=malloc(col*sizeof(int));
        R_Subtraction[i]= malloc(col*sizeof(int));
    }
    srand(time(NULL));
    for(i=0;i<row;i++)
        for(j=0;j<col;j++)
        {
            F_Matrix1[i][j]=rand()%43;
            S_Matrix2[i][j]=rand()%43;
        }
    clock_t Cpu_Starttime=clock();
    printf("Resulatant Addition Matrix:\n");
    for(i=0;i<row;i++){
        for(j=0;j<col;j++){
            R_Addition[i][j]=F_Matrix1[i][j]+S_Matrix2[i][j];
            //printf("%d\t",R_Addition[i][j]);
        }
        printf("\n");
    }
    printf("Resultant Subtraction Matrix:\n");
    for(i=0;i<row;i++){
        for(j=0;j<col;j++){
            R_Subtraction[i][j]=F_Matrix1[i][j]-S_Matrix2[i][j];
            //printf("%d\t",R_Subtraction[i][j]);
        }
        printf("\n");
    }
    clock_t Cpu_Endtime=clock();
    double serial_time=(double)(Cpu_Endtime-Cpu_Starttime)/CLOCKS_PER_SEC;
    printf("Serial Execution Time(in Seconds):%fseconds\n",serial_time);
    for(i=0;i<row;i++)
    {
        free(F_Matrix1[i]);
        free(S_Matrix2[i]);
        free(R_Addition[i]);
        free(R_Subtraction[i]);
    }
    free(F_Matrix1);
    free(S_Matrix2);
    free(R_Addition);
    free(R_Subtraction);
    return 0;
}
