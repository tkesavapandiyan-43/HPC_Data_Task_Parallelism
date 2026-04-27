#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main()
{
    int row,col,i,j,k;
    printf("Enter the number of rows in Matrix1(row) and columns of Matrix1 / rows of Matrix2 (col): ");
    scanf("%d %d",&row,&col);
    int **F_Matrix1=malloc(row*sizeof(int*));
    int **S_Matrix2=malloc(col*sizeof(int*));
    int **R_Multiplication=malloc(row*sizeof(int*));
    for(i=0;i<row;i++)
    {
        F_Matrix1[i]=malloc(col*sizeof(int));
        R_Multiplication[i]=malloc(row*sizeof(int));
    }
    for(i=0;i<col;i++){
        S_Matrix2[i]=malloc(row*sizeof(int));
    }
    srand(time(NULL));
    printf("First Matrix:\n");
    for(i=0;i<row;i++){
        for(j=0;j<col;j++){
            F_Matrix1[i][j]=rand()%43;
            printf("%d\t",F_Matrix1[i][j]);
        }
        printf("\n");
    }
    printf("Second Matrix:\n");
    for(i=0;i<col;i++){
        for(j=0;j<row;j++){
            S_Matrix2[i][j]=rand()%43;
            printf("%d\t",S_Matrix2[i][j]);
        }
        printf("\n");
    }
    clock_t Cpu_Starttime=clock();
    printf("Resulatant Multiplication Matrix\n");
    for(i=0;i<row;i++){
        for(j=0;j<row;j++){
            R_Multiplication[i][j]=0;
            for(k=0;k<col;k++){
                R_Multiplication[i][j]+=F_Matrix1[i][k]*S_Matrix2[k][j];
            }
            printf("%d\t",R_Multiplication[i][j]);
        }
        printf("\n");
    }
    clock_t Cpu_Endtime=clock();
    double Exe_serial_time =(double)(Cpu_Endtime - Cpu_Starttime)/CLOCKS_PER_SEC;
    printf("Serial Matrix Multiplication Time: %f seconds\n",Exe_serial_time);
    for(i=0;i<row;i++)
    {
        free(F_Matrix1[i]);
        free(R_Multiplication[i]);
    }
    for(i=0;i<col;i++){
        free(S_Matrix2[i]);
    }
    free(F_Matrix1);
    free(S_Matrix2);
    free(R_Multiplication);
    return 0;
}
