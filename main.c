#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "function.h"

float a[2048 * 2048] = {0};
float b[2048 * 2048] = {0};
float d[2048 * 2048] = {0};
int read_row(FILE *fp);
int read_col(FILE *fp);

int main(int argc, char *argv[])
{
   clock_t start, finish, finish1, start1;
   double duration, duration1;
   FILE *f1;
   FILE *f2;
   int col1, row1, col2, row2 = 0;
   //f1文件读入
   start = clock();
   f1 = fopen(argv[1], "r");
   if (f1 == NULL)
      perror("Error opening file");
   else
   {
      col1 = read_col(f1);
      row1 = read_row(f1);
      while (!feof(f1))
      {
         for (int i = 0; i < row1 * col1; i++)
         {
            fscanf(f1, "%f", &a[i]);
         }
      }
      fclose(f1);
   }

   //f2文件读入
   f2 = fopen(argv[2], "r");
   if (f2 == NULL)
      perror("Error opening file");
   else
   {
      col2 = read_col(f2);
      row2 = read_row(f2);
      while (!feof(f2))
      {
         for (int i = 0; i < row2 * col2; i++)
         {
            fscanf(f2, "%f", &b[i]);
         }
      }
      fclose(f2);
   }
   finish1 = clock();

   //function generate 的测试
   struct mat mat1 = generate(row1, col1, a);
   struct mat mat2 = generate(row2, col2, b);
   struct mat mat3 = mulmat(mat1, mat2);

   // //function generateR 的测试
   // struct mat matR = generateR(2,2);
   // printf("the col of matR is:%d, and the row of matR is:%d \n",matR.col,matR.row);
   // for(int i = 0;i < 4;i++){
   //    printf("%f \n",*matR.matrix);
   //    matR.matrix ++;
   // }
   // matR.matrix = matR.matrix -4;

   //function delete 的测试
   // struct mat * p = &mat1;
   // deletemat(p);
   // printf("the col of mat1 is:%d, and the row of mat1 is:%d \n",mat1.col,mat1.row);

   // //function copy 的测试
   // struct mat mat3 = copymat( mat2);
   // printf("the col of mat3 is:%d, and the row of mat3 is:%d \n",mat3.col,mat3.row);
   // for(int i = 0;i < 4;i++){
   //    printf("%f \n",*mat3.matrix);
   //    mat3.matrix ++;
   // }
   // mat3.matrix = mat3.matrix-4;

   // //function getvalue 的测试
   // printf("here is the test for getvalue,mat3[3] is %f\n",getvalueofmat(1,1,mat2));
   // //function setvalue 的测试
   // struct mat * p2 = &mat2;
   // setvalueofmat(0,0,0.4433f,p2);
   // printf("here test for setvalue function, now mat2[0] is %f\n",*mat2.matrix);

   //f3文件的写出
   start1 = clock();
   FILE *f3 = fopen(argv[3], "wb+");
   if (f3 == NULL)
      perror("Error opening file");
   else
   {
      for (int i = 0; i < row1; i++)
      {
         for (int j = 0; j < col2; j++)
         {
            fprintf(f3, "%f ", *mat3.matrix);
            mat3.matrix++;
         }
         fprintf(f3, "\n");
      }
   }
   fclose(f3);
   finish = clock();
   duration = (double)(finish - start) / CLOCKS_PER_SEC;
   duration1 = (double)(finish1 - start + finish - start1) / CLOCKS_PER_SEC;
   printf("running time is %f seconds\n", duration);
   printf("the IO time is %f seconds\n", duration1);
}

int read_row(FILE *fp)
{
   int c = 0;
   int row = 0;
   while ((c = fgetc(fp)) != EOF)
   {
      if (c == '\n')
      {
         row++;
      }
   }
   row++;
   rewind(fp);
   return row;
}

int read_col(FILE *fp)
{
   int c = 0;
   int col = 0;
   while ((c = fgetc(fp)) != '\n')
   {
      if (c == ' ')
      {
         col++;
      }
   }
   col++;
   rewind(fp);
   return col;
}